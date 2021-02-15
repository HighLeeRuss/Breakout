////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_MATRIX_HEADER
#define KF_MATRIX_HEADER

#include "kf/kf.h"
#include "kf/kf_vector.h"
//#include "kf/kf_matrix3.h"
//#include "kf/kf_matrix4.h"
#include <ostream>

namespace kf
{
	template<typename TT, int DIM>
	struct Mat
	{
		static_assert(sizeof(TT) == 0, "Invalid Matrix dimensions. Only 2D, 3D and 4D matrices supported.");
	};

#pragma region Dimension Specialisation
	template <typename TT> struct Mat<TT, 2>
	{
		union
		{
			TT c[2*2];
			Vec<TT, 2> row[2];
		};
		Mat() : c{ 0, 0, 0, 0 } {}
		Mat(TT c11, TT c12, TT c21, TT c22) : c{ c11, c12, c21, c22 } {}
		explicit Mat(const TT* p) : c{ p[0], p[1], p[2], p[3] } {}
		static Mat identity() { return Mat(TT(1), TT(0), TT(0), TT(1)); }
		Vec<TT, 2> column(unsigned int i) { return Vec<TT, 2>(c[i], c[i + 4]); }
		Mat& setColumn(unsigned int i, const Vec<TT, 2>& v) { c[i] = v.x; c[i + 4] = v.y; return *this; }
		Vec<TT, 2>& operator[](unsigned int r) { return row[r]; }
		TT& operator()(int j, int i) { return c[j * DIM + i]; }
		const TT& operator()(int j, int i) const { return c[j * DIM + i]; }
		inline Mat<TT, 2>& operator=(const Mat<TT, 2>& a)
		{
			c[0] = a.c[0]; c[1] = a.c[1]; 
			c[2] = a.c[2]; c[3] = a.c[3];
			return *this;
		}

	};

