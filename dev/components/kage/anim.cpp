////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage/anim.h"

namespace kage
{
	AnimSequence::AnimSequence():m_looping(true)
	{
	}

	AnimSequence::AnimSequence(int start, int end, float length, bool looping):m_start(start), m_end(end), m_length(length), m_looping(looping)
	{
	}

	AnimSequence::~AnimSequence()
	{
	}

	AnimSequence &AnimSequence::looping(bool l)
	{
		m_looping = l;
		return *this;
	}

	bool AnimSequence::looping()
	{
		return m_looping;
	}


	Anim::Anim(sf::Sprite *sprite, int startX, int startY, int frameWidth, int frameHeight, int columns, int rows): 
		m_sprite(sprite), 
		m_startX(startX), 
		m_startY(startY), 
		m_frameWidth(frameWidth), 
		m_frameHeight(frameHeight), 
		m_columns(columns), 
		m_rows(rows),
		m_playing(false),
		m_frame(0),
		m_time(0)
	{
		setFrame(0);
	}

	Anim::~Anim()
	{
	}

	Anim &Anim::addSequence(const std::string &name, int frameStart, int frameEnd, float length, bool looping)
	{
		AnimSequence as(frameStart, frameEnd, length, looping);
		m_sequences[name] = as;
		return *this;
	}

	bool Anim::isPlaying() const
	{
		return m_playing;
	}

	Anim &Anim::setFrame(int f)
	{
		m_frame = f;
		if(m_frame >= m_rows * m_columns)
			m_frame = m_rows * m_columns - 1;
		int c = m_frame % m_columns;
		int r = m_frame / m_columns;
		if(m_sprite)
			m_sprite->setTextureRect(sf::IntRect(m_startX + c * m_frameWidth, m_startY + r * m_frameHeight, m_frameWidth, m_frameHeight));
		return *this;
	}

	int Anim::getFrame() const
	{
		return m_frame;
	}

	Anim &Anim::update(float deltaT)
	{
		if(m_playing && m_current != m_sequences.end())
		{
			m_time += deltaT;
			if(m_time < 0)
			{
				if(m_current->second.m_looping)
				{
					m_time = fmod(m_time, m_current->second.m_length) + m_current->second.m_length;
				}
				else
				{
					m_time = 0;
					m_playing = false;
				}
			}
			else if(m_time >= m_current->second.m_length)
			{
				if(m_current->second.m_looping)
				{
					m_time = fmod(m_time, m_current->second.m_length);
				}
				else
				{
					m_time = m_current->second.m_length;
					m_playing = false;
					setFrame(m_current->second.m_end);
					return *this;
				}
			}
			setFrame(int(((m_current->second.m_end - m_current->second.m_start + 1) / m_current->second.m_length) * m_time + m_current->second.m_start));
		}
		return *this;
	}

	Anim &Anim::play(const std::string &name, bool restart)
	{
		m_current = m_sequences.find(name);
		if(restart)
		{
			m_frame = 0;
			m_time = 0;
		}
		m_playing = true;
		return *this;
	}

	AnimSequence *Anim::getSequence(const std::string &name)
	{
		std::map<std::string, AnimSequence>::iterator it = m_sequences.find(name);
		if(it!=m_sequences.begin())
		{
			return &(it->second);
		}
		return 0;
	}

	Anim &Anim::stop()
	{
		m_playing = false;
		return *this;
	}

	Anim &Anim::setPlaying(bool play)
	{
		m_playing = play;
		return *this;
	}

	Anim::Anim():m_sprite(0),
		m_startX(0), 
		m_startY(0), 
		m_frameWidth(0), 
		m_frameHeight(0), 
		m_columns(0), 
		m_rows(0),
		m_playing(false),
		m_frame(0),
		m_time(0)
	{
	}

	Anim &Anim::setSprite(sf::Sprite *sprite)
	{
		m_sprite = sprite;
		return *this;
	}

	Anim &Anim::setStartPos(int startX, int startY)
	{
		m_startX = startX;
		m_startY = startY;
		return *this;
	}

	Anim &Anim::setFrameSize(int frameWidth, int frameHeight)
	{
		m_frameWidth = frameWidth;
		m_frameHeight = frameHeight;
		return *this;
	}

	Anim &Anim::setGridSize(int columns, int rows)
	{
		m_columns = columns;
		m_rows = rows;
		return *this;
	}

	sf::Sprite *Anim::getSprite() const
	{
		return m_sprite;
	}

	int Anim::getFrameWidth() const
	{
		return m_frameWidth;
	}
	
	int Anim::getFrameHeight() const
	{
		return m_frameHeight;
	}


}