#pragma once
#include "kage/gameobject.h"

class myGameObject : public kage::GameObject
{
public:
	myGameObject();
	~myGameObject();

	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);

#pragma region Optional
	//void render(sf::RenderTarget& rt);
	//void onCollisionStop(GameObject* obj);
	//void onCollisionStop(b2Fixture* fix);
#pragma endregion
};
