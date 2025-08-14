#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "agents/Agent.hpp"
#include "agents/Dog.hpp"
#include "objects/Shape.hpp"
#include "objects/Active_rectangle.hpp"
#include "objects/Active_capsule.hpp"
#include "Game.hpp"



/* TEMPORARY THOUGHTS
Lets use the cylinders for dog body parts. Also
Lets make the size controls actually do something

initial_position = lowest point of the back-leg 

I feel like the best bad solution for what lower_leg_length
actually means is that it's the distance between the circle 
centers in the capsule
*/



Dog::Dog(b2Vec2 initial_position, float lower_leg_length, float upper_leg_length, float body_length, float leg_radius, float body_radius, float visual_scaling_factor, Game *game) :
    Agent(initial_position)
{
    // TODO: control these wo magic values at some point
    motor_speed = 0.5 * B2_PI;
    motor_torque = 300.0f;

    // temporary variables to make stuff simpler
    // l = low, v = vertical, u = up, h = horizontal, b = back, f = front
    b2Vec2 radius_vertical_leg = {0.0f, leg_radius};
    b2Vec2 leg_low_height = {0.0f, lower_leg_length};
    b2Vec2 leg_up_height = {0.0f, upper_leg_length};
    b2Vec2 body_vector = {body_length, 0.0f};

    // 3 highest, 1 lowest
    b2Vec2 center_1_back = initial_position - radius_vertical_leg;
    b2Vec2 center_2_back = center_1_back - leg_low_height;
    b2Vec2 center_3_back = center_2_back - leg_up_height;
    b2Vec2 center_1_front = center_1_back + body_vector;
    b2Vec2 center_2_front = center_2_back + body_vector;
    b2Vec2 center_3_front = center_3_back + body_vector;

    

    // Creating a dog seems to work
    dog_body = new Active_capsule(center_3_back, center_3_front, body_radius, 0.3, 1.0, visual_scaling_factor, game->get_world_id());

    // BACK LEG
    // create boxes
    back_leg_lower = new Active_capsule(center_1_back, center_2_back, leg_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    back_leg_upper = new Active_capsule(center_2_back, center_3_back, leg_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());

    // connect with joint
    b2RevoluteJointDef back_leg_joint_def = b2DefaultRevoluteJointDef();
    back_leg_joint_def.bodyIdA = back_leg_upper->get_body_id();
    back_leg_joint_def.bodyIdB = back_leg_lower->get_body_id();
    // anchor point between legs
    b2Vec2 pivot_back_leg = center_2_back;
    back_leg_joint_def.localAnchorA = b2Body_GetLocalPoint(back_leg_upper->get_body_id(), pivot_back_leg);
    back_leg_joint_def.localAnchorB = b2Body_GetLocalPoint(back_leg_lower->get_body_id(), pivot_back_leg);
    
    // define angle limit
    back_leg_joint_def.referenceAngle = ( // bodyB - bodyA
        back_leg_lower->get_rotation().asRadians() -
        back_leg_upper->get_rotation().asRadians()
    );
    // This defines the legs to turn in opposite direction as dogs, but 
    // I think that way the task to move is easier
    back_leg_joint_def.lowerAngle = -0.01 * B2_PI; // how much lower leg turn backwards
    back_leg_joint_def.upperAngle = 0.9 * B2_PI; // how much lower leg turn forwards
    back_leg_joint_def.enableLimit = true; // bruh, forgoring this bad :D

    // Add motors
    // ok so this is apparently the target speed of the motor, and to control
    // the agent, we just edit it with
    // b2RevoluteJoint_SetMotorSpeed(motor_joint, speed);
    back_leg_joint_def.motorSpeed = 0 * B2_PI; 
    back_leg_joint_def.maxMotorTorque = motor_torque; // is this a lot ro little, dunno
    back_leg_joint_def.enableMotor = true;

    // create the joint
    b2JointId back_leg_joint = b2CreateRevoluteJoint( game->get_world_id(), &back_leg_joint_def );


    // FRONT LEG
    front_leg_lower = new Active_capsule(center_1_front, center_2_front, leg_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    front_leg_upper = new Active_capsule(center_2_front, center_3_front, leg_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    
    // connect with joint
    b2RevoluteJointDef front_leg_joint_def = b2DefaultRevoluteJointDef();
    front_leg_joint_def.bodyIdA = front_leg_upper->get_body_id();
    front_leg_joint_def.bodyIdB = front_leg_lower->get_body_id();
    // anchor point between legs
    b2Vec2 pivot_front_leg = center_2_front;
    front_leg_joint_def.localAnchorA = b2Body_GetLocalPoint(front_leg_upper->get_body_id(), pivot_front_leg);
    front_leg_joint_def.localAnchorB = b2Body_GetLocalPoint(front_leg_lower->get_body_id(), pivot_front_leg);
    
    // define angle limit
    front_leg_joint_def.referenceAngle = ( // bodyB - bodyA
        front_leg_lower->get_rotation().asRadians() -
        front_leg_upper->get_rotation().asRadians()
    );
    front_leg_joint_def.lowerAngle = -0.01 * B2_PI;
    front_leg_joint_def.upperAngle = 0.9 * B2_PI;
    front_leg_joint_def.enableLimit = true; 

    // Add the motors
    front_leg_joint_def.motorSpeed = 0 * B2_PI; 
    front_leg_joint_def.maxMotorTorque = motor_torque; // is this a lot ro little, dunno
    front_leg_joint_def.enableMotor = true;
    
    // create the joint
    b2JointId front_leg_joint = b2CreateRevoluteJoint( game->get_world_id(), &front_leg_joint_def );


    // CONNECT LEGS TO BODY
    // Front
    b2RevoluteJointDef front_leg_body_joint_def = b2DefaultRevoluteJointDef();
    front_leg_body_joint_def.bodyIdA = front_leg_upper->get_body_id();
    front_leg_body_joint_def.bodyIdB = dog_body->get_body_id();
    b2Vec2 pivot_front_leg_body = center_3_front;
    front_leg_body_joint_def.localAnchorA = b2Body_GetLocalPoint(front_leg_upper->get_body_id(), pivot_front_leg_body);
    front_leg_body_joint_def.localAnchorB = b2Body_GetLocalPoint(dog_body->get_body_id(), pivot_front_leg_body);
    
    // define angle limit
    front_leg_body_joint_def.referenceAngle = ( // bodyB - bodyA
        dog_body->get_rotation().asRadians() -
        front_leg_upper->get_rotation().asRadians()
    );
    front_leg_body_joint_def.lowerAngle = -0.4 * B2_PI; // how much leg turns back
    front_leg_body_joint_def.upperAngle = 0.5 * B2_PI; // how much leg turns front
    front_leg_body_joint_def.enableLimit = true; 
    
    // Add the motors
    front_leg_body_joint_def.motorSpeed = 0 * B2_PI; 
    front_leg_body_joint_def.maxMotorTorque = motor_torque; // is this a lot ro little, dunno
    front_leg_body_joint_def.enableMotor = true;
    
    // create the joint
    b2JointId front_leg_body_joint = b2CreateRevoluteJoint( game->get_world_id(), &front_leg_body_joint_def );
    

    // Back
    b2RevoluteJointDef back_leg_body_joint_def = b2DefaultRevoluteJointDef();
    back_leg_body_joint_def.bodyIdA = back_leg_upper->get_body_id();
    back_leg_body_joint_def.bodyIdB = dog_body->get_body_id();
    b2Vec2 pivot_back_leg_body = center_3_back;
    back_leg_body_joint_def.localAnchorA = b2Body_GetLocalPoint(back_leg_upper->get_body_id(), pivot_back_leg_body);
    back_leg_body_joint_def.localAnchorB = b2Body_GetLocalPoint(dog_body->get_body_id(), pivot_back_leg_body);
    
    back_leg_body_joint_def.referenceAngle = ( // bodyB - bodyA
        dog_body->get_rotation().asRadians() -
        back_leg_upper->get_rotation().asRadians()
    );
    back_leg_body_joint_def.lowerAngle = -0.4 * B2_PI; // how much leg turns back
    back_leg_body_joint_def.upperAngle = 0.5 * B2_PI; // how much leg turns front
    back_leg_body_joint_def.enableLimit = true; 

    // Add the motors
    back_leg_body_joint_def.motorSpeed = 0 * B2_PI; 
    back_leg_body_joint_def.maxMotorTorque = motor_torque; // is this a lot ro little, dunno
    back_leg_body_joint_def.enableMotor = true;

    // create the joint
    b2JointId back_leg_body_joint = b2CreateRevoluteJoint( game->get_world_id(), &back_leg_body_joint_def );

    // Add all bodyparts to a vector for easier update function
    body_parts.push_back(dog_body);
    body_parts.push_back(back_leg_upper);
    body_parts.push_back(back_leg_lower);
    body_parts.push_back(front_leg_upper);
    body_parts.push_back(front_leg_lower);

    // joints ordered left to right, up to down
    joints.push_back(back_leg_body_joint);
    joints.push_back(front_leg_body_joint);
    joints.push_back(back_leg_joint);
    joints.push_back(front_leg_joint);

    std::cout << joints.size() << std::endl;
}

sf::Vector2f Dog::get_location() {
    return dog_body->get_position();
}

std::vector<float> Dog::get_body_part_angles() {
    // return the angle of the main body essentially
    std::vector<float> parts = {
        dog_body->get_rotation().asRadians(),
        back_leg_lower->get_rotation().asRadians(),
        back_leg_upper->get_rotation().asRadians(),
        front_leg_lower->get_rotation().asRadians(),
        front_leg_upper->get_rotation().asRadians(),
    };
    return parts;
}


Dog::~Dog() {
    // Manually destroy body parts
    delete dog_body;
    delete back_leg_upper;
    delete back_leg_lower;
    delete front_leg_upper;
    delete front_leg_lower;
}

void Dog::update(float visual_scaling_factor) {
    for (auto obj : body_parts) {
        obj->update(visual_scaling_factor);
    }
}

void Dog::draw(sf::RenderWindow *window) const {
    for (auto obj : body_parts) {
        obj->draw(window);
    }
}

void Dog::move_leg(int leg_ind, bool pos_dir) {
    //std::cout << "Moving joint " << leg_ind << std::endl;

    if (!b2Joint_IsValid(joints[leg_ind])) {
        std::cout << "Joint " << leg_ind << " is invalid!" << std::endl;
        return;
    }

    // The legs can get stuck if we dont wake them up
    for (auto* part : body_parts) {
        if (part) {
            b2Body_SetAwake(part->get_body_id(), true);
        }
    }

    float dir = pos_dir ? 1.0f : -1.0f;
    b2RevoluteJoint_SetMotorSpeed(joints[leg_ind], dir*motor_speed);
    b2RevoluteJoint_SetMaxMotorTorque(joints[leg_ind], motor_torque);
    //auto end = std::chrono::system_clock::now();
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    //std::cout << "move " << std::ctime(&end_time);
}

void Dog::release_leg(int leg_ind) {
    //std::cout << "release" << std::endl;
    b2RevoluteJoint_SetMotorSpeed(joints[leg_ind], 0.0f);
    b2RevoluteJoint_SetMaxMotorTorque(joints[leg_ind], 0.0f);

    //auto end = std::chrono::system_clock::now();
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    //std::cout << "release " << std::ctime(&end_time);
}


void Dog::debug() {
    
    // check body states
    for (int i = 0; i < body_parts.size(); i++) {
        if (body_parts[i]) {
            b2BodyId bodyId = body_parts[i]->get_body_id();
            if (B2_IS_NON_NULL(bodyId)) {
                bool awake = b2Body_IsAwake(bodyId);
                bool enabled = b2Body_IsEnabled(bodyId);
                std::cout << "Body " << i << ": Awake=" << awake << ", Enabled=" << enabled << std::endl;
            }
        }
    }
}



