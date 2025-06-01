#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"

#include "objects/Shape.hpp"
#include "objects/Passive_rectangle.hpp"
#include "objects/Active_rectangle.hpp"

Game::Game(uint16_t window_w, uint16_t window_h, float fps, float gravity, float visual_scaling_factor) :
    window_w(window_w),
    window_h(window_h),
    visual_scaling_factor(visual_scaling_factor),
    fps(fps), 
    timestep(1.0f/fps), 
    window(sf::VideoMode({window_w, window_h}), "Learn to run")
{
    worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, gravity};  // small gravity pointing to negative y
    worldId = b2CreateWorld(&worldDef);
};


void Game::add_body(Shape *shape) {
    shapes.push_back(shape);
}

void Game::add_agent(Agent *agent) {
    agents.push_back(agent);
}

b2WorldId& Game::get_world_id() {
    return worldId;
}

float Game::get_visual_scaling_factor() {
    return visual_scaling_factor;
}

// It would probs be better to do this with a smart pointer, but lets not focus on that now
Passive_rectangle Game::generate_terrain(float width, float ground_level) {
    Passive_rectangle ground((b2Vec2){world_generation_edge+width/2.0f, ground_level}, width, 1.0f, 0.3f, 1.0f, visual_scaling_factor, get_world_id());
    world_generation_edge += width;
    //std::cout << "Edge now at x=" << world_generation_edge << std::endl;
    return ground;
}

bool Game::terrain_edge_visible(float screen_center_x, float margin) {
    //std::cout << "Agent x=" << screen_center_x + margin + window_w/(2.0f*visual_scaling_factor) << std::endl;
    return screen_center_x + margin + window_w/(2.0f*visual_scaling_factor) > world_generation_edge;
}

void Game::progress_simulation() {
    b2World_Step(worldId, timestep, 4); // i dont think substep count needs to be controllable
    for (auto obj : shapes) {
        obj->update(visual_scaling_factor);
    }
    for (auto obj : agents) {
        obj->update(visual_scaling_factor);
    }
}

void Game::draw(sf::Vector2f center) {
    window.clear(sf::Color::White);

    // should move the camera
    sf::View view = window.getDefaultView();
    //std::cout << center.x << " " << center.y << std::endl;
    view.setCenter(center);
    window.setView(view);

    //std::cout<<"here"<<std::endl;
    for (auto obj : shapes) {
        obj->draw(&window);
    }    
    for (auto obj : agents) {
        obj->draw(&window);
    }
}

void Game::display() {
    window.display();
}
