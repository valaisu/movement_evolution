#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "agents/Agent.hpp"
#include "agents/Car.hpp"
#include "objects/Shape.hpp"
#include "objects/Active_rectangle.hpp"
#include "objects/Active_circle.hpp"
#include "Game.hpp"




Car::Car(b2Vec2 initial_position, float car_width, float car_height, float wheel_radius, float visual_scaling_factor, Game *game)
    : Agent(initial_position) 
{
    // TODO: define better
    motor_torque = 100.0f;
    motor_speed = 10.0f * B2_PI;

    // Initial position = where back wheel touches ground?
    b2Vec2 diff_wheel_b = {car_width * 1.0f/5.0f, -wheel_radius};
    b2Vec2 diff_wheel_f = {car_width * 4.0f/5.0f, -wheel_radius};
    b2Vec2 diff_body = {car_width/2.0f, -(car_height/2.0f + wheel_radius)};

    car_body = new Active_rectangle(initial_position + diff_body, car_width, car_height, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    back_wheel = new Active_circle(initial_position + diff_wheel_b, wheel_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    front_wheel = new Active_circle(initial_position + diff_wheel_f, wheel_radius, 0.3f, 1.0f, visual_scaling_factor, game->get_world_id());
    body_parts.push_back(car_body);
    body_parts.push_back(back_wheel);
    body_parts.push_back(front_wheel);

    b2Vec2 axis = { 0.0f, 1.0f }; // Suspension direction?

    // back wheel
    b2Vec2 pivot_b = b2Body_GetPosition(back_wheel->get_body_id());

    b2WheelJointDef jointDef_b = b2DefaultWheelJointDef();
    jointDef_b.bodyIdA = car_body->get_body_id();
    jointDef_b.bodyIdB = back_wheel->get_body_id();
    jointDef_b.localAxisA = b2Body_GetLocalVector(jointDef_b.bodyIdA, axis);
	jointDef_b.localAnchorA = b2Body_GetLocalPoint(jointDef_b.bodyIdA, pivot_b);
	jointDef_b.localAnchorB = b2Body_GetLocalPoint(jointDef_b.bodyIdB, pivot_b);
    jointDef_b.motorSpeed = motor_speed;
    jointDef_b.maxMotorTorque = 0.0f;
    jointDef_b.enableMotor = true;
    jointDef_b.hertz = 5.0f; // value from some example
    jointDef_b.dampingRatio = 0.7f;
    jointDef_b.lowerTranslation = -0.2f * wheel_radius;
    jointDef_b.upperTranslation = 0.2f * wheel_radius;
    jointDef_b.enableLimit = true;

    b2JointId rear_axle = b2CreateWheelJoint(game->get_world_id(), &jointDef_b);


    // front wheel
    b2Vec2 pivot_f = b2Body_GetPosition(front_wheel->get_body_id());

    b2WheelJointDef jointDef_f = b2DefaultWheelJointDef();
    jointDef_f.bodyIdA = car_body->get_body_id();
    jointDef_f.bodyIdB = front_wheel->get_body_id();
    jointDef_f.localAxisA = b2Body_GetLocalVector(jointDef_f.bodyIdA, axis);
	jointDef_f.localAnchorA = b2Body_GetLocalPoint(jointDef_f.bodyIdA, pivot_f);
	jointDef_f.localAnchorB = b2Body_GetLocalPoint(jointDef_f.bodyIdB, pivot_f);
    jointDef_f.motorSpeed = motor_speed;
    jointDef_f.maxMotorTorque = 0.0f;
    jointDef_f.enableMotor = true;
    jointDef_f.hertz = 5.0f; // value from some example
    jointDef_f.dampingRatio = 0.7f;
    jointDef_f.lowerTranslation = -0.2f * wheel_radius;
    jointDef_f.upperTranslation = 0.2f * wheel_radius;
    jointDef_f.enableLimit = true;

    b2JointId front_axle = b2CreateWheelJoint(game->get_world_id(), &jointDef_f);

    joints.push_back(rear_axle);
    joints.push_back(front_axle);


}

sf::Vector2f Car::get_location() {
    return car_body->get_position();
}


void Car::move_forward() {
    // wheels can also get stuck
    for (auto* wheel : body_parts) {
        if (wheel) {
            b2Body_SetAwake(wheel->get_body_id(), true);
        }
    }

    for (auto joint : joints) {
        b2WheelJoint_SetMaxMotorTorque(joint, motor_torque);
        b2WheelJoint_SetMotorSpeed(joint, motor_speed);
    }
}


void Car::move_reverse() {
    // wheels can also get stuck
    for (auto* wheel : body_parts) {
        if (wheel) {
            b2Body_SetAwake(wheel->get_body_id(), true);
        }
    }

    for (auto joint : joints) {
        b2WheelJoint_SetMaxMotorTorque(joint, motor_torque);
        b2WheelJoint_SetMotorSpeed(joint, -motor_speed);
    }
}

void Car::move_neutral() {
    for (auto joint : joints) {
        b2WheelJoint_SetMaxMotorTorque(joint, 0.0f);
        b2WheelJoint_SetMotorSpeed(joint, 0.0f);
    }
}


void Car::update(float visual_scaling_factor) {
    for (auto obj : body_parts) {
        obj->update(visual_scaling_factor);
    }
}

void Car::draw(sf::RenderWindow *window) const {
    for (auto obj : body_parts) {
        obj->draw(window);
    }
}



Car::~Car() {
    delete car_body;
    delete back_wheel;
    delete front_wheel;
}