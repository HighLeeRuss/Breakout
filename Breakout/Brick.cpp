#include "Brick.h"
#include "app.h"

Brick::Brick()
{
	m_sprite = kage::TextureManager::getSprite("data/brick.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Brick");

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.type(b2BodyType::b2_staticBody)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();

	// Make a fixture (collision shape) for the body
	kage::Physics::BoxBuilder()
		.size(2, 1)
		.mass(1)
		.category(4)
		.mask(65527)
		.build(m_body); // We need to tell the builder which body to attach to
}

Brick::~Brick()
{

}

void Brick::update(float deltaT)
{
	// Do logic here
}

void Brick::onCollision(GameObject *obj)
{
	//if (obj->m_tags.has("enemy"))
	//{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	//}
}

void Brick::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void Brick::onCollisionStop(GameObject* obj)
//{
//}

//void Brick::onCollisionStop(b2Fixture* fix)
//{
//}

//void Brick::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
