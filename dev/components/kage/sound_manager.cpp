////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include "kage/sound_manager.h"
#include "kage/system.h"
#include "kage/world.h"
#include "kage/gameobject.h"

namespace
{
	long long g_maxId=0;
	
	
}
namespace kage
{
	namespace SoundManager
	{
		std::map<std::string, sf::SoundBuffer*>& getSoundBuffers()
		{
			static std::map<std::string, sf::SoundBuffer*> s_soundBuffers;
			return s_soundBuffers;
		}
		
		std::vector<sf::Sound*>& getSounds()
		{
			static std::vector<sf::Sound*> s_sounds;
			return s_sounds;
		}

		sf::Sound *playSound(const std::string &filename)
		{
			sf::SoundBuffer *sb;
			std::map<std::string, sf::SoundBuffer *>::iterator it = getSoundBuffers().find(filename);
			if (it == getSoundBuffers().end())
			{
				sb = new sf::SoundBuffer;
				kage::initDirectory();
				if (!sb->loadFromFile(filename))
				{
					delete sb;
					return 0;
				}
				getSoundBuffers()[filename] = sb;
			}
			else
			{
				sb = it->second;
			}

			sf::Sound *s = new sf::Sound(*sb);
			s->play();
			return s;
		}

		void update()
		{
			for (int i = 0; i < getSounds().size(); ++i)
			{
				if (getSounds()[i]->getStatus() == sf::SoundSource::Stopped)
				{
					delete getSounds()[i];
					getSounds().erase(getSounds().begin() + i);
					--i;
				}
			}
		}

		void preload(const std::string& filename)
		{
			sf::SoundBuffer* sb;
			std::map<std::string, sf::SoundBuffer*>::iterator it = getSoundBuffers().find(filename);
			if (it == getSoundBuffers().end())
			{
				sb = new sf::SoundBuffer;
				kage::initDirectory();
				if (!sb->loadFromFile(filename))
				{
					delete sb;
					return;
				}
				getSoundBuffers()[filename] = sb;
			}
		}
	}
}
