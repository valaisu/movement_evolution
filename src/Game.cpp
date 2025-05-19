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

b2WorldId& Game::get_world_id() {
    return worldId;
}

float Game::get_visual_scaling_factor() {
    return visual_scaling_factor;
}

void Game::progress_simulation() {
    b2World_Step(worldId, timestep, 4); // i dont think substep count needs to be controllable
    for (auto obj : shapes) {
        obj->update(visual_scaling_factor);
    }
}

void Game::draw() {
    window.clear(sf::Color::White);
    //std::cout<<"here"<<std::endl;
    for (auto obj : shapes) {
        obj->draw(&window);
    }
}

void Game::display() {
    window.display();
}
