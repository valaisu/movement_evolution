

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "agents/Agent.hpp"

#include "objects/Shape.hpp"
#include "objects/Passive_rectangle.hpp"
#include "objects/Active_rectangle.hpp"




Agent::Agent(b2Vec2 initial_position) :
    location(initial_position) {}


Agent::~Agent() {}

