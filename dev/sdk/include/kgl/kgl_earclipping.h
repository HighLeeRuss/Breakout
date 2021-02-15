////////////////////////////////////////////////////////////
// KGL - Kojack Graphics Library
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KGL is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KGL_EARCLIPPING_HEADER
#define KGL_EARCLIPPING_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector.h"
#include <vector>
#include "kf/kf_log.h"

#pragma warning( disable : 4201)

namespace kgl
{
	class Polygon
	{
	public:
		std::vector<kf::Vector2> m_positions;
		void add(kf::Vector2 p)
		{
			m_positions.push_back(p);
		}
	};

	inline std::vector<unsigned int> earClip(Polygon &poly)
	{
		unsigned int count = poly.m_positions.size();
		unsigned int start = 0;
		unsigned int current = 0;
		std::vector<unsigned int> indexOrder;
		std::vector<unsigned int> nextIndex;
		for (int i = 0;i < count;++i)
		{
			nextIndex.push_back((i + 1)%count);
		}
		while (count>2)
		{
			kf_log("Pass. Count = "<<count);
			do
			{
				unsigned int i1 = current;
				unsigned int i2 = nextIndex[i1];
				unsigned int i3 = nextIndex[i2];

				if (count == 3)
				{
					indexOrder.push_back(i1);
					indexOrder.push_back(i2);
					indexOrder.push_back(i3);
					return indexOrder;
				}
				kf::Vector2 p1 = poly.m_positions[i1];
				kf::Vector2 p2 = poly.m_positions[i2];
				kf::Vector2 p3 = poly.m_positions[i3];
				kf::Vector2 perp = (p2 - p1).perpCCW();
				float d = perp.dot(p3 - p1);
				kf_log("Vertex " << i2 << (d >= 0 ? " convex" : " concave"));
				if (d >= 0) // convex ear
				{
					kf::Vector2 perp1 = (p3 - p1).perpCCW();
					unsigned int colIndex = nextIndex[i3];
					bool intersect = false;
					while (nextIndex[colIndex] != i1)
					{
						kf::Vector2 p4 = poly.m_positions[colIndex];
						kf::Vector2 p5 = poly.m_positions[nextIndex[colIndex]];
						kf::Vector2 perp2 = (p5 - p4).perpCCW();
						if (kf::sign(perp1.dot(p5 - p1)) != kf::sign(perp1.dot(p4 - p1)))
						{
							if (kf::sign(perp2.dot(p1 - p4)) != kf::sign(perp2.dot(p3 - p4)))
							{
								intersect = true;
								break;
							}

						}
						colIndex = nextIndex[colIndex];
					}
					if (!intersect)
					{
						indexOrder.push_back(i1);
						indexOrder.push_back(i2);
						indexOrder.push_back(i3);
						if (i2 == start)
						{
							start = i3;
						}
						nextIndex[i1] = i3;
						count--;
					}
				}
				current = nextIndex[i1];
			} while (current != start);
		}
		return indexOrder;
	}
}

#endif

