#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "objects/Active_capsule.hpp"

Active_capsule::Active_capsule(b2Vec2 center_1, b2Vec2 center_2, float radius, float friction, float density, float visual_scaling_factor, b2WorldId &worldId) :
    Shape(center_1),
    radius(radius)
{
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = center_1;
    b2Vec2 diff = center_2 - center_1;
    // or
    //b2Vec2 midpoint = {
    //    (center_1.x + center_2.x) * 0.5f,
    //    (center_1.y + center_2.y) * 0.5f
    //};
    //bodyDef.position = midpoint;
    base_angle = b2Atan2(diff.y, diff.x);
    bodyDef.rotation = b2MakeRot(base_angle);
    bodyId = b2CreateBody(worldId, &bodyDef);
    
    b2Capsule dynamic_capsule;
    width = sqrt(diff.x * diff.x + diff.y * diff.y);
    dynamic_capsule.center1 = {-width * 0.5f, 0};
    dynamic_capsule.center2 = {width * 0.5f, 0};
    dynamic_capsule.radius = radius;
    
    shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.material.friction = friction;
    b2CreateCapsuleShape(bodyId, &shapeDef, &dynamic_capsule);
    
    rectangle_visual = sf::RectangleShape(sf::Vector2f(width*visual_scaling_factor, radius*2*visual_scaling_factor));
    circle_visual_1 = sf::CircleShape(radius*visual_scaling_factor);
    circle_visual_2 = sf::CircleShape(radius*visual_scaling_factor);
    
    rectangle_visual.setFillColor(sf::Color(100, 100, 200));
    rectangle_visual.setOrigin({width*visual_scaling_factor*0.5f, radius*visual_scaling_factor});
    circle_visual_1.setFillColor(sf::Color(100, 100, 200));
    circle_visual_1.setOrigin({radius*visual_scaling_factor, radius*visual_scaling_factor});
    circle_visual_2.setFillColor(sf::Color(100, 100, 200));
    circle_visual_2.setOrigin({radius*visual_scaling_factor, radius*visual_scaling_factor});
    
    update(visual_scaling_factor);
}

void Active_capsule::draw(sf::RenderWindow *window) const {
    window->draw(rectangle_visual);
    window->draw(circle_visual_1);
    window->draw(circle_visual_2);
}

void Active_capsule::update(float visual_scaling_factor) {
    position = b2Body_GetPosition(bodyId);
    rotation = b2Body_GetRotation(bodyId);
    float angle = b2Rot_GetAngle(rotation);
    
    rectangle_visual.setRotation(get_rotation());
    rectangle_visual.setPosition(get_position() * visual_scaling_factor);
    
    float x_delta = cosf(angle) * (width * 0.5f);
    float y_delta = sinf(angle) * (width * 0.5f);
    
    circle_visual_1.setPosition({
        (position.x + x_delta) * visual_scaling_factor,
        (position.y + y_delta) * visual_scaling_factor
    });
    
    circle_visual_2.setPosition({
        (position.x - x_delta) * visual_scaling_factor,
        (position.y - y_delta) * visual_scaling_factor
    });
}