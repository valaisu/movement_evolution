// Agent is the base class for controllable 
// agents such as dog and car

#ifndef DOG_HPP
#define DOG_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "agents/Agent.hpp"
#include "objects/Shape.hpp"
#include "objects/Active_rectangle.hpp"
#include "Game.hpp"

// the constructor defines what the body looks like, takes some work

class Dog : public Agent{
public:
    Dog(b2Vec2 initial_position, float lower_leg_length, float upper_leg_length, float body_length, float leg_radius, float body_radius, float visual_scaling_factor, Game *game);
    ~Dog() override;
    
    void update(float time_step) override;
    void draw(sf::RenderWindow *window) const override;
    void control_leg(int leg_ind, bool pos_dir);
private:
    // this is a bit of a bubblegum solution
    Active_capsule* dog_body;
    Active_capsule* back_leg_upper;
    Active_capsule* back_leg_lower;
    Active_capsule* front_leg_upper;
    Active_capsule* front_leg_lower;
    // also TODO: remove these in deconstructor
    // body_parts;
    // location
    std::vector<b2JointId*> joints;
    float motor_speed;
    float motor_torque;
}; 










#endif