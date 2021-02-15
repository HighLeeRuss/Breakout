////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_ANIM_HEADER
#define KAGE_ANIM_HEADER
#include "kf/kf_vector.h"
#include <SFML/Graphics.hpp>

namespace kage
{
	class AnimSequence
	{
	public:
		AnimSequence();
		AnimSequence(int start, int end, float length, bool looping);
		virtual ~AnimSequence();
		virtual AnimSequence &looping(bool l);
		virtual bool looping();
		std::string m_name;
		int m_start;
		int m_end;
		float m_length;
		bool m_looping;
	};

	class Anim
	{
	public:
		Anim();
		Anim(sf::Sprite *sprite, int startX, int startY, int frameWidth, int frameHeight, int columns, int rows);
		virtual ~Anim();
		virtual Anim &setSprite(sf::Sprite *sprite);
		virtual Anim &setStartPos(int startX, int startY);
		virtual Anim &setFrameSize(int frameWidth, int frameHeight);
		virtual Anim &setGridSize(int columns, int rows);
		virtual Anim &addSequence(const std::string &name, int frameStart, int frameEnd, float length, bool looping);
		virtual bool isPlaying() const;
		virtual Anim &setFrame(int f);
		virtual int getFrame() const;
		virtual Anim &update(float deltaT);
		virtual Anim &play(const std::string &name, bool restart);
		virtual Anim &stop();
		virtual Anim &setPlaying(bool play);
		virtual AnimSequence *getSequence(const std::string &name);
		virtual sf::Sprite *getSprite() const;
		virtual int getFrameWidth() const;
		virtual int getFrameHeight() const;

	protected:
		sf::Sprite *m_sprite;
		bool m_playing;
		int m_startX, m_startY;
		int m_frameWidth, m_frameHeight;
		int m_columns, m_rows;
		int m_frame;
		float m_time;
		std::map<std::string, AnimSequence> m_sequences;
		std::map<std::string, AnimSequence>::iterator m_current;
	};
}
#endif
