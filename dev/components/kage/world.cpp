////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage/world.h"
#include "kage/gameobject.h"
#include "kage/sfml_util.h"
#include "kage/texture_manager.h"
#include "kage/physics.h"
#include "kage/sound_manager.h"
#include "kage/input.h"
#include "imgui/imgui.h"

namespace kage
{
	namespace World
	{
		std::map<long long, GameObject*> worldObjects;
		long long worldHighestID = 0;
		bool sortOrderDirty = false;
		float worldScale = 64.0f;
		bool paused = false;

		long long newID()
		{
			return ++worldHighestID;
		}

		void update(float dt)
		{
			if (paused)
			{
				return;
			}
			kage::SoundManager::update();
			kage::Physics::update(dt);
			std::vector<long long> deadobjects;
			for (std::map<long long, GameObject*>::iterator it = worldObjects.begin(); it != worldObjects.end(); ++it)
			{
				it->second->preUpdate(dt);
				it->second->update(dt);
				if (it->second->m_dead)
				{
					deadobjects.push_back(it->first);
				}
			}
			for (unsigned int i = 0; i < deadobjects.size(); ++i)
			{
				std::map<long long, GameObject*>::iterator it = worldObjects.find(deadobjects[i]);
				if (it != worldObjects.end())
				{
					delete it->second;
					worldObjects.erase(it);
				}
			}
		}

		bool sortOrder(GameObject* g1, GameObject* g2)
		{
			return g1->m_order < g2->m_order;
		}

		void render(sf::RenderTarget& rt)
		{
			std::vector<GameObject*> objects(worldObjects.size());
			int i = 0;
			for (std::map<long long, GameObject*>::iterator it = worldObjects.begin(); it != worldObjects.end(); ++it)
			{
				objects[i++] = it->second;
			}

			std::sort(objects.begin(), objects.end(), sortOrder);

			for (i = 0; i < objects.size(); ++i)
			{
				objects[i]->render(rt);
			}
		}

		void add(GameObject* obj)
		{
			if (obj->m_id == 0)
			{
				obj->m_id = newID();
			}
			auto it = worldObjects.find(obj->m_id);
			if (it == worldObjects.end())
			{
				worldObjects[obj->m_id] = obj;
			}
		}

		void remove(GameObject* obj)
		{
			auto it = worldObjects.find(obj->m_id);
			if (it != worldObjects.end())
			{
				delete it->second;
				worldObjects.erase(it);
			}
		}

		void remove(std::string tag)
		{
			for (std::map<long long, GameObject*>::iterator it = worldObjects.begin(); it != worldObjects.end();)
			{
				if (it->second->m_tags.has(tag))
				{
					delete it->second;
					it = worldObjects.erase(it);
				}
				else
				{
					it++;
				}
			}
		}

		void clear()
		{
			for (std::map<long long, GameObject*>::iterator it = worldObjects.begin(); it != worldObjects.end(); ++it)
			{
				delete it->second;
			}
			worldObjects.clear();
		}

		GameObject* findByID(long long id)
		{
			auto it = worldObjects.find(id);
			if (it != worldObjects.end())
				return it->second;
			return 0;
		}

		GameObject* findByTag(std::string tag)
		{
			for (std::map<long long, GameObject*>::iterator it = worldObjects.begin(); it != worldObjects.end(); ++it)
			{
				if (it->second->m_tags.has(tag))
					return it->second;
			}
			return 0;
		}

		std::vector<GameObject*> findAllByTag(std::string tag)
		{
			std::vector<GameObject*> found;
			for (std::map<long long, GameObject*>::iterator it = worldObjects.begin(); it != worldObjects.end(); ++it)
			{
				if (it->second->m_tags.has(tag))
					found.push_back(it->second);
			}
			return found;
		}

		float scale()
		{
			return worldScale;
		}

		void scale(float s)
		{
			worldScale = s;
		}

		std::map<long long, GameObject*>& getWorldObjects()
		{
			return worldObjects;
		}

