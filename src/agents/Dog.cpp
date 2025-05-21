#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

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
    // temporary variables to make stuff easier
    // l = low, v = vertical, u = up, h = horizontal, b = back, f = front
    b2Vec2 radius_vertical_leg = {0.0f, leg_radius};
    b2Vec2 leg_low_height = {0.0f, lower_leg_length};
    b2Vec2 leg_up_height = {0.0f, upper_leg_length};
    b2Vec2 body_vector = {body_length, 0.0f};

    b2Vec2 center_1_back = initial_position - radius_vertical_leg;
    b2Vec2 center_2_back = center_1_back - leg_low_height;
    b2Vec2 center_3_back = center_2_back - leg_up_height;
    b2Vec2 center_1_front = center_1_back + body_vector;
    b2Vec2 center_2_front = center_2_back + body_vector;
    b2Vec2 center_3_front = center_3_back + body_vector;

    

    // Creating a dog seems to work
    //dog_body = new Active_rectangle((b2Vec2){16.5f, 13.6f}, 3.0f, 0.4f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    dog_body = new Active_capsule(center_3_back, center_3_front, body_radius, 0.3, 1.0, visual_scaling_factor, game->get_world_id());

    // BACK LEG
    // create boxes
    //back_leg_upper = new Active_rectangle((b2Vec2){15.0f, 14.0f}, 0.4f, 1.0f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    //back_leg_lower = new Active_rectangle((b2Vec2){15.0f, 15.0f}, 0.4f, 1.0f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    back_leg_upper = new Active_capsule(center_1_back, center_2_back, leg_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    back_leg_lower = new Active_capsule(center_2_back, center_3_back, leg_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());

    // connect with joint
    b2RevoluteJointDef back_leg_joint_def = b2DefaultRevoluteJointDef();
    back_leg_joint_def.bodyIdA = back_leg_upper->get_body_id();
    back_leg_joint_def.bodyIdB = back_leg_lower->get_body_id();
    // anchor point between legs
    b2Vec2 pivot_back_leg = center_2_back;
    back_leg_joint_def.localAnchorA = b2Body_GetLocalPoint(back_leg_upper->get_body_id(), pivot_back_leg);
    back_leg_joint_def.localAnchorB = b2Body_GetLocalPoint(back_leg_lower->get_body_id(), pivot_back_leg);
    // create the joint
    b2JointId back_leg_joint = b2CreateRevoluteJoint( game->get_world_id(), &back_leg_joint_def );


    // FRONT LEG
    //front_leg_upper = new Active_rectangle((b2Vec2){18.0f, 14.0f}, 0.4f, 1.0f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    //front_leg_lower = new Active_rectangle((b2Vec2){18.0f, 15.0f}, 0.4f, 1.0f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    front_leg_upper = new Active_capsule(center_1_front, center_2_front, leg_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    front_leg_lower = new Active_capsule(center_2_front, center_3_front, leg_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    
    // connect with joint
    b2RevoluteJointDef front_leg_joint_def = b2DefaultRevoluteJointDef();
    front_leg_joint_def.bodyIdA = front_leg_upper->get_body_id();
    front_leg_joint_def.bodyIdB = front_leg_lower->get_body_id();
    // anchor point between legs
    b2Vec2 pivot_front_leg = center_2_front;
    front_leg_joint_def.localAnchorA = b2Body_GetLocalPoint(front_leg_upper->get_body_id(), pivot_front_leg);
    front_leg_joint_def.localAnchorB = b2Body_GetLocalPoint(front_leg_lower->get_body_id(), pivot_front_leg);
    // create the joint
    b2JointId front_leg_joint = b2CreateRevoluteJoint( game->get_world_id(), &front_leg_joint_def );


    // Connect legs to body
    // Front
    b2RevoluteJointDef front_leg_body_joint_def = b2DefaultRevoluteJointDef();
    front_leg_body_joint_def.bodyIdA = front_leg_lower->get_body_id(); // TODO: this indicates problems, fix
    front_leg_body_joint_def.bodyIdB = dog_body->get_body_id();
    b2Vec2 pivot_front_leg_body = center_3_front;
    front_leg_body_joint_def.localAnchorA = b2Body_GetLocalPoint(front_leg_lower->get_body_id(), pivot_front_leg_body);
    front_leg_body_joint_def.localAnchorB = b2Body_GetLocalPoint(dog_body->get_body_id(), pivot_front_leg_body);
    // create the joint
    b2JointId front_leg_body_joint = b2CreateRevoluteJoint( game->get_world_id(), &front_leg_body_joint_def );
    // Back
    b2RevoluteJointDef back_leg_body_joint_def = b2DefaultRevoluteJointDef();
    back_leg_body_joint_def.bodyIdA = back_leg_lower->get_body_id();
    back_leg_body_joint_def.bodyIdB = dog_body->get_body_id();
    b2Vec2 pivot_back_leg_body = center_3_back;
    back_leg_body_joint_def.localAnchorA = b2Body_GetLocalPoint(back_leg_lower->get_body_id(), pivot_back_leg_body);
    back_leg_body_joint_def.localAnchorB = b2Body_GetLocalPoint(dog_body->get_body_id(), pivot_back_leg_body);
    // create the joint
    b2JointId back_leg_body_joint = b2CreateRevoluteJoint( game->get_world_id(), &back_leg_body_joint_def );

    // Add all bodyparts to a vector for easier update function
    body_parts.push_back(dog_body);
    body_parts.push_back(back_leg_upper);
    body_parts.push_back(back_leg_lower);
    body_parts.push_back(front_leg_upper);
    body_parts.push_back(front_leg_lower);

    // TODO: 
    // use capsules instead of boxes
    // add constraints to the joints
    // add motors to the joints
    // keybinds for moving the motors
    // at some point: dont store stuff in game and shapes if possible, 
    //  requires editing the games update function as well as some 
    //  other things
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








