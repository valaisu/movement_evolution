#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "agents/Agent.hpp"
#include "agents/Dog.hpp"
#include "objects/Shape.hpp"
#include "objects/Active_rectangle.hpp"
#include "Game.hpp"


/*
Ok so currently, each bodypart is saved to 
    the class   (here it is actually stored)
    game        (collects everything to be updated)
    shapes      (prevents stuff from going out of scope?)

Only the first one is needed I think, we can just have to modify the
game.cpp to update all of the agents separately

*/



Dog::Dog(b2Vec2 initial_position, float lower_leg_length, float upper_leg_length, float body_length, float leg_radius, float body_radius, float visual_scaling_factor, Game *game) :
    Agent(initial_position)
{
    // Creating a dog seems to work
    dog_body = new Active_rectangle((b2Vec2){16.5f, 13.6f}, 3.0f, 0.4f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());


    // BACK LEG
    // create boxes
    back_leg_upper = new Active_rectangle((b2Vec2){15.0f, 14.0f}, 0.4f, 1.0f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    back_leg_lower = new Active_rectangle((b2Vec2){15.0f, 15.0f}, 0.4f, 1.0f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    // connect with joint
    b2RevoluteJointDef back_leg_joint_def = b2DefaultRevoluteJointDef();
    back_leg_joint_def.bodyIdA = back_leg_upper->get_body_id();
    back_leg_joint_def.bodyIdB = back_leg_lower->get_body_id();
    // anchor point between legs
    b2Vec2 pivot_back_leg = {15.0f, 14.5f};
    back_leg_joint_def.localAnchorA = b2Body_GetLocalPoint(back_leg_upper->get_body_id(), pivot_back_leg);
    back_leg_joint_def.localAnchorB = b2Body_GetLocalPoint(back_leg_lower->get_body_id(), pivot_back_leg);
    // create the joint
    b2JointId back_leg_joint = b2CreateRevoluteJoint( game->get_world_id(), &back_leg_joint_def );


    // FRONT LEG
    front_leg_upper = new Active_rectangle((b2Vec2){18.0f, 14.0f}, 0.4f, 1.0f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    front_leg_lower = new Active_rectangle((b2Vec2){18.0f, 15.0f}, 0.4f, 1.0f, 0.5f, 1.0f, visual_scaling_factor, game->get_world_id());
    // connect with joint
    b2RevoluteJointDef front_leg_joint_def = b2DefaultRevoluteJointDef();
    front_leg_joint_def.bodyIdA = front_leg_upper->get_body_id();
    front_leg_joint_def.bodyIdB = front_leg_lower->get_body_id();
    // anchor point between legs
    b2Vec2 pivot_front_leg = {18.0f, 14.5f};
    front_leg_joint_def.localAnchorA = b2Body_GetLocalPoint(front_leg_upper->get_body_id(), pivot_front_leg);
    front_leg_joint_def.localAnchorB = b2Body_GetLocalPoint(front_leg_lower->get_body_id(), pivot_front_leg);
    // create the joint
    b2JointId front_leg_joint = b2CreateRevoluteJoint( game->get_world_id(), &front_leg_joint_def );


    // Connect legs to body
    // Front
    b2RevoluteJointDef front_leg_body_joint_def = b2DefaultRevoluteJointDef();
    front_leg_body_joint_def.bodyIdA = front_leg_upper->get_body_id();
    front_leg_body_joint_def.bodyIdB = dog_body->get_body_id();
    b2Vec2 pivot_front_leg_body = {18.0f, 13.5f};
    front_leg_body_joint_def.localAnchorA = b2Body_GetLocalPoint(front_leg_upper->get_body_id(), pivot_front_leg_body);
    front_leg_body_joint_def.localAnchorB = b2Body_GetLocalPoint(dog_body->get_body_id(), pivot_front_leg_body);
    // create the joint
    b2JointId front_leg_body_joint = b2CreateRevoluteJoint( game->get_world_id(), &front_leg_body_joint_def );
    // Back
    b2RevoluteJointDef back_leg_body_joint_def = b2DefaultRevoluteJointDef();
    back_leg_body_joint_def.bodyIdA = back_leg_upper->get_body_id();
    back_leg_body_joint_def.bodyIdB = dog_body->get_body_id();
    b2Vec2 pivot_back_leg_body = {15.0f, 13.5f};
    back_leg_body_joint_def.localAnchorA = b2Body_GetLocalPoint(back_leg_upper->get_body_id(), pivot_back_leg_body);
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








