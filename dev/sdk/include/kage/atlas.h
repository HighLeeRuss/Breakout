////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_ATLAS_HEADER
#define KAGE_ATLAS_HEADER
#include "kf/kf_vector.h"
#include <SFML/Graphics.hpp>

namespace kage
{
	class Atlas
	{
	public:
		Atlas();
		Atlas(std::string textureName, int tileWidth, int tileHeight);
		virtual ~Atlas();
		virtual Atlas &create(std::string textureName, int tileWidth, int tileHeight);
		virtual sf::Sprite *getSprite() const;
		virtual int getTileWidth() const;
		virtual int getTileHeight() const;
		virtual void draw(sf::RenderTarget& target, int x, int y, unsigned int tile);
		virtual void draw(sf::RenderTarget& target, int x, int y, unsigned int tileX, unsigned int tileY);
		virtual Atlas& selectTile(unsigned int tile);
		virtual Atlas& selectTile(unsigned int tileX, unsigned int tileY);

	protected:
		sf::Sprite *m_sprite;
		int m_tileWidth, m_tileHeight;
		int m_columns, m_rows;
	};
}
#endif
