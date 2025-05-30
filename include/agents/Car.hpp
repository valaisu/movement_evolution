// Agent is the base class for controllable 
// agents such as dog and car

#ifndef CAR_HPP
#define CAR_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "agents/Agent.hpp"
#include "objects/Shape.hpp"
#include "objects/Active_rectangle.hpp"
#include "objects/Active_circle.hpp"
#include "Game.hpp"

// the constructor defines what the body looks like, takes some work

class Car : public Agent{
public:
    Car(b2Vec2 initial_position, float car_width, float car_height, float wheel_radius, float visual_scaling_factor, Game *game);
    ~Car() override;
    
    void update(float time_steps) override;
    void draw(sf::RenderWindow *window) const override;
    void move_forward();
    void move_reverse();
    void move_neutral();
    void debug();
private:
    // this is a bit of a bubblegum solution
    Active_rectangle* car_body;
    Active_circle* back_wheel;
    Active_circle* front_wheel;
    // also TODO: remove these in deconstructor
    // location
    std::vector<b2JointId> joints;
    float motor_speed;
    float motor_torque;
}; 










#endif