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
		.category(2)
		.mask(65525)
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

	auto vel = velocity();
	
	if (vel.y < 0 && vel.y > -3.0)
	{
		vel.y = -3.0f;
	}
	if (vel.y >= 0 && vel.y < 3.0)
	{
		vel.y = 3.0f;
	}
	
	vel = normalise(vel);
	vel *= 8.0f;
	velocity(vel);
}

void Ball::onCollision(GameObject *obj)
{
	int healthSpawn = 90;
	int ballSpawn = 70;
	int chance = rand() % 100 + 1;
	
	if (obj->m_tags.has("Brick")) 
	{
		//m_dead = true;		// kills itself
		obj->m_dead = true;	// kills the other object
		App::score += 10; //adds +10 to the score everytime a brick is broken
		auto sound = kage::SoundManager::playSound("data/NFF-soft-confirm.wav"); //plays a the sound effect
		sound -> setVolume(20); //turns down the VOLUME!
		
		if (chance > ballSpawn)
		{
			auto ball = kage::World::build<Ball>();
			ball->position(position());
			ball->velocity(5, 6);
		}

		if (chance > healthSpawn)
		{
			auto heart = kage::World::build<Heart>();
			heart->position(position());
			heart->velocity(0, 1);
			
		}


		
	}
	if (obj->m_tags.has("Paddle"))
	{
		auto sound = kage::SoundManager::playSound("data/NFF-soft-confirm.wav");
		sound->setVolume(20);
		sound->setPitch(1 + App::getRNG().norm());
	}
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
