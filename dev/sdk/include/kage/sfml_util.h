////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_SFML_UTIL_HEADER
#define KAGE_SFML_UTIL_HEADER
#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "kf/kf_vector.h"

namespace kage
{
	void selectSpriteTile1D(sf::Sprite *sprite, unsigned int tileNum, unsigned int tileWidth, unsigned int tileHeight);
	void selectSpriteTile2D(sf::Sprite *sprite, unsigned int tileX, unsigned int tileY, unsigned int tileWidth, unsigned int tileHeight);
	void centreOrigin(sf::Sprite *sprite);
	void scaleSprite(sf::Sprite* sprite, kf::Vec2i size);
	void drawLine(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, sf::Color c = sf::Color::White);
	void drawLine(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, sf::Color c1, sf::Color c2);
	void drawBox(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, sf::Color c = sf::Color::White);
	void drawBoxFilled(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, sf::Color c = sf::Color::White);
	void drawShaderQuad(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, const std::string& shader);
	void drawCircle(sf::RenderTarget& rt, kf::Vec2 p, float radius, unsigned int segments, sf::Color c = sf::Color::White);
	void drawCircleFilled(sf::RenderTarget& rt, kf::Vec2 p, float radius, unsigned int segments, sf::Color c = sf::Color::White);
	void drawCircleFilled(sf::RenderTarget& rt, kf::Vec2 p, float radius, unsigned int segments, sf::Color inner, sf::Color outer);
	void drawArrow(sf::RenderTarget & rt, kf::Vec2 p1, kf::Vec2 p2, float headWidth, float headLength, sf::Color c = sf::Color::White);
}
#endif