		void inspector(sf::RenderTarget *rt)
		{
			static int currentListItem = 0;
			std::vector<char*> items;

			ImGui::Begin("World Inspector");

			if (rt)
			{
				ImGui::Text("View");
				sf::View view = rt->getView();
				auto c = view.getCenter() / worldScale;
				auto s = view.getSize() / worldScale;
				auto r = view.getRotation();
				bool changed = false;
				changed |= ImGui::SliderFloat("View X", &c.x, 0, 40);
				changed |= ImGui::SliderFloat("View Y", &c.y, 0, 40);
				changed |= ImGui::SliderFloat("View Width", &s.x, 0, 40);
				changed |= ImGui::SliderFloat("View Height", &s.y, 0, 40);
				changed |= ImGui::SliderFloat("View Rotation", &r, 0, 360);
				if (changed)
				{
					view.setCenter(c * worldScale);
					view.setSize(s * worldScale);
					view.setRotation(r);
					rt->setView(view);
				}
			}

			ImGui::Columns(2);

			if (!worldObjects.empty())
			{
				if (currentListItem >= worldObjects.size())
				{
					currentListItem = (int)worldObjects.size() - 1;
				}
				std::vector<long long> ids(worldObjects.size());
				{
					int i = 0;
					for (auto it = worldObjects.begin(); it != worldObjects.end(); ++it)
					{
						ids[i] = it->first;
						std::string s;
						s = std::to_string(it->first);
						if (!it->second->m_tags.getVector().empty())
						{
							s += "  (";
							for (int t = 0; t < it->second->m_tags.getVector().size(); ++t)
							{
								if (t != 0) s += ", ";
								s += it->second->m_tags.getVector()[t];
							}
							s += ")";
						}
						char* text = new char[s.size() + 1];
						sprintf(text, "%s", s.c_str());
						items.push_back(text);
						++i;
					}
				}
				ImGui::ListBox("", &currentListItem, &items[0], (int)items.size());
				for (int ii = 0; ii < items.size(); ++ii)
				{
					delete items[ii];
				}
				ImGui::NextColumn();
				kage::GameObject* gob = kage::World::findByID(ids[currentListItem]);
				if (gob)
				{
					ImGui::Text("GameObject");
					kf::Vec2 pos = gob->position();
					bool changed = false;
					changed = ImGui::SliderFloat("Pos X", &pos.x, 0, 40);
					changed |= ImGui::SliderFloat("Pos Y", &pos.y, 0, 40);
					if (changed)
					{
						gob->position(pos);
					}

					kf::Vec2 vel = gob->velocity();
					changed = ImGui::InputFloat2("Velocity", &vel.x);
					if (changed)
					{
						gob->velocity(vel);
					}
					ImGui::InputFloat("Life", &gob->m_life);
					ImGui::Text("");
					ImGui::Text("Custom Properties");
					for (int i = 0; i < gob->m_propertiesInt.size(); ++i)
					{
						ImGui::InputInt(gob->m_propertiesInt[i].first.c_str(), gob->m_propertiesInt[i].second);
					}
					for (int i = 0; i < gob->m_propertiesFloat.size(); ++i)
					{
						ImGui::InputFloat(gob->m_propertiesFloat[i].first.c_str(), gob->m_propertiesFloat[i].second);
					}
					for (int i = 0; i < gob->m_propertiesBool.size(); ++i)
					{
						ImGui::Checkbox(gob->m_propertiesBool[i].first.c_str(), gob->m_propertiesBool[i].second);
					}


					if (gob->m_body)
					{
						ImGui::Text("");
						ImGui::Text("Physics Body");
						float mass = gob->m_body->GetMass();
						if (ImGui::Button("Wake"))
						{
							gob->m_body->SetAwake(true);
						}
						if (ImGui::InputFloat("Mass", &mass))
						{

							//							gob->m_body->SetMassData(
						}
						b2Fixture* fix = gob->m_body->GetFixtureList();
						while (fix)
						{
							std::string s;
							switch (fix->GetType())
							{
							case b2Shape::e_circle:
								s += "Circle ";
								break;
							case b2Shape::e_polygon:
								s += "Polygon ";
								break;
							case b2Shape::e_chain:
								s += "Chain ";
								break;
							case b2Shape::e_edge:
								s += "Edge ";
								break;
							}
							s += "UserData:";
							s += std::to_string((unsigned long long)fix->GetUserData().pointer);
							//s += " Pos:(";
							//s+= std::to_string(fix->GetShape()->
							b2MassData md;
							fix->GetMassData(&md);
							s += " Weight:" + std::to_string(md.mass) + "kg";
							if (fix->IsSensor())
							{
								s += " Sensor";
							}
							ImGui::Text(s.c_str());
							fix = fix->GetNext();
						}

					}
				}

			}
			ImGui::End();
		}

