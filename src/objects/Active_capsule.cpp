#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "objects/Active_capsule.hpp"

Active_capsule::Active_capsule(b2Vec2 center_1, b2Vec2 center_2, float radius, float friction, float density, float scaling_factor, b2WorldId &worldId) :
    Shape(center_1),
    radius(radius)
{
    // Create the box body
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = center_1; // This could be wrong
    bodyId = b2CreateBody(worldId, &bodyDef);
    b2Capsule dynamic_capsule;
    dynamic_capsule.center1 = center_1;
    dynamic_capsule.center2 = center_2;
    dynamic_capsule.radius = radius;

    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    b2CreateCapsuleShape(bodyId, &shapeDef, &dynamic_capsule);

    // setup the visual side of the cube
    // again, one of those "I think this should work"
    float height = scaling_factor * radius*2;
    width = scaling_factor * sqrt(pow(center_1.x - center_2.x, 2) + pow(center_1.y - center_2.y, 2));
    rectangle_visual = sf::RectangleShape(sf::Vector2f(width*scaling_factor, height*scaling_factor));
    circle_visual_1 = sf::CircleShape(radius*scaling_factor);
    circle_visual_2 = sf::CircleShape(radius*scaling_factor);
    rectangle_visual.setFillColor(sf::Color(100, 100, 200));
    circle_visual_1.setFillColor(sf::Color(100, 100, 200));
    circle_visual_2.setFillColor(sf::Color(100, 100, 200));

    rectangle_visual.setOrigin({(center_1.x+center_2.x)*scaling_factor/2.0f, (center_1.y+center_2.y)*scaling_factor/2.0f});
    circle_visual_1.setOrigin({center_1.x, center_1.y});
    circle_visual_2.setOrigin({center_2.x, center_2.y});

    update(scaling_factor);
}

void Active_capsule::draw(sf::RenderWindow *window) const {
    window->draw(rectangle_visual);
    window->draw(circle_visual_1);
    window->draw(circle_visual_2);
}

void Active_capsule::update(float scaling_factor) {
    position = b2Body_GetPosition(bodyId); // I hope this also is based on the center
    rotation = b2Body_GetRotation(bodyId);
    rectangle_visual.setRotation(get_rotation());
    rectangle_visual.setPosition(get_position() * scaling_factor);
    
    // then the part that takes some brain work, ie. updating the circle locations
    float x_delta = std::cos(b2Rot_GetAngle(rotation)) * scaling_factor * width;
    float y_delta = std::cos(b2Rot_GetAngle(rotation)) * scaling_factor * radius;
    sf::Vector2 delta_1 = {x_delta, y_delta};
    sf::Vector2 delta_2 = {-x_delta, -y_delta};
    circle_visual_1.setPosition((get_position()+delta_1) * scaling_factor);
    circle_visual_2.setPosition((get_position()+delta_2) * scaling_factor);

}