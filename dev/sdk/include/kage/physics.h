////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_PHYSICS_HEADER
#define KAGE_PHYSICS_HEADER
#include "box2d/Box2D.h"
#include "kf/kf_vector.h"

namespace sf
{
	class RenderWindow;
}

namespace kage
{
	class GameObject;

	namespace Physics
	{
		// Hit is used to hold raycast intersection results.
		struct Hit
		{
		public:
			kf::Vec2 pos;	// Position of intersection.
			float distance;		// Proportion of the ray at which the intersection occured.
			bool hit;			// Bool to say if an intersection happened.
			b2Fixture *fixture;		// The collider that was intersected.

			Hit() : pos(kf::Vec2(0, 0)), distance(0), hit(false), fixture(0) {}
		};


		void init(b2Vec2 gravity = b2Vec2(0,0));	// Initialise the physics system.
		void update(float dt);						// Step the physics system.
		void gravity(b2Vec2 gravity);
		b2Vec2 gravity();
		b2World *getWorld();						// Retrieve the Box2D world.
		void clear();
		void clearDefaultStaticFixtures();
		void debugDraw(sf::RenderWindow *win, float scale);							// Draw debug information.
		b2Fixture *createCircle(b2Body *body, float radius, kf::Vec2 offset, float density, float damping, void *userData, float restitution, float friction);		// Create a circle collider.
		b2Fixture *createBox(b2Body *body, kf::Vec2 size, kf::Vec2 offset, float angle, float density, float damping, void *userData, float restitution, float friction);	// Create a box collider.
		b2Fixture *createEdge(b2Body *body, kf::Vec2 vertex1, kf::Vec2 vertex2, float density, float damping, void *userData, float restitution, float friction);	// Create an edge collider.
		b2Body *createBody(kf::Vec2 pos, float angle = 0, b2BodyType type = b2BodyType::b2_dynamicBody, bool fixedRotation = false, void *userData = 0, float gravityScale = 1.0f);
		Hit rayCast(kf::Vec2 p1, kf::Vec2 p2, unsigned short mask=0xffff);	// Perform a ray cast. Only the closest intersection is returned.
		b2Body* getDefaultStatic();
		GameObject *getGameObject(b2Fixture *fixture);
		GameObject *getGameObject(b2Body *fixture);
		b2Fixture *getTouching(b2Body *body, long long fixtureNum);
		b2Fixture *testPoint(kf::Vec2 pos);

		template<typename T>
		class BaseFixtureBuilder
		{
		public:
			kf::Vec2 m_pos;
			float		m_mass;
			float		m_density;
			float		m_damping;
			void	   *m_userData;
			b2BodyType	m_type;
			bool		m_calcDensity;
			float		m_restitution;
			float       m_friction;
			bool		m_sensor;
			float		m_angle;
			unsigned short m_filterCategory = 1;
			unsigned short m_filterMask = 0xffff;
			short m_group = 0;

		public:
			BaseFixtureBuilder() : m_pos(kf::Vec2(0, 0)),
				m_mass(0),
				m_density(1),
				m_damping(0),
				m_userData(0),
				m_calcDensity(false),
				m_restitution(0),
				m_friction(0),
				m_angle(0),
				m_sensor(false)
			{
			}

			T &pos(const kf::Vec2 &p)
			{
				m_pos = p;
				return *static_cast<T*>(this);
			}

			T &pos(float x, float y)
			{
				m_pos.set(x, y);
				return *static_cast<T*>(this);
			}

			T &angle(float a)
			{
				m_angle = a;
				return *static_cast<T*>(this);
			}

			T &mass(float m)
			{
				m_mass = m;
				m_calcDensity = true;
				return *static_cast<T*>(this);
			}

			T &density(float d)
			{
				m_damping = d;
				m_calcDensity = false;
				return *static_cast<T*>(this);
			}

			T &damping(float d)
			{
				m_damping = d;
				return *static_cast<T*>(this);
			}

			T &userData(void *ud)
			{
				m_userData = ud;
				return *static_cast<T*>(this);
			}

			T &userData(int ud)
			{
				m_userData = (void *)ud;
				return *static_cast<T*>(this);
			}

			T &restitution(float r)
			{
				m_restitution = r;
				return *static_cast<T*>(this);
			}

			T &friction(float f)
			{
				m_friction = f;
				return *static_cast<T*>(this);
			}

			T& sensor(bool s)
			{
				m_sensor = s;
				return *static_cast<T*>(this);
			}

			T& category(unsigned short cat)
			{
				m_filterCategory = cat;
				return *static_cast<T*>(this);
			}

			T& mask(unsigned short m)
			{
				m_filterMask = m;
				return *static_cast<T*>(this);
			}

			T& group(short g)
			{
				m_group = g;
				return *static_cast<T*>(this);
			}
		};

		// Fluent Circle collider builder helper
		class CircleBuilder : public BaseFixtureBuilder<CircleBuilder>
		{
		public:
			float		m_radius;

		public:
			CircleBuilder() : m_radius(1.0f)
			{
			}

			CircleBuilder &radius(float r);
			b2Fixture *build(b2Body *body);
		};

		// Fluent Box collider builder helper
		class BoxBuilder : public BaseFixtureBuilder<BoxBuilder>
		{
		public:
			kf::Vec2 m_size;

		public:
			BoxBuilder() : m_size(kf::Vec2(1, 1))
			{
			}

			BoxBuilder &size(float x, float y);
			BoxBuilder &size(float s);
			BoxBuilder &size(const kf::Vec2 &s);
			b2Fixture *build(b2Body *body);
		};

		// Fluent Edge collider builder helper
		class EdgeBuilder : public BaseFixtureBuilder<EdgeBuilder>
		{
		public:
			float		m_radius;
			kf::Vec2 m_start;
			kf::Vec2 m_end;

		public:
			EdgeBuilder() : m_radius(1.0f)
			{
			}

			EdgeBuilder& start(const kf::Vec2& s);
			EdgeBuilder& start(float x, float y);
			EdgeBuilder& end(const kf::Vec2& e);
			EdgeBuilder& end(float x, float y);
			b2Fixture* build(b2Body* body);
		};

		class BodyBuilder
		{
		public:
			b2BodyType m_type;
			kf::Vec2 m_pos;
			void	   *m_userData;
			float       m_angle;
			bool		m_fixedRotation;
			float		m_gravityScale;

			BodyBuilder() : m_type(b2BodyType::b2_dynamicBody), m_userData(0), m_angle(0), m_fixedRotation(true), m_gravityScale(1.0f)
			{
			}

			BodyBuilder &type(b2BodyType type);
			BodyBuilder &pos(const kf::Vec2 &p);
			BodyBuilder &pos(float x, float y);
			BodyBuilder &angle(float a);
			BodyBuilder &userData(void *ud);
			BodyBuilder &fixedRotation(bool fr);
			BodyBuilder& gravityScale(float g);
			b2Body *build();
		};
	}
}

#endif