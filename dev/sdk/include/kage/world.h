////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_WORLD_HEADER
#define KAGE_WORLD_HEADER
#include "kf/kf_vector.h"
#include <SFML/Graphics.hpp>
//#include "box2d\Box2D.h"


namespace kage
{
	class GameObject;

	namespace World
	{
		// Game objects
		long long newID();
		void add(GameObject* obj);
		void remove(GameObject* obj);
		void remove(std::string tag);
		template<typename T> T* build()
		{
			GameObject* obj = new T;
			obj->m_id = newID();
			add(obj);
			return (T*)obj;
		}

		// Queries
		GameObject* findByID(long long id);
		GameObject* findByTag(std::string tag);
		std::vector<GameObject*> findAllByTag(std::string tag);
		std::map<long long, GameObject*>& getWorldObjects();

		// View
		void setView(sf::RenderTarget& rt, kf::Vec2 centre, float zoom);
		void setView(sf::RenderTarget& rt);
		void setViewFitWidth(sf::RenderTarget& rt, kf::Vec2 pos, float width, bool isCentre = true);
		void setViewFitHeight(sf::RenderTarget& rt, kf::Vec2 pos, float height, bool isCentre = true);
		void setViewFitAll(sf::RenderTarget& rt, kf::Vec2 pos, float width, float height, bool isCentre = true);

		// World
		void update(float dt);
		void render(sf::RenderTarget& rt);
		void clear();
		float scale();	// Get the scaling factor between the physics engine and the renderer.
		void scale(float s); // Set the scaling factor between the physics engine and the renderer.
		void pause(bool p);
		bool pause();

		// Debug
		void inspector(sf::RenderTarget* rt = 0);
		void debugGrid(sf::RenderTarget& rt);
	}
}

#endif