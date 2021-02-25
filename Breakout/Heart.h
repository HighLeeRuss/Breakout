#pragma once
#include "kage/gameobject.h"

class Heart : public kage::GameObject
{
public:
	Heart();
	~Heart();

	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);

#pragma region Optional
	//void render(sf::RenderTarget& rt);
	//void onCollisionStop(GameObject* obj);
	//void onCollisionStop(b2Fixture* fix);
#pragma endregion
};
