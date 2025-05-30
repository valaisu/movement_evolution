#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "objects/Active_circle.hpp"

Active_circle::Active_circle(b2Vec2 initial_position, float radius, float friction, float density, float visual_scaling_factor, b2WorldId &worldId) :
    Shape(initial_position),
    radius(radius),
    circle_visual(sf::CircleShape(radius*visual_scaling_factor, 16))
    //square_visual(sf::RectangleShape(sf::Vector2f(width*visual_scaling_factor, height*visual_scaling_factor)))
{
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = initial_position;
    bodyId = b2CreateBody(worldId, &bodyDef);

    // define physical characteristics
    b2Circle dynamic_circle;
    dynamic_circle.center = {0.0f, 0.0f};
    dynamic_circle.radius = radius;
    // TODO: rolling friction?

    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    b2CreateCircleShape(bodyId, &shapeDef, &dynamic_circle);

    // Define visuals
    circle_visual.setFillColor(sf::Color(100, 100, 200));
    circle_visual.setOrigin({visual_scaling_factor*radius, visual_scaling_factor*radius});
    update(visual_scaling_factor);
}

void Active_circle::draw(sf::RenderWindow *window) const {
    window->draw(circle_visual);
}

void Active_circle::update(float visual_scaling_factor) {
    position = b2Body_GetPosition(bodyId);
    rotation = b2Body_GetRotation(bodyId);
    circle_visual.setRotation(get_rotation()); // is this stupid? maybe, oh well
    circle_visual.setPosition(get_position() * visual_scaling_factor);
}