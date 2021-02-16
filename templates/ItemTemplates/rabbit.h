#pragma once
#include "kage/gameobject.h"

class $safeitemname$ : public kage::GameObject
{
public:
	$safeitemname$();
	~$safeitemname$();

	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);

#pragma region Optional
	//void render(sf::RenderTarget& rt);
	//void onCollisionStop(GameObject* obj);
	//void onCollisionStop(b2Fixture* fix);
#pragma endregion
};