		void setView(sf::RenderTarget& rt, kf::Vec2 centre, float zoom)
		{
			sf::View v = rt.getDefaultView();
			v.setCenter(centre * worldScale);
			v.zoom(zoom);
			rt.setView(v);
		}

		void setView(sf::RenderTarget& rt)
		{
			sf::View v = rt.getDefaultView();
			rt.setView(v);
		}

		void debugGrid(sf::RenderTarget& rt)
		{
			kf::Vec2 tl = rt.mapPixelToCoords(sf::Vector2i(0, 0)) / kage::World::scale();
			kf::Vec2 br = rt.mapPixelToCoords(sf::Vector2i(rt.getSize().x, rt.getSize().y)) / kage::World::scale();
			for (int x = (int)tl.x; x <= (int)br.x; ++x)
			{
				unsigned char c = 64;
				if (x == 0)
					c = 160;
				kage::drawLine(rt, kf::Vec2((float)x, tl.y - 1), kf::Vec2((float)x, br.y + 1), sf::Color(c, c, c, 255));
			}
			for (int y = (int)tl.y; y <= (int)br.y; ++y)
			{
				unsigned char c = 64;
				if (y == 0)
					c = 160;
				kage::drawLine(rt, kf::Vec2(tl.x - 1, (float)y), kf::Vec2(br.x + 1, (float)y), sf::Color(c, c, c, 255));
			}
		}

		void setViewFitWidth(sf::RenderTarget& rt, kf::Vec2 pos, float width, bool isCentre)
		{
			sf::View v = rt.getDefaultView();
			pos *= worldScale;
			float aspect = float(rt.getSize().x) / float(rt.getSize().y);
			kf::Vec2 size(width * worldScale, (width * worldScale) / aspect);
			if (isCentre)
				pos -= size / 2.0;
			v.reset(sf::FloatRect(pos.x, pos.y, size.x, size.y));
			rt.setView(v);
		}
		void setViewFitHeight(sf::RenderTarget& rt, kf::Vec2 pos, float height, bool isCentre)
		{
			sf::View v = rt.getDefaultView();
			pos *= worldScale;
			float aspect = float(rt.getSize().x) / float(rt.getSize().y);
			kf::Vec2 size(height * worldScale * aspect, (height * worldScale));
			if (isCentre)
				pos -= size / 2.0;
			v.reset(sf::FloatRect(pos.x, pos.y, size.x, size.y));
			rt.setView(v);
		}
		void setViewFitAll(sf::RenderTarget& rt, kf::Vec2 pos, float width, float height, bool isCentre)
		{
			sf::View v = rt.getDefaultView();
			pos *= worldScale;
			float aspect = float(rt.getSize().x) / float(rt.getSize().y);
			float aspect2 = width / height;
			kf::Vec2 size;
			if (aspect > aspect2)
			{
				size.set(height * worldScale * aspect, (height * worldScale));
			}
			else
			{
				size.set(width * worldScale, (width * worldScale) / aspect);
			}
			if (isCentre)
				pos -= size / 2.0;
			v.reset(sf::FloatRect(pos.x, pos.y, size.x, size.y));
			rt.setView(v);
		}
		void pause(bool p)
		{
			paused = p;
		}

		bool pause()
		{
			return paused;
		}
	}
}
