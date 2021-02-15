////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage.h"
#include "kf/kf_tags.h"

namespace kage
{
	entt::registry g_registry;

	entt::registry& registry()
	{
		return g_registry;
	}

	void addTag(entt::entity ent, const std::string& tag)
	{
		if (!g_registry.all_of<kf::Tags>(ent))
		{
			g_registry.emplace<kf::Tags>(ent);
		}
		auto& tags = g_registry.get<kf::Tags>(ent);
		tags.add(tag);
	}

	bool hasTag(entt::entity ent, const std::string& tag)
	{
		if (g_registry.all_of<kf::Tags>(ent))
		{
			auto& tags = g_registry.get<kf::Tags>(ent);
			return tags.has(tag);
		}
		return false;
	}

	void removeTag(entt::entity ent, const std::string& tag)
	{
		if (g_registry.all_of<kf::Tags>(ent))
		{
			auto& tags = g_registry.get<kf::Tags>(ent);
			tags.remove(tag);
		}
	}

	std::vector<std::string> allTags(entt::entity ent, const std::string& tag)
	{
		if (g_registry.all_of<kf::Tags>(ent))
		{
			auto& tags = g_registry.get<kf::Tags>(ent);
			return tags.getVector();
		}
		return std::vector<std::string>();
	}

	entt::entity findByTag(std::string tag)
	{
		auto view = g_registry.view<kf::Tags>();
		for (auto entity : view)
		{
			auto& tags = g_registry.get<kf::Tags>(entity);
			if (tags.has(tag))
			{
				return entity;
			}
		}
		return entt::null;
	}

	std::vector<entt::entity> findAllByTag(std::string tag)
	{
		std::vector<entt::entity> found;
		auto view = g_registry.view<kf::Tags>();
		for (auto entity : view)
		{
			auto& tags = g_registry.get<kf::Tags>(entity);
			if (tags.has(tag))
			{
				found.push_back(entity);
			}
		}
		return found;
	}
}
