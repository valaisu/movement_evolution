#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

//#include "objects/Active_box.hpp"
//#include "objects/Passive_box.hpp"
#include "Game.hpp"

#include "objects/Shape.hpp"
#include "objects/Passive_rectangle.hpp"
#include "objects/Active_rectangle.hpp"
#include "objects/Active_circle.hpp"
#include "objects/Active_capsule.hpp"
#include "agents/Dog.hpp"


int main() {

    // These maybe should be like main function params
    const float world_size_x_meters = 30;
    const float world_size_y_meters = 20;
    const float visual_scaling_factor = 30;
    const float fps = 60;
    const float gravity = 9.81f;

    Game game(
        world_size_x_meters * visual_scaling_factor, 
        world_size_y_meters * visual_scaling_factor, 
        fps, gravity, visual_scaling_factor);
    Passive_rectangle ground((b2Vec2){15.0f, 19.5f}, 22.0f, 1.0f, 0.2f, 1.0f, visual_scaling_factor, game.get_world_id());
    game.add_body(&ground);

    //std::vector<Active_rectangle*> active_bodies;
    std::vector<Shape*> shapes;
    for(int i = 0; i < 10; i++) {
        Active_rectangle* active_rectangle = new Active_rectangle((b2Vec2){10.0f - 0.1f*i, 10.0f + i}, 0.4f, 0.4f, 0.3f, 1.0f, visual_scaling_factor, game.get_world_id());
        shapes.push_back(active_rectangle);
        game.add_body(active_rectangle);
    }

    //Active_rectangle* active_rectangle = new Active_rectangle((b2Vec2){12.0f, 12.0f}, 2.0f, 2.0f, 0.3f, 1.0f, visual_scaling_factor, game.get_world_id());
    //shapes.push_back(active_rectangle);
    //game.add_body(active_rectangle);

    // Try adding a capsule
    Active_capsule* capsule = new Active_capsule((b2Vec2){13.0f, 13.0f}, (b2Vec2){14.0f, 14.0f}, 0.5f, 0.3f, 1.0f, visual_scaling_factor, game.get_world_id());
    shapes.push_back(capsule);
    game.add_body(capsule);


    // lets try to create a simple pendulum
    // create 2 bodies
    Passive_rectangle pendulum_base((b2Vec2){15.0f, 10.0f}, 1.0f, 1.0f, 0.3f, 1.0f, visual_scaling_factor, game.get_world_id());
    game.add_body(&pendulum_base);

    Active_rectangle* pendulum = new Active_rectangle((b2Vec2){23.0f, 10.0f}, 0.4f, 0.4f, 0.3f, 1.0f, visual_scaling_factor, game.get_world_id());
    shapes.push_back(pendulum);
    game.add_body(pendulum);
    
    // try to connect them
    b2Vec2 pivot = {15.0f, 10.0f};
    b2RevoluteJointDef jointDef = b2DefaultRevoluteJointDef();
    jointDef.bodyIdA = pendulum_base.get_body_id();
    jointDef.bodyIdB = pendulum->get_body_id();
    jointDef.localAnchorA = b2Body_GetLocalPoint(pendulum_base.get_body_id(), pivot);
    jointDef.localAnchorB = b2Body_GetLocalPoint(pendulum->get_body_id(), pivot);

    b2JointId m_jointId1 = b2CreateRevoluteJoint( game.get_world_id(), &jointDef );



    Dog* doge = new Dog((b2Vec2){16.5f, 13.6f}, 1.0f, 1.0f, 2.5f, 0.3f, 0.4f, visual_scaling_factor, &game);
    game.add_agent(doge);

/*

		m_enableSpring = false;
		m_enableLimit = true;
		m_enableMotor = false;
		m_hertz = 1.0f;
		m_dampingRatio = 0.5f;
		m_motorSpeed = 1.0f;
		m_motorTorque = 1000.0f;

		{
			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.type = b2_dynamicBody;
			bodyDef.position = { -10.0f, 20.0f };
			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );

			b2ShapeDef shapeDef = b2DefaultShapeDef();
			shapeDef.density = 1.0f;

			b2Capsule capsule = { { 0.0f, -1.0f }, { 0.0f, 6.0f }, 0.5f };
			b2CreateCapsuleShape( bodyId, &shapeDef, &capsule );

			b2Vec2 pivot = { -10.0f, 20.5f };
			b2RevoluteJointDef jointDef = b2DefaultRevoluteJointDef();
			jointDef.bodyIdA = groundId;
			jointDef.bodyIdB = bodyId;
			jointDef.localAnchorA = b2Body_GetLocalPoint( jointDef.bodyIdA, pivot );
			jointDef.localAnchorB = b2Body_GetLocalPoint( jointDef.bodyIdB, pivot );
			jointDef.enableSpring = m_enableSpring;
			jointDef.hertz = m_hertz;
			jointDef.dampingRatio = m_dampingRatio;
			jointDef.motorSpeed = m_motorSpeed;
			jointDef.maxMotorTorque = m_motorTorque;
			jointDef.enableMotor = m_enableMotor;
			jointDef.referenceAngle = 0.5f * B2_PI;
			jointDef.lowerAngle = -0.5f * B2_PI;
			jointDef.upperAngle = 0.75f * B2_PI;
			jointDef.enableLimit = m_enableLimit;

			m_jointId1 = b2CreateRevoluteJoint( m_worldId, &jointDef );
		}
*/





    sf::Clock clock;
    float timeStep = 1.0f / 60.0f;

    while (game.window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = game.window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                game.window.close();
        }
        game.progress_simulation();
        game.draw();
        game.display();
        
        // try to keep the correct fps
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() < timeStep) {
            sf::sleep(sf::seconds(timeStep - elapsed.asSeconds()));
        }
        clock.restart();
    }



    b2DestroyWorld(game.get_world_id());
    return 0;
}