	template <typename TT> struct Mat<TT, 3>
	{
		union
		{
			TT c[3 * 3];
			Vec<TT, 3> row[3];
		};
		Mat() : c{ 0, 0, 0, 0, 0, 0, 0, 0, 0 } {}
		Mat(TT c11, TT c12, TT c13, TT c21, TT c22, TT c23, TT c31, TT c32, TT c33) : c{ c11, c12, c13, c21, c22, c23, c31, c32, c33 } {}
		explicit Mat(const TT* p) : c{ p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8] } {}
		static Mat identity() { return Mat(TT(1), TT(0), TT(0), TT(0), TT(1), TT(0), TT(0), TT(0), TT(1)); }
		Vec<TT, 3> column(unsigned int i) { return Vec<TT, 3>(c[i], c[i + 4], c[i + 8]); }
		Mat& setColumn(unsigned int i, const Vec<TT, 2>& v) { c[i] = v.x; c[i + 4] = v.y; return *this; }
		Mat& setColumn(unsigned int i, const Vec<TT, 3>& v) { c[i] = v.x; c[i + 4] = v.y; c[i + 8] = v.z; return *this; }
		Vec<TT, 3>& operator[](unsigned int r) { return row[r]; }
		TT& operator()(int j, int i) { return c[j * DIM + i]; }
		const TT& operator()(int j, int i) const { return c[j * DIM + i]; }
		inline Mat<TT, 3>& operator=(const Mat<TT, 3>& a)
		{
			c[0] = a.c[0]; c[1] = a.c[1]; c[2] = a.c[2]; 
			c[3] = a.c[3]; c[4] = a.c[4]; c[5] = a.c[5]; 
			c[6] = a.c[6]; c[7] = a.c[7]; c[8] = a.c[8]; 
			return *this;
		}
	};

	template <typename TT> struct Mat<TT, 4>
	{
		union
		{
			TT c[4 * 4];
			Vec<TT, 4> row[4];
		};
		Mat() : c{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } {}
		Mat(TT c11, TT c12, TT c13, TT c14, TT c21, TT c22, TT c23, TT c24, TT c31, TT c32, TT c33, TT c34, TT c41, TT c42, TT c43, TT c44) : c{ c11, c12, c13, c14, c21, c22, c23, c24, c31, c32, c33, c34, c41, c42, c43, c44 } {}
		Mat(const Mat& m) : c{ m.c[0], m.c[1], m.c[2], m.c[3], m.c[4], m.c[5], m.c[6], m.c[7], m.c[8], m.c[9], m.c[10], m.c[11], m.c[12], m.c[13], m.c[14], m.c[15] } {}
		explicit Mat(const TT* p) : c{ p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15] } {}
		static Mat identity() { return Mat(TT(1), TT(0), TT(0), TT(0), TT(0), TT(1), TT(0), TT(0), TT(0), TT(0), TT(1), TT(0), TT(0), TT(0), TT(0), TT(1)); }
		Vec<TT, 4> column(unsigned int i) { return Vec<TT, 4>(c[i], c[i + 4], c[i + 8], c[i + 12]); }
		Mat& setColumn(unsigned int i, const Vec<TT, 2>& v) { c[i] = v.x; c[i + 4] = v.y; return *this; }
		Mat& setColumn(unsigned int i, const Vec<TT, 3>& v) { c[i] = v.x; c[i + 4] = v.y; c[i + 8] = v.z; return *this; }
		Mat& setColumn(unsigned int i, const Vec<TT, 4>& v) { c[i] = v.x; c[i + 4] = v.y; c[i + 8] = v.z; c[i + 12] = v.w; return *this; }
		Vec<TT, 4>& operator[](unsigned int r) { return row[r]; }
		TT& operator()(int j, int i) { return c[j * DIM + i]; }
		const TT& operator()(int j, int i) const { return c[j * DIM + i]; }
		inline Mat<TT, 4>& operator=(const Mat<TT, 4>& a)
		{
			c[0] = a.c[0]; c[1] = a.c[1]; c[2] = a.c[2]; c[3] = a.c[3];
			c[4] = a.c[4]; c[5] = a.c[5]; c[6] = a.c[6]; c[7] = a.c[7];
			c[8] = a.c[8]; c[9] = a.c[9]; c[10] = a.c[10]; c[11] = a.c[11];
			c[12] = a.c[12]; c[13] = a.c[13]; c[14] = a.c[14]; c[15] = a.c[15];
			return *this;
		}
	};
	/*
#define KFMATDOT2(i, y, x) m.c[i] = a.c[0+y*DIM] * b.c[x+0*DIM] + a.c[1+y*DIM] * b.c[x+1*DIM];
#define KFMATDOT3(i, y, x) m.c[i] = a.c[0+y*DIM] * b.c[x+0*DIM] + a.c[1+y*DIM] * b.c[x+1*DIM] + a.c[2+y*DIM] * b.c[x+2*DIM];
#define KFMATDOT4(i, y, x) m.c[i] = a.c[0+y*DIM] * b.c[x+0*DIM] + a.c[1+y*DIM] * b.c[x+1*DIM] + a.c[2+y*DIM] * b.c[x+2*DIM] + a.c[3+y*DIM] * b.c[x+3*DIM];
	template <typename TT, int DIM>
	Mat<TT, DIM> operator*(const Mat<TT, DIM>& a, const Mat<TT, DIM>& b)
	{
		Mat<TT, DIM> m;
			if constexpr (DIM == 2)
			{
				KFMATDOT2(0, 0, 0); KFMATDOT2(1, 0, 1);
				KFMATDOT2(2, 1, 0);	KFMATDOT2(3, 1, 1);
			}
			if constexpr (DIM == 3)
			{
				KFMATDOT2(0, 0, 0); KFMATDOT2(1, 0, 1); KFMATDOT2(2, 0, 2);
				KFMATDOT2(3, 1, 0); KFMATDOT2(4, 1, 1); KFMATDOT2(5, 0, 2);
				KFMATDOT2(6, 2, 0); KFMATDOT2(7, 2, 1); KFMATDOT2(8, 0, 2);
			}
			if constexpr (DIM == 4)
			{
				KFMATDOT2(0, 0, 0); KFMATDOT2(1, 0, 1); KFMATDOT2(2, 0, 2); KFMATDOT2(3, 0, 3);
				KFMATDOT2(4, 1, 0); KFMATDOT2(5, 1, 1); KFMATDOT2(6, 1, 2); KFMATDOT2(7, 1, 3);
				KFMATDOT2(8, 2, 0); KFMATDOT2(9, 2, 1); KFMATDOT2(10, 2, 2); KFMATDOT2(11, 2, 3);
				KFMATDOT2(12, 3, 0); KFMATDOT2(13, 3, 1); KFMATDOT2(14, 3, 2); KFMATDOT2(15, 3, 3);
			}
		return m;
	}
#undef KFMATDOT2
#undef KFMATDOT3
#undef KFMATDOT4
	*/
	template <typename TT, int DIM>
	Mat<TT, DIM> operator*(const Mat<TT, DIM> & a, const Mat<TT, DIM> & b)
	{
		Mat<TT, DIM> m;
		for (int y = 0; y < DIM; ++y)
		{
			for (int x = 0; x < DIM; ++x)
			{
				if constexpr (DIM == 2)
					m.c[x + y * DIM] = a.c[0 + y * DIM] * b.c[x + 0 * DIM] + a.c[1 + y * DIM] * b.c[x + 1 * DIM];
				if constexpr (DIM == 3)
					m.c[x + y * DIM] = a.c[0 + y * DIM] * b.c[x + 0 * DIM] + a.c[1 + y * DIM] * b.c[x + 1 * DIM] + a.c[2 + y * DIM] * b.c[x + 2 * DIM];
				if constexpr (DIM == 4)
					m.c[x + y * DIM] = a.c[0 + y * DIM] * b.c[x + 0 * DIM] + a.c[1 + y * DIM] * b.c[x + 1 * DIM] + a.c[2 + y * DIM] * b.c[x + 2 * DIM] + a.c[3 + y * DIM] * b.c[x + 3 * DIM];
			}
		}
		return m;
	}

	template <typename TT>
	Mat<TT, 3> makeTranslation3LH(const Vec<TT, 2>& v)
	{
		return Mat<TT, 3>(1, 0, v.x,  0, 1, v.y,  0, 0, 1);
	}

	template <typename TT>
	Mat<TT, 3> makeTranslation3RH(const Vec<TT, 2>& v)
	{
		return Mat<TT, 3>(1, 0, 0, 0, 1, 0, v.x, v.y, 1);
	}

	template <typename TT>
	Mat<TT, 4> makeTranslation4LH(const Vec<TT, 3>& v)
	{
		return Mat<TT, 4>(1, 0, 0, v.x, 0, 1, 0, v.y, 0, 0, 1, v.z, 0, 0, 0, 1);
	}

	template <typename TT>
	Mat<TT, 4> makeTranslation4RH(const Vec<TT, 3>& v)
	{
		return Mat<TT, 4>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, v.x, v.y, v.z, 1);
	}

	template <typename TT>
	Mat<TT, 2> transpose(const Mat<TT, 2>& m)
	{
		return Mat<TT, 2>(m.c[0], m.c[2], m.c[1], m.c[3]);
	}
	template <typename TT>
	Mat<TT, 3> transpose(const Mat<TT, 3>& m)
	{
		return Mat<TT, 3>(m.c[0], m.c[3], m.c[6], m.c[1], m.c[4], m.c[7], m.c[2], m.c[5], m.c[8]);
	}
	template <typename TT>
	Mat<TT, 4> transpose(const Mat<TT, 4>& m)
	{
		return Mat<TT, 4>(m.c[0], m.c[4], m.c[8], m.c[12], m.c[1], m.c[5], m.c[9], m.c[13], m.c[2], m.c[6], m.c[10], m.c[14], m.c[3], m.c[7], m.c[11], m.c[15]);
	}

