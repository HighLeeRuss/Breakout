////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_GAMEOBJECT_HEADER
#define KAGE_GAMEOBJECT_HEADER
#include "kf/kf_vector.h"
#include <SFML/Graphics.hpp>
#include "box2d\Box2D.h"
#include "world.h"
#include "kf/kf_euler.h"
#include "kf/kf_tags.h"

namespace kage
{
	class GameObject
	{
	private:
		kf::Vec2 m_position;
		kf::Vec2 m_velocity;
		kf::Vec2 m_force;
		kf::Euler m_rotation;

	public:
		float m_life = 0;
		bool m_dead = false;
		long long m_id;
		sf::Sprite *m_sprite = 0;
		b2Body *m_body = 0;
		int m_order = 0;
		kf::Tags m_tags;
		std::vector<std::pair<std::string, int*>> m_propertiesInt;
		std::vector<std::pair<std::string, float*>> m_propertiesFloat;
		std::vector<std::pair<std::string, bool*>> m_propertiesBool;

		GameObject();
		virtual ~GameObject();
		virtual void preUpdate(float dt);
		virtual void update(float dt);
		virtual void render(sf::RenderTarget &rt);
		virtual void onCollision(GameObject *obj);
		virtual void onCollision(b2Fixture *fix);
		virtual void onCollisionStop(GameObject* obj);
		virtual void onCollisionStop(b2Fixture* fix);
		virtual GameObject &position(const kf::Vec2 &pos);
		virtual GameObject &velocity(const kf::Vec2 &vel);
		virtual GameObject &position(float x, float y);
		virtual GameObject &velocity(float x, float y);
		virtual GameObject& rotationDeg(float angle);
		virtual GameObject& rotationRad(float angle);
		virtual kf::Vec2 position();
		virtual kf::Vec2 velocity();
		virtual float rotationDeg();
		virtual float rotationRad();
		virtual GameObject &addForce(const kf::Vec2& force, const kf::Vec2 offset = { 0.0f, 0.0f });
		virtual GameObject &addForce(float x, float y, float offsetx=0, float offsety=0);
		virtual GameObject &addImpulse(const kf::Vec2 &force, const kf::Vec2 offset = { 0.0f, 0.0f });
		virtual GameObject &addImpulse(float x, float y, float offsetx = 0, float offsety = 0);
		virtual GameObject &addTorque(float torque);
		virtual GameObject &addTorqueImpulse(float torque);
		static GameObject *build();
		void property(const std::string& name, int &p);
		void property(const std::string& name, float &p);
		void property(const std::string& name, bool &p);
		void addTag(const std::string& tag);
		bool hasTag(const std::string& tag);
		void removeTag(const std::string& tag);
		std::vector<std::string> allTags();
	};
}

#endif