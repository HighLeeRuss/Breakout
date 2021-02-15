////////////////////////////////////////////////////////////
// KGL - Kojack Graphics Library
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KGL is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KGL_SVG_HEADER
#define KGL_SVG_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector.h"
#include <vector>
#include <string>
#include "kf/kf_log.h"
#include "kf/kf_bounds.h"

#pragma warning( disable : 4201)

namespace kgl
{
	class SVGStyle
	{
	public:
		unsigned int m_colourFill;
		unsigned int m_colourStroke;
		float m_thickness;
		float m_fontSize;
		float m_fillOpacity;
		bool m_hasStroke = false;
		bool m_hasFill = false;
		bool m_hasThickness = false;
		bool m_hasFontSize = false;
		bool m_fillNotNone = false;
		bool m_strokeNotNone = false;
		bool m_hasFillOpacity = false;

		
		SVGStyle() :m_colourFill(0xffffff), m_colourStroke(0x000000), m_thickness(1.0f), m_fontSize(18),m_fillOpacity(1.0f)
		{
		}
		
		SVGStyle &fillOpacity(float opacity)
		{
			m_fillOpacity = opacity;
			m_hasFillOpacity = true;
			return *this;
		}

		SVGStyle &fontSize(float size)
		{
			m_fontSize = size;
			m_hasFontSize = true;
			return *this;
		}

		SVGStyle &thickness(float t)
		{
			m_thickness = t;
			m_hasThickness = true;
			return *this;
		}

		SVGStyle &fill(unsigned int col)
		{
			m_colourFill = col;
			m_hasFill = true;
			m_fillNotNone = true;
			return *this;
		}

		SVGStyle &drawFill(bool b)
		{
			m_fillNotNone = b;
			m_hasFill = true;
			return *this;
		}

		SVGStyle &stroke(unsigned int col)
		{
			m_colourStroke = col;
			m_hasStroke = true;
			m_strokeNotNone = true;
			return *this;
		}

		SVGStyle &drawStroke(bool b)
		{
			m_strokeNotNone = b;
			m_hasStroke = true;
			return *this;
		}

		std::string rgbColour(unsigned int c)
		{
			return std::string("rgb(") + std::to_string((c >> 16) & 0xff) + "," + std::to_string((c >> 8) & 0xff) + "," + std::to_string((c) & 0xff) + ")";
		}

		std::string toString()
		{
			std::stringstream ss;
			ss << " style=\"";
			if (m_hasFill)
			{
				if (m_fillNotNone)
					ss << "fill:" << rgbColour(m_colourFill) << ";";
				else
					ss << "fill:none;";
			}
			if (m_hasStroke)
			{
				if (m_strokeNotNone)
					ss << "stroke:" << rgbColour(m_colourStroke) << ";";
				else
					ss << "stroke:none;";
			}
			if (m_hasThickness)
			{
				ss << "stroke-width:" << m_thickness << "px;";
			}
			if (m_hasFontSize)
			{
				ss << "font-size:" << m_fontSize << "px;";
			}
			if (m_hasFillOpacity)
			{
				ss << "fill-opacity:" << m_fillOpacity << ";";
				ss << "stroke-opacity:" << m_fillOpacity << ";";
			}
			ss << "\"";
			return ss.str();
		}
		
		SVGStyle merge(SVGStyle &s)
		{
			SVGStyle style(*this);

			if (s.m_hasFill)
			{
				style.fill(s.m_colourFill);
				style.drawFill(s.m_fillNotNone);
			}
			if (s.m_hasStroke)
			{
				style.stroke(s.m_colourStroke);
				style.drawStroke(s.m_strokeNotNone);
			}
			if (s.m_hasFontSize)
			{
				style.fontSize(s.m_fontSize);
			}
			if (s.m_hasFillOpacity)
			{
				style.fillOpacity(s.m_fillOpacity);
			}
			if (s.m_hasThickness)
			{
				style.thickness(s.m_thickness);
			}

			return style;
		}
	};

	class SVG
	{
	public:
		std::string m_source;
		float m_width;
		float m_height;
		kf::Vector2 m_viewboxPos;
		kf::Vector2 m_viewbowSize;
		std::vector<SVGStyle> m_styleStack;
		SVGStyle m_style;
		kf::AABB2 m_aabb;

		SVG() :m_width(0), m_height(0), m_viewboxPos(0, 0), m_viewbowSize(1, 1)
		{
		}
		
		SVG &clear()
		{
			m_source = "a";
			return *this;
		}

		SVG &pushStyle()
		{
			m_styleStack.push_back(m_style);
			return *this;
		}

		SVG &popStyle()
		{
			if (m_styleStack.size() > 0)
			{
				m_style = m_styleStack.back();
				m_styleStack.pop_back();
			}
			return *this;
		}

