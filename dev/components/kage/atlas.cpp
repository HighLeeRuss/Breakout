////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage/atlas.h"
#include "kage/texture_manager.h"
#include "kage/sfml_util.h"

namespace kage
{
	Atlas::Atlas():m_sprite(0),m_columns(0),m_rows(0),m_tileHeight(0),m_tileWidth(0)
	{
	}

	Atlas::Atlas(std::string textureName, int tileWidth, int tileHeight)
	{
		create(textureName, tileWidth, tileHeight);
	}

	Atlas::~Atlas()
	{
	}

	Atlas &Atlas::create(std::string textureName, int tileWidth, int tileHeight)
	{
		delete m_sprite;
		m_sprite = kage::TextureManager::getSprite(textureName);
		sf::Vector2u s = m_sprite->getTexture()->getSize();
		m_tileWidth = tileWidth;
		m_tileHeight = tileHeight;
		m_columns = s.x / tileWidth;
		m_rows = s.y / tileHeight;
		return *this;
	}

	sf::Sprite * Atlas::getSprite() const
	{
		return m_sprite;
	}

	int Atlas::getTileWidth() const
	{
		return m_tileWidth;
	}
	
	int Atlas::getTileHeight() const
	{
		return m_tileHeight;
	}

	void Atlas::draw(sf::RenderTarget& target, int x, int y, unsigned int tile)
	{
		m_sprite->setPosition((float)x, (float)y);
		kage::selectSpriteTile1D(m_sprite, tile, m_tileWidth, m_tileHeight);
		target.draw(*m_sprite);
	}

	void Atlas::draw(sf::RenderTarget& target, int x, int y, unsigned int tileX, unsigned int tileY)
	{
		m_sprite->setPosition((float)x, (float)y);
		kage::selectSpriteTile2D(m_sprite, tileX, tileY, m_tileWidth, m_tileHeight);
		target.draw(*m_sprite);
	}

	Atlas& Atlas::selectTile(unsigned int tile)
	{
		kage::selectSpriteTile1D(m_sprite, tile, m_tileWidth, m_tileHeight);
		return *this;
	}

	Atlas& Atlas::selectTile(unsigned int tileX, unsigned int tileY)
	{
		kage::selectSpriteTile2D(m_sprite, tileX, tileY, m_tileWidth, m_tileHeight);
		return *this;
	}


}