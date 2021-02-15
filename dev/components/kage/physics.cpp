////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////
 
#include "kage/physics.h"
#include "kage/gameobject.h"
#include "kage/sfml_util.h"
#include "kf/kf_log.h"

#pragma warning(disable: 4100)

namespace kage
{

	namespace Physics
	{
		struct Collision
		{
			b2Fixture* f1;
			b2Fixture* f2;
			GameObject* g1;
			GameObject* g2;
		};

		std::vector<Collision> g_beginCollisions;
		std::vector<Collision> g_endCollisions;

		class ContactListener : public b2ContactListener
		{
		public:
			virtual void BeginContact(b2Contact* contact)
			{
				b2Fixture *f1 = contact->GetFixtureA();
				b2Fixture *f2 = contact->GetFixtureB();
				kf::Vec2 v1 = f1->GetBody()->GetLinearVelocity();
				kf::Vec2 v2 = f2->GetBody()->GetLinearVelocity();
				kf::Vec2 p1 = f1->GetBody()->GetPosition();
				kf::Vec2 p2 = f1->GetBody()->GetPosition();

				b2WorldManifold worldManifold;
				contact->GetWorldManifold(&worldManifold);

				kf::Vec2 norm = worldManifold.normal;
				
				GameObject *g1 = getGameObject(f1);
				GameObject *g2 = getGameObject(f2);

				g_beginCollisions.push_back(Collision{f1,f2,g1,g2});
			}

			virtual void EndContact(b2Contact* contact)
			{
				b2Fixture* f1 = contact->GetFixtureA();
				b2Fixture* f2 = contact->GetFixtureB();
				GameObject* g1 = getGameObject(f1);
				GameObject* g2 = getGameObject(f2);
				g_endCollisions.push_back(Collision{ f1,f2,g1,g2 });
			}
		};

