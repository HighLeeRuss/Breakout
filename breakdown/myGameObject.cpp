#include "myGameObject.h"
#include "app.h"

myGameObject::myGameObject()
{
	m_sprite = kage::TextureManager::getSprite("data/zazaka.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("myGameObject");

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

myGameObject::~myGameObject()
{

}

void myGameObject::update(float deltaT)
{
	// Do logic here
}

void myGameObject::onCollision(GameObject *obj)
{
	//if (obj->m_tags.has("enemy"))
	//{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	//}
}

void myGameObject::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void myGameObject::onCollisionStop(GameObject* obj)
//{
//}

//void myGameObject::onCollisionStop(b2Fixture* fix)
//{
//}

//void myGameObject::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion