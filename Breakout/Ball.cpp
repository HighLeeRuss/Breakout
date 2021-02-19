#include "Ball.h"
#include "app.h"

Ball::Ball()
{
	m_sprite = kage::TextureManager::getSprite("data/ball.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Ball");

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();

	m_body->SetGravityScale(0);

	// Make a fixture (collision shape) for the body
	kage::Physics::CircleBuilder()
		.radius(0.4f)
		.mass(1)
		.restitution(1)
		.build(m_body); // We need to tell the builder which body to attach to
}

Ball::~Ball()
{

}

void Ball::update(float deltaT)
{
	// Do logic here
	if (position().y > 16.875)
	{
		m_dead = true;
	}
}

void Ball::onCollision(GameObject *obj)
{
	if (obj->m_tags.has("Brick")) 
	//{
		//m_dead = true;		// kills itself
		obj->m_dead = true;	// kills the other object
	//}
}

void Ball::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void Ball::onCollisionStop(GameObject* obj)
//{
//}

//void Ball::onCollisionStop(b2Fixture* fix)
//{
//}

//void Ball::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
