////////////////////////////////////////////////////////////
// KF - Kojack Graphics Library
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////
// SDF functions based on Inigo Quilez's articles at:
// https://www.iquilezles.org/www/articles/distfunctions2d/distfunctions2d.htm
// https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
////////////////////////////////////////////////////////////

#ifndef KF_SDF_HEADER
#define KF_SDF_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector.h"
#include <vector>
#include "kf/kf_log.h"
#include "algorithm"

#pragma warning( disable : 4201)

namespace kf
{
	// 2D Functions

	namespace sdf
	{
		template <typename TT, typename TT2>
		inline TT circle(const kf::Vec<TT,2>& p, TT2 radius)
		{
			return length(p) - radius;
		}

		template <typename TT>
		inline TT line(const kf::Vec<TT, 2>& p, const kf::Vec<TT,2>& a, const kf::Vec<TT,2>& b)
		{
			kf::Vec<TT, 2> pa = p - a;
			kf::Vec<TT, 2> ba = b - a;
			TT h = kf::clamp(kf::dot(pa, ba) / kf::dot(ba, ba), 0.0f, 1.0f);
			return length(pa-ba*h);
		}

		template <typename TT>
		inline TT box(const kf::Vec<TT, 2>& p, const kf::Vec<TT, 2>& size)
		{
			kf::Vec<TT, 2> d = abs(p) - size;
			return length(maximum(d, kf::Vec<TT, 2>::zero())) + std::min(std::max(d.x, d.y), 0.0f);
		}

		template <typename TT>
		inline TT rhombus(const kf::Vec<TT, 2>& p, const kf::Vec<TT, 2>& size)
		{
			// Curently wrong
			kf::Vec<TT, 2> q = abs(p);
			TT h = kf::clamp((-2.0 * ndot(q, size) + ndot(size, size)) / dot(size, size), -1.0, 1.0);
			TT d = length(q - 0.5 * size * kf::Vec<TT, 2>(1.0 - h, 1.0 + h));
			return d * sign(q.x * size.y + q.y * size.x - size.x * size.y);
		}

		template <typename TT>
		inline TT equilateralTriangle(const kf::Vec<TT, 2>& p)
		{
			TT k = std::sqrt(3.0);
			auto q = p;
			q.set(fabs(p.x) - 1.0f, q.y + 1.0f / k);
			if (q.x + k * q.y > 0.0) 
				q = kf::Vec<TT, 2>(q.x - k * q.y, -k * q.x - q.y) / 2.0f;
			q.x -= kf::clamp(q.x, -2.0f, 0.0f);
			return -length(q) * sign(q.y);
		}

		template <typename TT, typename TT2>
		inline TT unevenCapsule(const kf::Vec<TT, 2>& p, TT2 r1, TT2 r2, TT2 h)
		{
			p.x = fabs(p.x);
			TT b = (r1 - r2) / h;
			TT a = sqrt(1.0 - b * b);
			TT k = kf::dot(p, kf::Vec<TT, 2>(-b, a));
			if (k < 0.0) return length(p) - r1;
			if (k > a * h) return length(p - kf::Vector2(0.0, h)) - r2;
			return dot(p, kf::Vec<TT, 2>(a, b)) - r1;
		}

		template <typename TT>
		inline TT add(TT d1, TT d2)
		{ 
			return std::min(d1, d2); 
		}

		template <typename TT>
		inline TT subtract(TT d1, TT d2)
		{ 
			return std::max(-d1, d2); 
		}

		template <typename TT>
		inline TT intersect(TT d1, TT d2)
		{ 
			return std::max(d1, d2);
		}

		template <typename TT>
		inline TT smoothAdd(TT d1, TT d2, TT k) {
			TT h = kf::clamp(0.5f + 0.5f * (d2 - d1) / k, 0.0f, 1.0f);
			return kf::lerp(d2, d1, h) - k * h * (1.0f - h);
		}

		template <typename TT>
		inline TT smoothSubtract(TT d1, TT d2, TT k) {
			TT h = kf::clamp(0.5f - 0.5f * (d2 + d1) / k, 0.0f, 1.0f);
			return kf::lerp(d2, -d1, h) + k * h * (1.0f - h);
		}

		template <typename TT>
		inline TT smoothIntersect(TT d1, TT d2, TT k) {
			TT h = kf::clamp(0.5f - 0.5f * (d2 - d1) / k, 0.0f, 1.0f);
			return kf::lerp(d2, d1, h) + k * h * (1.0f - h);
		}

		template <typename TT>
		inline kf::Vec<TT, 2> move(const kf::Vec<TT, 2>& p, const kf::Vec<TT, 2>& offset)
		{
			return p - offset;
		}


		// 3D Functions
		template <typename TT, typename TT2>
		inline TT sphere(const kf::Vec<TT, 3>& p, TT2 radius)
		{
			return length(p) - radius;
		}

		template <typename TT>
		inline TT box(const kf::Vec<TT, 3>& p, const kf::Vec<TT, 3>& size)
		{
			kf::Vector3 d = kf::Vector3::abs(p) - size;
			return std::min(std::max(d.x, std::max(d.y, d.z)), 0.0f) + kf::Vector3::maximum(d, kf::Vector3::ZERO()).length();
		}

		template <typename TT, typename TT2>
		inline TT torus(const kf::Vec<TT, 3>& p, TT2 innerRadius, TT2 outerRadius)
		{
			return kf::Vector2(p.xz().length() - innerRadius, p.y).length() - outerRadius;
		}

		template <typename TT>
		inline TT cylinder(const kf::Vec<TT, 3>& p, const kf::Vec<TT, 3>& c)
		{
			return (p.xz() - c.xy()).length() - c.z;
		}

		template <typename TT>
		inline TT cone(const kf::Vec<TT, 3>& p, const kf::Vec<TT, 3>& c)
		{
			return c.dot(kf::Vector2(p.xy().length(), p.z));
		}

		template <typename TT, typename TT2>
		inline TT capsule(const kf::Vec<TT, 3>& p, const kf::Vec<TT, 3>& a, const kf::Vec<TT, 3>& b, TT2 radius)
		{
			kf::Vector3 pa = p - a;
			kf::Vector3 ba = b - a;
			TT2 h = kf::clamp(pa.dot(ba) / ba.dot(ba), 0.0f, 1.0f);
			return (pa - ba*h).length() - radius;
		}

		template <typename TT>
		inline kf::Vec<TT, 3> move(const kf::Vec<TT, 3>& p, const kf::Vec<TT, 3>& offset)
		{
			return p - offset;
		}

	}
}

#endif

