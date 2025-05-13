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

// the constructor defines what the body looks like, takes some work

/* class Dog : public Agent{
public:
    Dog(float lower_leg_length, float upper_leg_length, float body_length);
    void update(float time_step);
private:
    std::vector<Shape*> body_parts;
    // I probably need a list of the body parts so that they can
    // be updated based on the user controls
}; */










#endif