#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "objects/Passive_rectangle.hpp"

Passive_rectangle::Passive_rectangle(b2Vec2 initial_position, float width, float height, float friction, float density, float scaling_factor, b2WorldId &worldId) :
    Shape(initial_position),
    width(width),
    height(height),
    square_visual(sf::RectangleShape(sf::Vector2f(width*scaling_factor, height*scaling_factor)))
{
    // Create the box body
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    bodyDef.position = initial_position;
    bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon staticBox = b2MakeBox(width/2, height/2);
    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &staticBox);

    // setup the visual side of the cube
    // again, one of those "I think this should work"
    square_visual.setFillColor(sf::Color(100, 100, 100));
    square_visual.setOrigin({scaling_factor*width/2.0f, scaling_factor*height/2.0f});
    square_visual.setPosition(
        sf::Vector2f(
            (initial_position.x)*scaling_factor, 
            (initial_position.y)*scaling_factor));
    std::cout<< initial_position.x*scaling_factor << " " << initial_position.y*scaling_factor << std::endl;
}

void Passive_rectangle::draw(sf::RenderWindow *window) const {
    window->draw(square_visual);
}

// just here so update can be called for all shapes
void Passive_rectangle::update(float scaling_factor) {}