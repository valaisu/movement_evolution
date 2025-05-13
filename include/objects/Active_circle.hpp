#ifndef ACTIVE_CIRCLE_HPP
#define ACTIVE_CIRCLE_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Shape.hpp" 



class Active_circle : public Shape {
public:
    Active_circle(b2Vec2 initial_position, float radius, float friction, float density, float scaling_factor, b2WorldId &worldId);
    void update(float scaling_factor) override;
    void draw(sf::RenderWindow *window) const override;

private:

    float radius;
    sf::CircleShape circle_visual;

};

#endif
