////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage/gameobject.h"
#include <map>
#include <string>
#include "kage/system.h"

namespace
{
	long long g_maxId=0;
	
}

namespace kage
{
	namespace TextureManager
	{
		std::map<std::string, sf::Texture*>& getTextures()
		{
			static std::map<std::string, sf::Texture*> s_textures;
			return s_textures;
		}

		sf::Texture *getTexture(const std::string &filename)
		{
			std::map<std::string, sf::Texture *>::iterator it = getTextures().find(filename);
			if (it == getTextures().end())
			{
				sf::Texture *im = new sf::Texture;
				kage::initDirectory();
				if (!im->loadFromFile(filename))
				{
					im->create(32, 32);
					sf::Color pixels[32 * 32];
					for (int i = 0; i < 32 * 32; ++i)
					{
						pixels[i] = sf::Color::Magenta;
					}
					im->update((sf::Uint8*)pixels);
				}
				getTextures()[filename] = im;
				return im;
			}
			return it->second;
		}

		sf::Sprite *getSprite(const std::string &filename)
		{
			sf::Texture *t = getTexture(filename);
			sf::Sprite *s = new sf::Sprite();

			if (t)
			{
				s->setTexture(*t);
			}
			return s;
		}

		void preload(const std::string& filename)
		{
			getTexture(filename);
		}
	}
}
