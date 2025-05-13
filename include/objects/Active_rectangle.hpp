#ifndef ACTIVE_RECTANGLE_HPP
#define ACTIVE_RECTANGLE_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Shape.hpp" 



class Active_rectangle : public Shape {
public:
    Active_rectangle(b2Vec2 initial_position, float width, float height, float friction, float density, float scaling_factor, b2WorldId &worldId);
    void update(float scaling_factor) override;
    void draw(sf::RenderWindow *window) const override;

private:

    float width;
    float height;
    sf::RectangleShape square_visual;

};

#endif
