////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#pragma once
#include "kf/kf_vector.h"

// Euler angle class.
// It represents a single angle in the range -Pi to Pi.
// It features wrap around for out of range values and degree and radian support.
namespace kf
{
	const float c_radiansToDegrees = 180.0f / 3.14159265f;		// Multiply a radian value by this to get degrees.
	class Euler
	{
	public:
		float angle;

	public:
		Euler(float a = 0) :angle(a)
		{
			wrap();
		}

		Euler(const kf::Vec2 &v) :angle(atan2(v.y, v.x)) {}

		Euler(const Euler &e) :angle(e.angle) {}

		inline Euler &operator=(const Euler &e)
		{
			angle = e.angle;
			return *this;
		}

		// Set the angle using a value in degrees.
		inline Euler &degrees(float a)
		{
			angle = a / c_radiansToDegrees;
			wrap();
			return *this;
		}

		// Set the angle using a value in radians.
		inline Euler &radians(float a)
		{
			angle = a;
			wrap();
			return *this;
		}

		// Return the current angle in degrees.
		inline float degrees()
		{
			return angle * c_radiansToDegrees;
		}

		// Return the current angle in radians.
		inline float radians()
		{
			return angle;
		}

		// Wrap the current angle around to always fit in the -Pi to Pi range.
		inline Euler &wrap()
		{
			angle = wrap(angle);
			return *this;
		}

		// Wrap the given angle around to always fit in the -Pi to Pi range.
		inline static float wrap(float a)
		{
			if (a >= 0)
			{
				a = fmod(a + 3.14159265f, 3.14159265f*2.0f) - 3.14159265f;
			}
			else
			{
				a = fmod(a - 3.14159265f, 3.14159265f*2.0f) + 3.14159265f;
			}
			return a;
		}

		// Add a radian angle.
		inline Euler &operator+=(float a)
		{
			angle += a;
			wrap();
			return *this;
		}

		// Subtract a radian angle.
		inline Euler &operator-=(float a)
		{
			angle -= a;
			wrap();
			return *this;
		}

		// Add a radian angle.
		inline Euler operator+(float a)
		{
			return Euler(angle + a);
		}

		// Subtract a radian angle.
		inline Euler operator-(float a)
		{
			return Euler(angle - a);
		}

		// Return the shortest path rotation to reach a given angle.
		inline float turnTo(const Euler &e)
		{
			return wrap(e.angle - angle);
		}

		// Cast the Euler to a Vector2.
		inline operator kf::Vec2()
		{
			return kf::Vec2(std::cos(angle), std::sin(angle));
		}

		// Convert a Vector2 into a euler angle.
		inline Euler &fromVector(const kf::Vec2 &v)
		{
			angle = atan2(v.y, v.x);
			return *this;
		}

		// Convert the Euler to a Vector2.
		inline kf::Vec2 toVector()
		{
			return kf::Vec2(std::cos(angle), std::sin(angle));
		}

		inline static Euler EulerDegree(float angle)
		{
			return Euler(angle / c_radiansToDegrees);
		}
	};
}
