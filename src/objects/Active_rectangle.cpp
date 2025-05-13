#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "objects/Active_rectangle.hpp"

Active_rectangle::Active_rectangle(b2Vec2 initial_position, float width, float height, float friction, float density, float scaling_factor, b2WorldId &worldId) :
    Shape(initial_position),
    width(width),
    height(height),
    square_visual(sf::RectangleShape(sf::Vector2f(width*scaling_factor, height*scaling_factor)))
{
    // Create the box body
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = initial_position;
    bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(width/2, height/2); // i think this is only temporarily needed
    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    // setup the visual side of the cube
    // again, one of those "I think this should work"
    square_visual.setFillColor(sf::Color(100, 100, 200));
    square_visual.setOrigin({scaling_factor*width/2.0f, scaling_factor*height/2.0f});
    update(scaling_factor);
}

void Active_rectangle::draw(sf::RenderWindow *window) const {
    window->draw(square_visual);
}

void Active_rectangle::update(float scaling_factor) {
    position = b2Body_GetPosition(bodyId);
    rotation = b2Body_GetRotation(bodyId);
    square_visual.setRotation(get_rotation());
    square_visual.setPosition(get_position() * scaling_factor);
}