#include "$safeitemname$.h"
#include "app.h"

$safeitemname$::$safeitemname$()
{
	m_sprite = kage::TextureManager::getSprite("data/zazaka.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("$safeitemname$");

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();

	// Make a fixture (collision shape) for the body
	kage::Physics::CircleBuilder()
		.radius(0.4f)
		.mass(1)
		.build(m_body); // We need to tell the builder which body to attach to
}

$safeitemname$::~$safeitemname$()
{

}

void $safeitemname$::update(float deltaT)
{
	// Do logic here
}

void $safeitemname$::onCollision(GameObject *obj)
{
	//if (obj->m_tags.has("enemy"))
	//{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	//}
}

void $safeitemname$::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void $safeitemname$::onCollisionStop(GameObject* obj)
//{
//}

//void $safeitemname$::onCollisionStop(b2Fixture* fix)
//{
//}

//void $safeitemname$::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
