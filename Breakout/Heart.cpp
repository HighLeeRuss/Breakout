#include "Heart.h"
#include "app.h"

Heart::Heart()
{
	m_sprite = kage::TextureManager::getSprite("data/droplet2.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Heart");

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();

	// Make a fixture (collision shape) for the body
	kage::Physics::CircleBuilder()
		.radius(0.4f)
		.mass(1)
		.category(8)
		.mask(65521)
		.build(m_body); // We need to tell the builder which body to attach to
}

Heart::~Heart()
{

}

void Heart::update(float deltaT)
{
	// Do logic here
}

void Heart::onCollision(GameObject *obj)
{
	if (obj->m_tags.has("Paddle"))
	{
		m_dead = true;		// kills itself
		App::lives += 1;
		if (App::lives > 5)
		{
			App::lives = 5;
		}
	}
}

void Heart::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void Heart::onCollisionStop(GameObject* obj)
//{
//}

//void Heart::onCollisionStop(b2Fixture* fix)
//{
//}

//void Heart::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
