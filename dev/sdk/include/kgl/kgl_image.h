////////////////////////////////////////////////////////////
// KGL - Kojack Graphics Library
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KGL is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KGL_IMAGE_HEADER
#define KGL_IMAGE_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector.h"
#include <vector>
#include <string>
#include "kf/kf_log.h"
#include "kf/kf_bounds.h"
#include <fstream>

//#pragma warning( disable : 4201)

namespace kgl
{
	const unsigned int c_SSE_ALIGNMENT = 16;

	class Image
	{
	public:
		kf::ColourRGBA *m_buffer;
		unsigned int m_width;
		unsigned int m_height;
		kf::ColourRGBA m_edgeColour;
		static kf::ColourRGBA m_dummy;

		Image(): m_width(0), m_height(0), m_buffer(0)
		{

		}

		Image(unsigned int width, unsigned int height): m_buffer(0)
		{
			create(width, height);
		}

		~Image()
		{
			release();
		}

		unsigned int getWidth() const
		{
			return m_width;
		}

		unsigned int getHeight() const
		{
			return m_height;
		}

		bool create(unsigned int width, unsigned int height)
		{
			if (m_buffer)
			{
				// Reuse the buffer if the same size is requested.
				if (width == m_width && height == m_height)
				{
					return true;
				}
				release();
			}
			if (width > 0 && height > 0)
			{
				m_buffer = static_cast<kf::ColourRGBA *>(_aligned_malloc(width*height*sizeof(kf::ColourRGBA), c_SSE_ALIGNMENT));
				if (!m_buffer)
				{
					return false;
				}
				m_width = width;
				m_height = height;
				clear(kf::ColourRGBA::ZERO());
				return true;
			}
			else
			{
				m_buffer = 0;
				m_width = 0;
				m_height = 0;
				return false;
			}
		}

		void release()
		{
			if (m_buffer)
			{
				_aligned_free(m_buffer);
			}
			m_buffer = 0;
			m_width = 0;
			m_height = 0;
		}

		void clear(const kf::ColourRGBA &c)
		{
			if (m_buffer)
			{
				for (unsigned int y = 0; y < m_height; ++y)
				{
					for (unsigned int x = 0; x < m_width; ++x)
					{
						m_buffer[x + y*m_width] = c;
					}
				}
			}
		}

		kf::ColourRGBA &operator()(unsigned int x, unsigned int y)
		{
			if (m_buffer && x < m_width && y < m_height)
			{
				return m_buffer[x + y * m_width];
			}
			return m_dummy;
		}

		const kf::ColourRGBA &operator()(unsigned int x, unsigned int y) const
		{
			if (m_buffer && x < m_width && y < m_height)
			{
				return m_buffer[x + y * m_width];
			}
			return m_dummy;
		}


#pragma pack(push,1)
	struct TGAHeader
	{
		char idFieldSize;
		char colourType;
		char imageType;
		char colourMap[5];
		unsigned short xOrigin;
		unsigned short yOrigin;
		unsigned short width;
		unsigned short height;
		char bpp;
		char descriptor;
	};
#pragma pack(pop)

	bool save(const char *filename, bool hdr)
	{
		if (hdr)
		{
			std::fstream out(std::string(filename) + ".pfm", std::ios::out | std::ios::binary);
			if (!out.good())
				return false;
			out << "PF" << std::endl;
			out << getWidth() << " " << getHeight() << std::endl;
			out << "-1" << std::endl;
			for (int y = getHeight() - 1; y >= 0; --y)
			{
				for (unsigned int x = 0; x < getWidth(); ++x)
				{
					kf::ColourRGBA c = (*this)(x, y);
					out.write((const char *)&c.r, 4);
					out.write((const char *)&c.g, 4);
					out.write((const char *)&c.b, 4);
				}
			}
			out.close();
		}
		else
		{
			std::fstream out(std::string(filename) + ".tga", std::ios::out | std::ios::binary);
			if (!out.good())
				return false;
			TGAHeader h;
			memset(&h, 0, sizeof(TGAHeader));
			h.idFieldSize = 0;
			h.colourType = 0;
			h.imageType = 2;
			h.xOrigin = 0;
			h.yOrigin = 0;
			h.width = (unsigned short)getWidth();
			h.height = (unsigned short)getHeight();
			h.descriptor = 40;
			h.bpp = 32;

			out.write((const char *)&h, sizeof(TGAHeader));
			for (unsigned int y = 0; y < getHeight(); ++y)
			{
				for (unsigned int x = 0; x < getWidth(); ++x)
				{
					kf::ColourRGBA c = (*this)(x, y);
					c = c.clamp(0, 1);
					out << (unsigned char(c.b * 255));
					out << (unsigned char(c.g * 255));
					out << (unsigned char(c.r * 255));
					out << (unsigned char(c.a * 255));
				}
			}
			out.close();
		}

	};


}

#endif

