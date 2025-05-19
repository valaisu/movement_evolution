#ifndef PASSIVE_SHAPE_HPP
#define PASSIVE_SHAPE_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Shape.hpp" 


//TODO: later, use templates and lambdas, useful skill to have
// there maybe should be a distinction between a dynamic and static boxes
// maybe use polymorphism, or just hardcode the ground

class Passive_rectangle : public Shape {
public:
    Passive_rectangle(b2Vec2 initial_position, float width, float height, float friction, float density, float visual_scaling_factor, b2WorldId &worldId);
    void update(float visual_scaling_factor) override; // literally does nothing
    void draw(sf::RenderWindow *window) const override;

private:
    float width;
    float height;
    sf::RectangleShape square_visual;

};

#endif
