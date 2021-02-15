////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#pragma once
#include "entt/entt.hpp"

using namespace entt::literals;
#define TAG(T) entt::tag<T##_hs>

namespace kage
{
	entt::registry& registry();
	void addTag(entt::entity ent, const std::string& tag);
	bool hasTag(entt::entity ent, const std::string& tag);
	void removeTag(entt::entity ent, const std::string& tag);
	std::vector<std::string> allTags(entt::entity ent, const std::string& tag);
	entt::entity findByTag(std::string tag);
	std::vector<entt::entity> findAllByTag(std::string tag);
};

