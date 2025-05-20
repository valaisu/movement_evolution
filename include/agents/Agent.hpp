// Agent is the base class for controllable 
// agents such as dog and car

#ifndef AGENT_HPP
#define AGENT_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "objects/Shape.hpp"
#include "objects/Passive_rectangle.hpp"
#include "objects/Active_rectangle.hpp"

// the constructor defines what the body looks like, takes some work

class Agent{
public:
    virtual void update(float time_step) = 0;
protected:
    Agent(b2Vec2 initial_position);
    virtual ~Agent();
    
    std::vector<Shape*> body_parts;
    b2Vec2 location;
private:
    // I probably need a list of the body parts so that they can
    // be updated based on the user controls
};










#endif