////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////
 
#include "kage/gameobject.h"

#pragma warning(disable: 4100)

namespace kage
{
	void GameObject::preUpdate(float dt)
	{
		if (m_life > 0)
		{
			m_life -= dt;
			if (m_life <= 0)
			{
				m_dead = true;
				return;
			}
		}
		if (m_body)
			{
				m_position.set(m_body->GetPosition().x, m_body->GetPosition().y);
				m_rotation = m_body->GetAngle();
			}
	}

	void GameObject::update(float dt)
	{
	}

	void GameObject::render(sf::RenderTarget &rt)
	{
		if(m_sprite)
		{
			m_sprite->setPosition(m_position.x * kage::World::scale(), m_position.y * kage::World::scale());
			m_sprite->setRotation(m_rotation.degrees());
			rt.draw(*m_sprite);
		}
	}

	GameObject::GameObject()
	{
		m_life = 0;
		m_dead = false;
		m_position.set(0,0);
		m_velocity.set(0,0);
		m_force.set(0,0);
		m_sprite = 0;
		m_id = 0;
		m_body = 0;
		m_rotation = 0;
		m_order = 0;
	}

	GameObject::~GameObject()
	{
		if(m_body)
		{
			m_body->GetWorld()->DestroyBody(m_body);
			m_body = 0;
		}
		//World::remove(this);
		delete m_sprite;
		m_sprite = 0;
	}

	GameObject *GameObject::build()
	{
		return new GameObject;
	}

	GameObject &GameObject::position(float x, float y)
	{
		return position(kf::Vec2(x, y));
	}

	GameObject &GameObject::position(const kf::Vec2&pos)
	{
		m_position = pos;
		if (m_body)
		{
			m_body->SetTransform(m_position, m_body->GetAngle());// m_rotation.radians());
		}
		return *this;
	}

	GameObject &GameObject::velocity(float x, float y)
	{
		return velocity(kf::Vec2(x, y));
	}

	GameObject &GameObject::velocity(const kf::Vec2&vel)
	{
		m_velocity = vel;
		if (m_body)
		{
			m_body->SetLinearVelocity(m_velocity);
		}
		return *this;
	}

	GameObject& GameObject::rotationDeg(float angle)
	{
		m_rotation.degrees(angle);
		if (m_body)
		{
			m_body->SetTransform(m_body->GetPosition(), m_rotation.radians());
		}
		return *this;
	}

	GameObject& GameObject::rotationRad(float angle)
	{
		m_rotation.radians(angle);
		if (m_body)
		{
			m_body->SetTransform(m_body->GetPosition(), m_rotation.radians());
		}
		return *this;
	}

	GameObject &GameObject::addForce(float x, float y, float offsetx, float offsety)
	{
		return addForce(kf::Vec2(x, y), kf::Vec2(offsetx, offsety));
	}

	GameObject &GameObject::addForce(const kf::Vec2& force, const kf::Vec2 offset)
	{
		if (m_body)
		{
			m_body->ApplyForce(force, offset, true);
		}
		return *this;
	}

	GameObject& GameObject::addImpulse(float x, float y, float offsetx, float offsety)
	{
		return addImpulse(kf::Vec2(x, y), kf::Vec2(offsetx, offsety));
		
	}

	GameObject& GameObject::addTorque(float torque)
	{
		if (m_body)
		{
			m_body->ApplyTorque(torque, true);
		}
		return *this;
	}

	GameObject& GameObject::addTorqueImpulse(float torque)
	{
		if (m_body)
		{
			m_body->ApplyAngularImpulse(torque, true);
		}
		return *this;
	}

	GameObject& GameObject::addImpulse(const kf::Vec2& force, const kf::Vec2 offset)
	{
		if (m_body)
		{
			m_body->ApplyLinearImpulse(force, offset, true);
		}
		return *this;
	}

	

	kf::Vec2 GameObject::position()
	{
		if (m_body)
		{
			return m_body->GetTransform().p;
		}
		return m_position;
	}

	kf::Vec2 GameObject::velocity()
	{
		if (m_body)
		{
			return m_body->GetLinearVelocity();
		}
		return m_velocity;
	}

	float GameObject::rotationDeg()
	{
		if (m_body)
		{
			m_rotation.radians(m_body->GetAngle());
		}
		return m_rotation.degrees();
	}

	float GameObject::rotationRad()
	{
		if (m_body)
		{
			m_rotation.radians(m_body->GetAngle());
		}
		return m_rotation.radians();
	}

	void GameObject::onCollision(GameObject *obj)
	{
	}

	void GameObject::onCollision(b2Fixture *fix)
	{
	}

	void GameObject::onCollisionStop(GameObject* obj)
	{
	}

	void GameObject::onCollisionStop(b2Fixture* fix)
	{
	}


	void GameObject::property(const std::string& name, int &p)
	{
		m_propertiesInt.push_back(std::pair<std::string, int*>(name, &p));
	}

	void GameObject::property(const std::string& name, float &p)
	{
		m_propertiesFloat.push_back(std::pair<std::string, float*>(name, &p));
	}

	void GameObject::property(const std::string& name, bool &p)
	{
		m_propertiesBool.push_back(std::pair<std::string, bool*>(name, &p));
	}
	void GameObject::addTag(const std::string& tag)
	{
		m_tags.add(tag);
	}
	bool GameObject::hasTag(const std::string& tag)
	{
		return m_tags.has(tag);
	}
	void GameObject::removeTag(const std::string& tag)
	{
		m_tags.remove(tag);
	}
	std::vector<std::string> GameObject::allTags()
	{
		return m_tags.getVector();
	}
}
