#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "objects/Shape.hpp"

Shape::Shape(b2Vec2 initial_position) :
    position(initial_position), 
    rotation((b2Rot){0.0f}) {}


void Shape::draw(sf::RenderWindow *window) const {}

float Shape::get_x_coord() {
    return position.x;
}

float Shape::get_y_coord() {
    return position.y;
}

sf::Vector2f Shape::get_position() {
    return sf::Vector2f(position.x, position.y);
}

sf::Angle Shape::get_rotation() {
    float radians = b2Rot_GetAngle(rotation);
    sf::Angle angle = sf::radians(radians);
    return angle;
}

b2BodyId Shape::get_body_id() {
    return bodyId;
}

Shape::~Shape() {}