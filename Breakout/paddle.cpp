#include "Paddle.h"
#include "app.h"

Paddle::Paddle()
{
	m_sprite = kage::TextureManager::getSprite("data/paddle.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Paddle");

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.type(b2BodyType::b2_kinematicBody)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();

	// Make a fixture (collision shape) for the body
	kage::Physics::BoxBuilder()
		.size(4, 0.5)
		.mass(1)
		.category(1)
		.mask(65535)
		.build(m_body); // We need to tell the builder which body to attach to
}

Paddle::~Paddle()
{

}

void Paddle::update(float deltaT)
{
	// Do logic here
	velocity(0, 0);
	if (kage::Input::isKeyDown(sf::Keyboard::Left))
	{
		velocity(-8, 0);
	}
	if (kage::Input::isKeyDown(sf::Keyboard::Right))
	{
		velocity(8, 0);
	}

	auto pos = position();

	pos.x = kage::Input::getMousePosition(App::getWindow()).x;

	if (pos.x < 2)
	{
		pos.x = 2;
	}
	if (pos.x > 28)
	{
		pos.x = 28;
	}

	position(pos);

}

void Paddle::onCollision(GameObject *obj)
{
	if (obj->m_tags.has("Ball"))
	{
		auto vel = obj -> velocity();
		float difference = obj->position().x - position().x;
		vel.x += difference * 2;
		obj -> velocity(vel);
	}
}

void Paddle::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void Paddle::onCollisionStop(GameObject* obj)
//{
//}

//void Paddle::onCollisionStop(b2Fixture* fix)
//{
//}

//void Paddle::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
