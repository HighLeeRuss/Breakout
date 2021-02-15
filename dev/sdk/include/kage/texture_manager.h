////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_TEXTUREMANAGER_HEADER
#define KAGE_TEXTUREMANAGER_HEADER

#include <SFML/Graphics.hpp>


namespace kage
{
	namespace TextureManager
	{
		sf::Texture *getTexture(const std::string &filename);
		sf::Sprite *getSprite(const std::string &filename);
		void preload(const std::string& filename);
	}
}

#endif