#pragma region IO
	template <typename TT, int DIM>
	inline std::ostream& operator<<(std::ostream& o, const Mat<TT, DIM>& a)
	{

		o << "[";
		for (int y = 0; y < DIM; ++y)
		{
			o << "[";
			for (int x = 0; x < DIM; ++x)
			{
				o << a.c[x + y * DIM];
				if (x < DIM - 1)
					o << ",";
			}
			o << "]";
			if (y < DIM - 1)
				o << ",";
		}
		o << "]";
		return o;
	}
#pragma endregion

#pragma region Typedefs
	typedef Mat<float,  2> Mat2;
	typedef Mat<float,  2> Mat2f;
	typedef Mat<double, 2> Mat2d;
	typedef Mat<int,    2> Mat2i;
	typedef Mat<bool,   2> Mat2b;

	typedef Mat<float,  3> Mat3;
	typedef Mat<float,  3> Mat3f;
	typedef Mat<double, 3> Mat3d;
	typedef Mat<int,    3> Mat3i;
	typedef Mat<bool,   3> Mat3b;

	typedef Mat<float,  4> Mat4;
	typedef Mat<float,  4> Mat4f;
	typedef Mat<double, 4> Mat4d;
	typedef Mat<int,    4> Mat4i;
	typedef Mat<bool,   4> Mat4b;
