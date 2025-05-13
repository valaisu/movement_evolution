#ifndef ACTIVE_BOX_HPP
#define ACTIVE_BOX_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>


//TODO: later, use templates and lambdas, useful skill to have
// there maybe should be a distinction between a dynamic and static boxes
// maybe use polymorphism, or just hardcode the ground

class Shape {
public:
    float get_x_coord();
    float get_y_coord();
    sf::Vector2f get_position();
    sf::Angle get_rotation();
    virtual void draw(sf::RenderWindow *window) const = 0;
    virtual void update(float scaling_factor) = 0;
    //void update(float scaling_factor); // passives dont need this
    b2BodyId get_body_id();
    
protected:
    virtual ~Shape();
    Shape(b2Vec2 initial_position);

    b2Vec2 position;
    b2Rot rotation;
    //float width;
    //float height;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2ShapeDef shapeDef;
    //sf::RectangleShape square_visual;
};

#endif