		std::string toString()
		{
			std::stringstream ss;
			ss << "<svg width=\"";
			if(m_width != 0)
				ss << m_width;
			else
				ss << "100%";
			ss << "\" height=\"";
			if (m_height != 0)
				ss << m_height;
			else
				ss << "100%";
			ss << "\" viewBox=\"" << m_viewboxPos.x << " " << m_viewboxPos.y << " " << m_viewbowSize.x << " " << m_viewbowSize.y <<"\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n";
			ss << m_source;
			ss << "</svg>\n";
			return ss.str();
		}

		SVG &circle(kf::Vector2 pos, float radius)
		{
			return circle(pos, radius, m_style);
		}

		SVG &circle(kf::Vector2 pos, float radius, SVGStyle style)
		{
			std::stringstream ss;
			style = m_style.merge(style);
			m_aabb.merge(pos + kf::Vector2(radius, 0));
			m_aabb.merge(pos + kf::Vector2(-radius, 0));
			m_aabb.merge(pos + kf::Vector2(0,radius));
			m_aabb.merge(pos + kf::Vector2(0,-radius));

			ss << "<circle cx=\"" << pos.x << "\" cy=\"" << pos.y << "\" r=\"" << radius
				<< "\" "<<style.toString()<<" />\n";
			m_source += ss.str();
			return *this;
		}

		SVG &rect(kf::Vector2 pos, kf::Vector2 size)
		{
			return rect(pos, size, m_style);
		}

		SVG &rect(kf::Vector2 pos, kf::Vector2 size, SVGStyle style)
		{
			std::stringstream ss; 
			style = m_style.merge(style);
			m_aabb.merge(kf::AABB2(pos, pos + size));

			ss << "<rect x=\"" << pos.x << "\" y=\"" << pos.y << "\" width=\"" << size.x << "\" height=\"" << size.y
				<< "\" " << style.toString() << " />\n";
			m_source += ss.str();
			return *this;
		}
		
		SVG &line(kf::Vector2 start, kf::Vector2 end)
		{
			return line(start, end, m_style);
		}

		SVG &line(kf::Vector2 start, kf::Vector2 end, SVGStyle style)
		{
			std::stringstream ss;
			style = m_style.merge(style);
			m_aabb.merge(start).merge(end);

			ss << "<line x1=\"" << start.x << "\" y1=\"" << start.y << "\" x2=\"" << end.x << "\" y2=\"" << end.y
				<< "\" " << style.toString() << " />\n";
			m_source += ss.str();
			return *this;
		}

		SVG &text(kf::Vector2 pos, std::string s)
		{
			return text(pos, s, m_style);
		}

		SVG &text(kf::Vector2 pos, std::string s, SVGStyle style)
		{
			style = m_style.merge(style);
			std::stringstream ss;
			m_aabb.merge(pos);
			ss << "<text x=\"" << pos.x << "\" y=\"" << pos.y << "\" " << style.toString() << " >"<<s<<"</text>\n";
			m_source += ss.str();
			return *this;
		}

		SVG &thickness(float t)
		{
			m_style.thickness(t);
			return *this;
		}

		SVG &fill(unsigned int col)
		{
			m_style.fill(col);
			return *this;
		}

		SVG &drawFill(bool b)
		{
			m_style.drawFill(b);
			return *this;
		}

		SVG &stroke(unsigned int col)
		{
			m_style.stroke(col);
			return *this;
		}

		SVG &drawStroke(bool b)
		{
			m_style.drawStroke(b);
			return *this;
		}

		SVG &width(float w)
		{
			m_width = w;
			return *this;
		}

		SVG &height(float h)
		{
			m_height = h;
			return *this;
		}

		SVG &viewboxPos(kf::Vector2 pos)
		{
			m_viewboxPos = pos;
			return *this;
		}

		SVG &viewboxSize(kf::Vector2 size)
		{
			m_viewbowSize = size;
			return *this;
		}

		SVG &polygon(const std::vector<kf::Vector2> &points)
		{

			return polygon(points, m_style);
		}

		SVG &polygon(const std::vector<kf::Vector2> &points, SVGStyle style)
		{
			std::stringstream ss;
			style = m_style.merge(style);
			ss << "<polygon points=\"";
			for (int i = 0;i < points.size();++i)
			{
				ss << points[i].x << "," << points[i].y << " ";
				m_aabb.merge(points[i]);
			}
			ss << "\" " << style.toString() << " />\n";
			m_source += ss.str();
			return *this;
		}

		SVG &fitBounds()
		{
			if (!m_aabb.infinite)
			{
				m_viewboxPos = m_aabb.minCorner;
				m_viewbowSize = m_aabb.size();
				//m_width = m_aabb.width();
				//m_height = m_aabb.height();
			}
			return *this;
		}

		kf::AABB2 getBounds() const
		{
			return m_aabb;
		}

		/*
		SVG &clear()
		{
			return *this;
		}
*/
	};

}

#endif

