#ifndef ACTIVE_CAPSULE_HPP
#define ACTIVE_CAPSULE_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Shape.hpp" 



class Active_capsule : public Shape {
public:
    Active_capsule(b2Vec2 center_1, b2Vec2 center_2, float radius, float friction, float density, float visual_scaling_factor, b2WorldId &worldId);
    void update(float visual_scaling_factor) override;
    void draw(sf::RenderWindow *window) const override;

private:
    float width;
    float radius;
    float base_angle;
    // The center of this shape is at the center of the central rectangle 
    sf::RectangleShape rectangle_visual;
    sf::CircleShape circle_visual_1;
    sf::CircleShape circle_visual_2;

};

#endif
