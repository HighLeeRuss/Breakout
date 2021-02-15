////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_QUATERNION_HEADER
#define KF_QUATERNION_HEADER

#include "kf/kf.h"
#include "kf/kf_vector.h"
#include <ostream>

namespace kf
{
	template<typename T>
	class QuatT
	{
	public:
		typedef T type;

		enum Elements
		{
			W = 0,
			X = 1,
			Y = 2,
			Z = 3
		};
		union
		{
			T c[4];
			struct
			{
				T w;
				T x;
				T y;
				T z;
			};
			struct
			{
				T real;
				Vec<T, 3> xyz;
			};
		};

		QuatT() : w(1), x(0), y(0), z(0)
		{
		}

		QuatT(const T &ww, const T &xx, const T &yy, const T &zz) : w(ww), x(xx), y(yy), z(zz)
		{
		}

		QuatT(const Vec<T,4> &v) : x(v.x), y(v.y), z(v.z), w(v.w)
		{
		}

		QuatT(const T &angle, const kf::Vec<T, 3>&axis)
		{
			kf::Vec<T, 3> naxis = kf::normalise(axis);
			T half = angle / T(2);
			w = cos(half);
			xyz = naxis * sin(half);
		}

		QuatT operator*(const QuatT &q) const
		{
			return QuatT(w * q.w - x * q.x - y * q.y - z * q.z,
				               w * q.x + x * q.w + y * q.z - z * q.y,
				               w * q.y - x * q.z + y * q.w + z * q.x,
				               w * q.z + x * q.y - y * q.x + z * q.w);
		}

		kf::Vec<T, 3> operator*(const kf::Vec<T, 3>&v) const
		{
			kf::Vec<T, 3> uv, uuv;
			kf::Vec<T, 3> qvec(x, y, z);
			uv = qvec.cross(v);
			uuv = qvec.cross(uv);
			uv *= (T(2) * w);
			uuv *= T(2);
			return v + uv + uuv;
		}

		QuatT operator+(const QuatT &q) const
		{
			return QuatT(w + q.w, x + q.x, y + q.y, z + q.z);
		}

		QuatT operator-(const QuatT&q) const
		{
			return QuatT(w - q.w, x - q.x, y - q.y, z - q.z);
		}

		inline QuatT conjugate() const
		{
			return QuatT(-x, -y, -z, w);
		}

		inline float normalise()
		{
			T l;
			l = T(sqrt(x*x + y * y + z * z + w * w));
			if (l != 0.0)
			{
				set(x / l, y / l, z / l, w / l);
			}
			else
			{
				set(0, 0, 0, 1);
			}
			return l;
		}

		friend inline QuatT normalise(const QuatT&q)
		{
			QuatT temp(q);
			temp.normalise();
			return temp;
		}

		inline T length() const
		{
			return sqrt(x*x + y * y + z * z + w * w);
		}

		friend inline T length(const QuatT&q)
		{
			return q.length();
		}

		inline T lengthSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}

		friend inline T lengthSquared(const QuatT&q)
		{
			return q.lengthSquared();
		}

		inline void set(const QuatT&value)
		{
			x = value.x;
			y = value.y;
			z = value.z;
			w = value.w;
		}

		inline void set(T xyzw)
		{
			x = y = z = w = xyzw;
		}

		inline void set(T ww, T xx, T yy, T zz)
		{
			w = ww;
			x = xx;
			y = yy;
			z = zz;
		}

		template<typename T2>
		inline void set(const T2 *p)
		{
			w = T(p[0]);
			x = T(p[1]);
			y = T(p[2]);
			z = T(p[3]);
		}

		inline T dot(const QuatT&q) const
		{
			return x * q.x + y * q.y + z * q.z + w * q.w;
		}

		inline friend T dot(const QuatT&q1, const QuatT&q2)
		{
			return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
		}

		//inline friend std::ostream &operator<<(std::ostream &o, const QuaternionT<T> &q)
		//{
		//	o << "{" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << "}";
		//	return o;
		//}

		//  KF_API static const QuaternionT<T> ZERO;
		//  KF_API static const QuaternionT<T> IDENTITY;
		inline static QuatT identity()
		{
			return QuatT(1, 0, 0, 0);
		}
	};

	template<typename T>
	QuatT<T> conjugate(const QuatT<T> &q)
	{
		return QuatT<T>(q.w, -q.x, -q.y, -q.z);
	}

	template<typename T>
	QuatT<T> normalise(const QuatT<T> &q)
	{
		T mag = q.magnitude();
		return QuatT<T>(q.w / mag, q.x / mag, q.y / mag, q.z / mag);
	}

	template <typename T1, typename T2>
	T1 convertQuaternion(const T2 &q)
	{
		T1 result;
		result.x = q.x;
		result.y = q.y;
		result.z = q.z;
		result.w = q.w;
		return result;
	}
#pragma region IO
	template <typename T>
	inline std::ostream& operator<<(std::ostream& o, const QuatT<T>& q)
	{
		o << "[" << q.w << ",<" << q.x << "," << q.y << "," << q.z << ">]";
		return o;
	}
#pragma endregion

#pragma region Typedefs
	typedef QuatT<float> Quat;
	typedef QuatT<double> Quatd;
	typedef QuatT<float> Quatf;
	typedef QuatT<int> Quati;
#pragma endregion
}
#endif
