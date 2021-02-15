////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage/sfml_util.h"
#include "kage/world.h"
#include "kage/shader_manager.h"

namespace kage
{
	void selectSpriteTile1D(sf::Sprite *sprite, unsigned int tileNum, unsigned int tileWidth, unsigned int tileHeight)
	{
		int tileColumns = sprite->getTexture()->getSize().x / tileWidth;
		sprite->setTextureRect(sf::IntRect((tileNum % tileColumns)*tileWidth, (tileNum / tileColumns)*tileHeight, tileWidth, tileHeight));
	}

	void selectSpriteTile2D(sf::Sprite *sprite, unsigned int tileX, unsigned int tileY, unsigned int tileWidth, unsigned int tileHeight)
	{
		sprite->setTextureRect(sf::IntRect(tileX*tileWidth, tileY*tileHeight, tileWidth, tileHeight));
	}

	void centreOrigin(sf::Sprite *sprite)
	{
		sf::IntRect rect = sprite->getTextureRect();
		sprite->setOrigin(rect.width / 2.0f, rect.height / 2.0f);
	}

	void scaleSprite(sf::Sprite* sprite, kf::Vec2i size)
	{
		kf::Vec2 scale = size;
		scale /= kf::Vec2(sprite->getTextureRect().getSize());
		sprite->setScale(scale);
	}

	void drawLine(sf::RenderTarget &rt, kf::Vec2 p1, kf::Vec2 p2, sf::Color c)
	{
		drawLine(rt, p1, p2, c, c);
	}
	
	void drawLine(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, sf::Color c1, sf::Color c2)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(p1 * kage::World::scale(), c1),
			sf::Vertex(p2 * kage::World::scale(), c2)
		};
		rt.draw(line, 2, sf::LineStrip);
	}

	void drawBox(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, sf::Color c)
	{
		p1 *= kage::World::scale();
		p2 *= kage::World::scale();
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(p1), c),
			sf::Vertex(sf::Vector2f(p2.x, p1.y), c),
			sf::Vertex(sf::Vector2f(p2), c),
			sf::Vertex(sf::Vector2f(p1.x, p2.y), c),
			sf::Vertex(sf::Vector2f(p1), c)
		};
		rt.draw(line, 5, sf::LineStrip);
	}

	void drawBoxFilled(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, sf::Color c)
	{
		p1 *= kage::World::scale();
		p2 *= kage::World::scale();
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(p1), c),
			sf::Vertex(sf::Vector2f(p2.x, p1.y), c),
			sf::Vertex(sf::Vector2f(p2), c),
			sf::Vertex(sf::Vector2f(p1), c),
			sf::Vertex(sf::Vector2f(p2), c),
			sf::Vertex(sf::Vector2f(p1.x, p2.y), c)
		};
		rt.draw(line, 6, sf::Triangles);
	}

	void drawShaderQuad(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, const std::string& shader)
	{
		p1 *= kage::World::scale();
		p2 *= kage::World::scale();
		sf::Color c(255, 255, 255, 255);
		sf::Vertex line[] =
		{
			sf::Vertex(p1, c, sf::Vector2f(0,0)),
			sf::Vertex(p2, c, sf::Vector2f(1,1)),
			sf::Vertex(sf::Vector2f(p2.x,p1.y), c, sf::Vector2f(1,0)),
			sf::Vertex(p1, c, sf::Vector2f(0,0)),
			sf::Vertex(sf::Vector2f(p1.x, p2.y), c, sf::Vector2f(0,1)),
			sf::Vertex(p2, c, sf::Vector2f(1,1)),
		};
		rt.draw(line, 6, sf::Triangles, ShaderManager::getShader(shader));
	}

	void drawCircle(sf::RenderTarget& rt, kf::Vec2 p, float radius, unsigned int segments, sf::Color c)
	{
		sf::Vertex lines[100];
		if (segments > 99)
			segments = 99;
		for (unsigned int i = 0; i < segments; ++i)
		{
			float angle = float((3.14159265*2.0 / segments)*i);
			sf::Vector2f pos(cos(angle)*radius + p.x, sin(angle)*radius + p.y);
			lines[i].position = pos * kage::World::scale();
			lines[i].color = c;
		}
		lines[segments] = lines[0];
		rt.draw(lines, segments+1, sf::LineStrip);
	}

	void drawCircleFilled(sf::RenderTarget& rt, kf::Vec2 p, float radius, unsigned int segments, sf::Color c)
	{
		drawCircleFilled(rt, p, radius, segments, c, c);
	}

	void drawCircleFilled(sf::RenderTarget& rt, kf::Vec2 p, float radius, unsigned int segments, sf::Color inner, sf::Color outer)
	{
		sf::Vertex lines[100];
		if (segments > 98)
			segments = 98;
		lines[0].position = p * kage::World::scale();
		lines[0].color = inner;
		for (unsigned int i = 0; i < segments; ++i)
		{
			float angle = float((3.14159265 * 2.0 / segments) * i);
			sf::Vector2f pos(cos(angle) * radius + p.x, sin(angle) * radius + p.y);
			lines[i+1].position = pos * kage::World::scale();
			lines[i+1].color = outer;
		}
		lines[segments + 1] = lines[1];
		rt.draw(lines, segments + 2, sf::TriangleFan);
	}

	void drawArrow(sf::RenderTarget& rt, kf::Vec2 p1, kf::Vec2 p2, float headWidth, float headLength, sf::Color c)
	{
		p1 *= kage::World::scale();
		p2 *= kage::World::scale();
		headWidth *= kage::World::scale();
		headLength *= kage::World::scale();
		kf::Vec2 dir = p2 - p1;
		dir = normalise(dir);
		kf::Vec2 perp = perpCW(dir);

		sf::Vertex line[] =
		{
			sf::Vertex(p1, c),
			sf::Vertex(p2, c),
			sf::Vertex(p2, c),
			sf::Vertex(p2-dir*headLength+perp*headWidth, c),
			sf::Vertex(p2, c),
			sf::Vertex(p2 - dir * headLength - perp * headWidth, c)
		};
		rt.draw(line, 6, sf::Lines);
	}

}