#pragma endregion

	
	/*
   inline kf::Matrix3 convertMatrix4ToMatrix3(const kf::Matrix4 &mat)
   {
      return kf::Matrix3(
         mat.m[0][0],mat.m[0][1],mat.m[0][2],
         mat.m[1][0],mat.m[1][1],mat.m[1][2],
         mat.m[2][0],mat.m[2][1],mat.m[2][2]);
   }

   inline kf::Matrix4 convertMatrix3ToMatrix4(const kf::Matrix3 &mat)
   {
      return kf::Matrix4(
         mat.m[0][0],mat.m[0][1],mat.m[0][2],0,
         mat.m[1][0],mat.m[1][1],mat.m[1][2],0,
         mat.m[2][0],mat.m[2][1],mat.m[2][2],0,
         0,0,0,1);
   }
   inline void insertMatrix3IntoMatrix4(kf::Matrix4 &mat4, const kf::Matrix3 &mat3)
   {
      mat4(0,0) = mat3(0,0);
      mat4(0,1) = mat3(0,1);
      mat4(0,2) = mat3(0,2);
      mat4(1,0) = mat3(1,0);
      mat4(1,1) = mat3(1,1);
      mat4(1,2) = mat3(1,2);
      mat4(2,0) = mat3(2,0);
      mat4(2,1) = mat3(2,1);
      mat4(2,2) = mat3(2,2);
   }

   //inline kf::Quaternion convertMatrix3ToQuaternion(const kf::Matrix3 &mat)
   //{
   //   kf::Quaternion q;

   //     float fTrace = mat.m[0][0]+mat.m[1][1]+mat.m[2][2];
   //     float fRoot;

   //     if ( fTrace > 0.0f )
   //     {
   //         // |w| > 1/2, may as well choose w > 1/2
   //         fRoot = sqrt(fTrace + 1.0f);  // 2w
   //         q.w = 0.5f*fRoot;
   //         fRoot = 0.5f/fRoot;  // 1/(4w)
   //         q.x = (mat.m[2][1]-mat.m[1][2])*fRoot;
   //         q.y = (mat.m[0][2]-mat.m[2][0])*fRoot;
   //         q.z = (mat.m[1][0]-mat.m[0][1])*fRoot;
   //     }
   //     else
   //     {
   //         // |w| <= 1/2
   //         static size_t s_iNext[3] = { 1, 2, 0 };
   //         size_t i = 0;
   //         if ( mat.m[1][1] > mat.m[0][0] )
   //             i = 1;
   //         if ( mat.m[2][2] > mat.m[i][i] )
   //             i = 2;
   //         size_t j = s_iNext[i];
   //         size_t k = s_iNext[j];

   //         fRoot = sqrt(mat.m[i][i]-mat.m[j][j]-mat.m[k][k] + 1.0f);
   //         float* apkQuat[3] = { &q.x, &q.y, &q.z };
   //         *apkQuat[i] = 0.5f*fRoot;
   //         fRoot = 0.5f/fRoot;
   //         q.w = (mat.m[k][j]-mat.m[j][k])*fRoot;
   //         *apkQuat[j] = (mat.m[j][i]+mat.m[i][j])*fRoot;
   //         *apkQuat[k] = (mat.m[k][i]+mat.m[i][k])*fRoot;
   //     }
   //     return q;
   // }

   //inline kf::Matrix4 convertQuaternionToMatrix4(const kf::Quaternion &q)
   //{
   //   float xx = q.x * q.x;
   //   float xy = q.x * q.y;
   //   float xz = q.x * q.z;
   //   float xw = q.x * q.w;
   //   float yy = q.y * q.y;
   //   float yz = q.y * q.z;
   //   float yw = q.y * q.w;
   //   float zz = q.z * q.z;
   //   float zw = q.z * q.w;

   //   return kf::Matrix4(1 - 2 * ( yy + zz ),     2 * ( xy - zw ),     2 * ( xz + yw ), 0,
   //                          2 * ( xy + zw ), 1 - 2 * ( xx + zz ),     2 * ( yz - xw ), 0,
   //                          2 * ( xz - yw ),     2 * ( yz + xw ), 1 - 2 * ( xx + yy ), 0,
   //                                        0,                   0,                   0, 1);
   //}
   //inline kf::Matrix3 convertQuaternionToMatrix3(const kf::Quaternion &q)
   //{
   //   float xx = q.x * q.x;
   //   float xy = q.x * q.y;
   //   float xz = q.x * q.z;
   //   float xw = q.x * q.w;
   //   float yy = q.y * q.y;
   //   float yz = q.y * q.z;
   //   float yw = q.y * q.w;
   //   float zz = q.z * q.z;
   //   float zw = q.z * q.w;

   //   return kf::Matrix3(1 - 2 * ( yy + zz ),     2 * ( xy - zw ),     2 * ( xz + yw ),
   //                          2 * ( xy + zw ), 1 - 2 * ( xx + zz ),     2 * ( yz - xw ),
   //                          2 * ( xz - yw ),     2 * ( yz + xw ), 1 - 2 * ( xx + yy ));
   //}

   */
}
#endif
