////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_PARTICLES_HEADER
#define KAGE_PARTICLES_HEADER
#include "kf/kf_vector.h"
#include "kf/kf_euler.h"
#include <SFML/Graphics.hpp>

namespace kage
{
	class ParticleEmitter
	{
	public:
		kf::Vec2 m_position;
		kf::Euler m_angle;
		float m_spread;
		float m_lifeMin;
		float m_lifeMax;
		kf::RGBAf m_startColour;
	};

	class ParticleSystem
	{
		sf::Sprite* m_sprite;
		std::vector<ParticleEmitter> m_emitters;
		kf::Vec2 m_position;
		int m_maxCount;
	public:
		void spawn();
		void spawn(const kf::Vec2& pos);
		
	};
	
	namespace ParticleManager
	{
	}

}
#endif
