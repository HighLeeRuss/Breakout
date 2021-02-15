////////////////////////////////////////////////////////////
// KGL - Kojack Graphics Library
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KGL is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KGL_SDF_HEADER
#define KGL_SDF_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector.h"
#include <vector>
#include "kf/kf_log.h"
#include "algorithm"

#pragma warning( disable : 4201)

namespace kgl
{
	inline float sDistanceSphere(const kf::Vector3 &p, float radius)
	{
		return p.length() - radius;
	}

	inline float sDistanceBox(const kf::Vector3 &p, const kf::Vector3 &size)
	{
		kf::Vector3 d = kf::Vector3::abs(p) - size;
		return std::min(std::max(d.x, std::max(d.y, d.z)), 0.0f) + kf::Vector3::maximum(d, kf::Vector3::ZERO()).length();
	}

	inline float sDistanceTorus(const kf::Vector3 &p, float innerRadius, float outerRadius)
	{
		return kf::Vector2(p.xz().length() - innerRadius, p.y).length() - outerRadius;
	}

	inline float sDistanceCylinder(const kf::Vector3 &p, const kf::Vector3 &c)
	{
		return (p.xz() - c.xy()).length() - c.z;
	}

	inline float sDistanceCone(const kf::Vector3 &p, const kf::Vector2 &c)
	{
		return c.dot(kf::Vector2(p.xy().length(), p.z));
	}

	inline float sDistanceCapsule(const kf::Vector3 &p, const kf::Vector3 &a, const kf::Vector3 &b, float radius)
	{
		kf::Vector3 pa = p - a;
		kf::Vector3 ba = b - a;
		float h = kf::clamp(pa.dot(ba) / ba.dot(ba), 0.0f, 1.0f);
		return (pa - ba*h).length() - radius;
	}

	inline float sdfUnion(float d1, float d2)
	{
		return std::min(d1, d2);
	}

	inline float sdfSubtraction(float d1, float d2)
	{
		return std::max(-d1, d2);
	}

	inline float sdfIntersection(float d1, float d2)
	{
		return std::max(d1, d2);
	}
}

#endif