		class DebugDraw : public b2Draw
		{
		public:
			sf::RenderWindow *m_win;
			//float m_scale;
			void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
			{
				sf::Vertex lines[100];
				if (vertexCount > 99)
					vertexCount = 99;
				for (int i = 0; i < vertexCount; ++i)
				{
					lines[i].position.x = vertices[i].x*kage::World::scale();
					lines[i].position.y = vertices[i].y * kage::World::scale();
					lines[i].color = sf::Color((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255), (sf::Uint8)(color.a * 255));
				}
				lines[vertexCount] = lines[0];
				m_win->draw(lines, vertexCount + 1, sf::LineStrip);
			}
			void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
			{
				DrawPolygon(vertices, vertexCount, color);
			}
			void DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
			{
				kage::drawCircle(*m_win, (kf::Vec2)center, radius, 16, sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
			}
			void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
			{
				kage::drawCircle(*m_win, (kf::Vec2)center, radius, 16, sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
				kage::drawArrow(*m_win, (kf::Vec2)center, (kf::Vec2)center + (kf::Vec2)axis, 0.05f, 0.1f, sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
			}
			void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
			{
				kage::drawLine(*m_win, (kf::Vec2)p1, (kf::Vec2)p2, sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
			}
			void DrawTransform(const b2Transform& xf)
			{
				kage::drawArrow(*m_win, (kf::Vec2)xf.p, (kf::Vec2)xf.p + (kf::Vec2)xf.q.GetXAxis(), 0.05f, 0.1f, sf::Color(255, 0, 0, 255));
				kage::drawArrow(*m_win, (kf::Vec2)xf.p, (kf::Vec2)xf.p + (kf::Vec2)xf.q.GetYAxis(), 0.05f, 0.1f, sf::Color(0, 255, 0, 255));
			}
			void DrawPoint(const b2Vec2& p, float size, const b2Color& color) {}
		};

		class RayCastCallback : public b2RayCastCallback {
		public:
			Hit hit;
			unsigned short m_mask = 0xffff;

			RayCastCallback(unsigned short mask = 0xffff): m_mask(mask)
			{
			}

			float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
			{
				if ((fixture->GetFilterData().categoryBits & m_mask) == 0)
				{
					return -1;
				}
				if (!hit.hit || fraction < hit.distance)
				{
					//GameObject *t = (GameObject *)fixture->GetUserData();
					hit.pos.set(point.x, point.y);
					hit.distance = fraction;
					hit.hit = true;
					hit.fixture = fixture;
					return fraction;
				}
				return 1;
			}
		};

		namespace
		{
			b2World *g_world = 0;
			int g_velocityIterations = 8;
			int g_positionIterations = 3;
			ContactListener g_contactListener;
			DebugDraw g_debugDraw;
			b2Body *g_defaultStatic = 0;
			std::vector<b2Fixture *> g_fixturesFromCallback;
		}

		b2World *getWorld()
		{
			return g_world;
		}

		void init(b2Vec2 gravity)
		{
			if (g_world)
			{
				delete g_world;
			}
			g_world = new b2World(gravity);
			g_world->SetContactListener(&g_contactListener);
			g_world->SetDebugDraw(&g_debugDraw);
			g_debugDraw.SetFlags(b2Draw::e_shapeBit);
			g_defaultStatic = createBody(kf::Vec2::zero(), 0, b2BodyType::b2_staticBody, true);
		}
		
		b2Body* getDefaultStatic()
		{
			return g_defaultStatic;
		}

		void update(float dt)
		{
			g_beginCollisions.clear();
			g_endCollisions.clear();
			g_world->Step(dt, g_velocityIterations, g_positionIterations);
			for (int i = 0; i < g_beginCollisions.size(); ++i)
			{
				if (g_beginCollisions[i].g1)
				{
					if (g_beginCollisions[i].g2)
					{
						g_beginCollisions[i].g1->onCollision(g_beginCollisions[i].g2);
					}
					else
					{
						g_beginCollisions[i].g1->onCollision(g_beginCollisions[i].f2);
					}
				}
				if (g_beginCollisions[i].g2)
				{
					if (g_beginCollisions[i].g1)
					{
						g_beginCollisions[i].g2->onCollision(g_beginCollisions[i].g1);
					}
					else
					{
						g_beginCollisions[i].g2->onCollision(g_beginCollisions[i].f1);
					}
				}
			}
			for (int i = 0; i < g_endCollisions.size(); ++i)
			{
				if (g_endCollisions[i].g1)
				{
					if (g_endCollisions[i].g2)
					{
						g_endCollisions[i].g1->onCollisionStop(g_endCollisions[i].g2);
					}
					else
					{
						g_endCollisions[i].g1->onCollisionStop(g_endCollisions[i].f2);
					}
				}
				if (g_endCollisions[i].g2)
				{
					if (g_endCollisions[i].g1)
					{
						g_endCollisions[i].g2->onCollisionStop(g_endCollisions[i].g1);
					}
					else
					{
						g_endCollisions[i].g2->onCollisionStop(g_endCollisions[i].f1);
					}
				}
			}
		}

		void clear()
		{
			b2Body *body = g_world->GetBodyList();
			while (body)
			{
				auto next = body->GetNext();
				if (body != g_defaultStatic)
				{
					g_world->DestroyBody(body);
				}
				body = next;
			}
			clearDefaultStaticFixtures();
		}

		void clearDefaultStaticFixtures()
		{
			if (g_defaultStatic)
			{
				b2Fixture *fix = g_defaultStatic->GetFixtureList();
				while (fix)
				{
					auto next = fix->GetNext();
					g_defaultStatic->DestroyFixture(fix);
					fix = next;
				}
			}
		}

		void gravity(b2Vec2 gravity)
		{
			g_world->SetGravity(gravity);
		}
		
		b2Vec2 gravity()
		{
			return g_world->GetGravity();
		}

		void debugDraw(sf::RenderWindow *win, float scale)
		{
			g_debugDraw.m_win = win;
			//g_debugDraw.m_scale = kage::World::scale();
			g_world->DebugDraw();
		}

		b2Fixture *createCircle(b2Body *body, float radius, kf::Vec2 offset, float density, float damping, void *userData, float restitution, float friction)
		{
			b2CircleShape shape;
			shape.m_radius = radius;
			shape.m_p = offset;
			b2FixtureDef fixDef;
			fixDef.density = density;
			fixDef.restitution = restitution;
			fixDef.friction = friction;
			fixDef.shape = &shape;
			fixDef.userData.pointer = (uintptr_t)userData;
			b2Fixture *fixture = body->CreateFixture(&fixDef);
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			body->SetLinearDamping(damping);
			return fixture;
		}

		b2Fixture *createBox(b2Body *body, kf::Vec2 size, kf::Vec2 offset, float angle, float density, float damping, void *userData,  float restitution, float friction)
		{
			b2PolygonShape shape;
			shape.SetAsBox(size.x / 2.0f, size.y / 2.0f, offset, angle);
			b2FixtureDef fixDef;
			fixDef.density = density;
			fixDef.restitution = restitution;
			fixDef.friction = friction;
			fixDef.shape = &shape;
			fixDef.userData.pointer = (uintptr_t)userData;
			b2Fixture *fixture = body->CreateFixture(&fixDef);
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			body->SetLinearDamping(damping);
			return fixture;
		}

		b2Fixture *createEdge(b2Body *body, kf::Vec2 vertex1, kf::Vec2 vertex2, float density, float damping, void *userData, float restitution, float friction)
		{
			b2EdgeShape shape;
			shape.SetTwoSided(vertex1, vertex2);
			b2FixtureDef fixDef;
			fixDef.density = density;
			fixDef.restitution = restitution;
			fixDef.friction = friction;
			fixDef.shape = &shape;
			fixDef.userData.pointer = (uintptr_t)userData;
			b2Fixture *fixture = body->CreateFixture(&fixDef);
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			body->SetLinearDamping(damping);
			return fixture;
		}

		b2Body *createBody(kf::Vec2 pos, float angle, b2BodyType type, bool fixedRotation, void *userData, float gravityScale)
		{
			b2BodyDef bodyDef;
			bodyDef.position = pos;
			bodyDef.type = type;
			bodyDef.angle = angle;
			bodyDef.fixedRotation = fixedRotation;
			bodyDef.userData.pointer = (uintptr_t)userData;
			bodyDef.gravityScale = gravityScale;
			return g_world->CreateBody(&bodyDef);
		}
		Hit rayCast(kf::Vec2 p1, kf::Vec2 p2, unsigned short mask)
		{
			RayCastCallback cb(mask);
			g_world->RayCast(&cb, p1, p2);
			return cb.hit;
		}

		GameObject *getGameObject(b2Fixture *fixture)
		{
			if (fixture)
			{
				b2Body *body = fixture->GetBody();
				return (GameObject*)body->GetUserData().pointer;
			}
			return 0;
		}

		GameObject *getGameObject(b2Body *body)
		{
			if (body)
			{
				return (GameObject*)body->GetUserData().pointer;
			}
			return 0;
		}

		b2Fixture *getTouching(b2Body *body, long long fixtureNum)
		{
			b2Fixture *f = body->GetFixtureList();
			int i = 0;
			for (; f; f = f->GetNext(),++i)
			{
				if ((long long)f->GetUserData().pointer == fixtureNum)
				{
					break;
				}
			}
			if (!f)
			{
				return 0;
			}
			for (b2ContactEdge* c = body->GetContactList(); c; c = c->next)
			{
				b2Fixture *f1;
				b2Fixture *f2;
				
				if (c->contact->GetFixtureA() == f)
				{
					f1 = c->contact->GetFixtureA();
					f2 = c->contact->GetFixtureB();
				}
				else if(c->contact->GetFixtureB() == f)
				{
					f1 = c->contact->GetFixtureB();
					f2 = c->contact->GetFixtureA();
				}
				else
				{
					continue;
				}

				if (c->contact->IsTouching())
				{
					return f2;
				}
			}
			return 0;
		}

		class AABBCallback :public b2QueryCallback
		{
		public:
			b2Vec2 pos;
			AABBCallback(b2Vec2 p) : pos(p)
			{

			}
			bool ReportFixture(b2Fixture* fixture)
			{
				if (fixture->TestPoint(pos))
				{
					g_fixturesFromCallback.push_back(fixture);
				}
				return true;
			}
		};

		b2Fixture *testPoint(kf::Vec2 pos)
		{
			g_fixturesFromCallback.clear();
			AABBCallback aabbcb(pos);
			b2AABB aabb;
			aabb.lowerBound = b2Vec2(pos);
			aabb.upperBound = b2Vec2(pos);
			g_world->QueryAABB(&aabbcb, aabb);
			if (g_fixturesFromCallback.size() > 0)
			{
				return g_fixturesFromCallback.front();
			}
			return 0;
		}
		

		CircleBuilder &CircleBuilder::radius(float r)
		{
			m_radius = r;
			return *this;
		}

		b2Fixture *CircleBuilder::build(b2Body *body)
		{
			if (m_calcDensity)
			{
				m_density = (float)(m_mass / (m_radius * m_radius * 3.14159265));
			}
			b2Fixture *fix = createCircle(body, m_radius, m_pos, m_density, m_damping, m_userData, m_restitution, m_friction);
			fix->SetSensor(m_sensor);
			b2Filter filter;
			filter.categoryBits = m_filterCategory;
			filter.maskBits = m_filterMask;
			filter.groupIndex = m_group;
			fix->SetFilterData(filter);

			return fix;
		}

		BoxBuilder &BoxBuilder::size(float x, float y)
		{
			m_size.set(x, y);
			return *this;
		}

		BoxBuilder &BoxBuilder::size(float s)
		{
			m_size.set(s, s);
			return *this;
		}

		BoxBuilder &BoxBuilder::size(const kf::Vec2 &s)
		{
			m_size = s;
			return *this;
		}

		b2Fixture *BoxBuilder::build(b2Body *body)
		{
			if (m_calcDensity)
			{
				m_density = m_mass / (m_size.x * m_size.y);
			}
			b2Fixture *fix = createBox(body, m_size, m_pos, m_angle, m_density, m_damping, m_userData, m_restitution, m_friction);
			fix->SetSensor(m_sensor);
			b2Filter filter;
			filter.categoryBits = m_filterCategory;
			filter.maskBits = m_filterMask;
			filter.groupIndex = m_group;
			fix->SetFilterData(filter);

			return fix;
		}


		EdgeBuilder& EdgeBuilder::start(const kf::Vec2& s)
		{
			m_start = s;
			return *this;
		}

		EdgeBuilder& EdgeBuilder::start(float x, float y)
		{
			m_start.set(x,y);
			return *this;
		}

		EdgeBuilder& EdgeBuilder::end(const kf::Vec2& e)
		{
			m_end = e;
			return *this;
		}

		EdgeBuilder& EdgeBuilder::end(float x, float y)
		{
			m_end.set(x, y);
			return *this;
		}

		b2Fixture* EdgeBuilder::build(b2Body* body)
		{
			if (m_calcDensity)
			{
				m_density = (float)(m_mass / (length(m_start-m_end)*0.01));
			}
			b2Fixture* fix = createEdge(body, m_start, m_end, m_density, m_damping, m_userData, m_restitution, m_friction);
			fix->SetSensor(m_sensor);
			b2Filter filter;
			filter.categoryBits = m_filterCategory;
			filter.maskBits = m_filterMask;
			filter.groupIndex = m_group;
			fix->SetFilterData(filter);

			return fix;
		}

		BodyBuilder &BodyBuilder::type(b2BodyType type)
		{
			m_type = type;
			return *this;
		}

		BodyBuilder &BodyBuilder::pos(const kf::Vec2 &p)
		{
			m_pos = p;
			return *this;
		}

		BodyBuilder &BodyBuilder::pos(float x, float y)
		{
			m_pos.set(x, y);
			return *this;
		}

		BodyBuilder &BodyBuilder::angle(float a)
		{
			m_angle = a;
			return *this;
		}

		BodyBuilder &BodyBuilder::userData(void *ud)
		{
			m_userData = ud;
			return *this;
		}

		BodyBuilder &BodyBuilder::fixedRotation(bool fr)
		{
			m_fixedRotation = fr;
			return *this;
		}

		BodyBuilder& BodyBuilder::gravityScale(float g)
		{
			m_gravityScale = g;
			return *this;
		}

		b2Body *BodyBuilder::build()
		{
			return createBody(m_pos, m_angle, m_type, m_fixedRotation, m_userData, m_gravityScale);
		}

	}

}
