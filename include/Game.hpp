#ifndef GAME_HPP
#define GAME_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "objects/Shape.hpp"
#include "objects/Passive_rectangle.hpp"
#include "objects/Active_rectangle.hpp"
#include "objects/Active_capsule.hpp"
#include "agents/Agent.hpp"

class Game {
public:
    Game(uint16_t window_h, uint16_t window_w, float fps, float gravity, float visual_scaling_factor);

    sf::RenderWindow window;
    void add_body(Shape *shape);
    void add_agent(Agent *agent);
    b2WorldId& get_world_id();

    float get_visual_scaling_factor();
    void progress_simulation();
    void draw(sf::Vector2f center);
    void display();

private:
    b2WorldDef worldDef;
    b2WorldId worldId;
    const float fps = 60.0f;
    const float timestep;
    const float window_w;
    const float window_h;
    const float visual_scaling_factor;
    std::vector<Shape*> shapes;
    std::vector<Agent*> agents;    
};


#endif

