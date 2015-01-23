//********************************************************************************************
//*
//*    This file is part of Egoboo.
//*
//*    Egoboo is free software: you can redistribute it and/or modify it
//*    under the terms of the GNU General Public License as published by
//*    the Free Software Foundation, either version 3 of the License, or
//*    (at your option) any later version.
//*
//*    Egoboo is distributed in the hope that it will be useful, but
//*    WITHOUT ANY WARRANTY; without even the implied warranty of
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*    General Public License for more details.
//*
//*    You should have received a copy of the GNU General Public License
//*    along with Egoboo.  If not, see <http://www.gnu.org/licenses/>.
//*
//********************************************************************************************
/// @file egolib/matrix.c
/// @details matrices
#include "egolib/matrix.h"

const fmat_4x4_t fmat_4x4_t::identity
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
const fmat_4x4_t fmat_4x4_t::zero
	(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);

float * mat_Copy(fmat_4x4_base_t DST, const fmat_4x4_base_t src)
{
	float * retval = NULL;

	if (NULL == DST)
	{
		retval = NULL;
	}
	else if (NULL == src)
	{
		retval = mat_Zero(DST);
	}
	else
	{
		retval = (float *)memmove(DST, src, sizeof(fmat_4x4_base_t));
	}

	return retval;
}

//--------------------------------------------------------------------------------------------
float * mat_Identity(fmat_4x4_base_t DST)
{
	if (NULL == DST) return NULL;

	DST[MAT_IDX(0, 0)] = 1; DST[MAT_IDX(1, 0)] = 0; DST[MAT_IDX(2, 0)] = 0; DST[MAT_IDX(3, 0)] = 0;
	DST[MAT_IDX(0, 1)] = 0; DST[MAT_IDX(1, 1)] = 1; DST[MAT_IDX(2, 1)] = 0; DST[MAT_IDX(3, 1)] = 0;
	DST[MAT_IDX(0, 2)] = 0; DST[MAT_IDX(1, 2)] = 0; DST[MAT_IDX(2, 2)] = 1; DST[MAT_IDX(3, 2)] = 0;
	DST[MAT_IDX(0, 3)] = 0; DST[MAT_IDX(1, 3)] = 0; DST[MAT_IDX(2, 3)] = 0; DST[MAT_IDX(3, 3)] = 1;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_Zero(fmat_4x4_base_t DST)
{
	// initializes matrix to zero

	if (NULL == DST) return NULL;

	DST[MAT_IDX(0, 0)] = 0; DST[MAT_IDX(1, 0)] = 0; DST[MAT_IDX(2, 0)] = 0; DST[MAT_IDX(3, 0)] = 0;
	DST[MAT_IDX(0, 1)] = 0; DST[MAT_IDX(1, 1)] = 0; DST[MAT_IDX(2, 1)] = 0; DST[MAT_IDX(3, 1)] = 0;
	DST[MAT_IDX(0, 2)] = 0; DST[MAT_IDX(1, 2)] = 0; DST[MAT_IDX(2, 2)] = 0; DST[MAT_IDX(3, 2)] = 0;
	DST[MAT_IDX(0, 3)] = 0; DST[MAT_IDX(1, 3)] = 0; DST[MAT_IDX(2, 3)] = 0; DST[MAT_IDX(3, 3)] = 0;

	return DST;
}

//--------------------------------------------------------------------------------------------
float *mat_Multiply(fmat_4x4_base_t dst, const fmat_4x4_base_t src1, const fmat_4x4_base_t src2)
{
	if (NULL == mat_Zero(dst)) return NULL;

#if fmat_4x4_layout == fmat_4x4_layout_RowMajor
	/* \f$ C_{i,j} = \sum_{i=0}^4 A_{i,k} * B_{k,j}\f$ */
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k)
			{
				dst[MAT_IDX(i, j)] += src1[MAT_IDX(i, k)] * src2[MAT_IDX(k, j)];
			}
		}
	}
#else
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k)
			{
				dst[MAT_IDX(i, j)] += src1[MAT_IDX(k, j)] * src2[MAT_IDX(i, k)];
			}
		}
	}
#endif
	return dst;
}

//--------------------------------------------------------------------------------------------
float * mat_Translate(fmat_4x4_base_t DST, const float dx, const float dy, const float dz)
{
	if (NULL == mat_Identity(DST)) return NULL;

	DST[MAT_IDX(3, 0)] = dx;
	DST[MAT_IDX(3, 1)] = dy;
	DST[MAT_IDX(3, 2)] = dz;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_RotateX(fmat_4x4_base_t DST, const float rads)
{
	float cosine = COS(rads);
	float sine = SIN(rads);

	if (NULL == mat_Identity(DST)) return NULL;

	DST[MAT_IDX(1, 1)] = cosine;
	DST[MAT_IDX(2, 2)] = cosine;
	DST[MAT_IDX(1, 2)] = -sine;
	DST[MAT_IDX(2, 1)] = sine;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_RotateY(fmat_4x4_base_t DST, const float rads)
{
	float cosine = COS(rads);
	float sine = SIN(rads);

	if (NULL == mat_Identity(DST)) return NULL;

	DST[MAT_IDX(0, 0)] = cosine;
	DST[MAT_IDX(2, 2)] = cosine;
	DST[MAT_IDX(0, 2)] = sine;
	DST[MAT_IDX(2, 0)] = -sine;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_RotateZ(fmat_4x4_base_t DST, const float rads)
{
	float cosine = COS(rads);
	float sine = SIN(rads);

	if (NULL == mat_Identity(DST)) return NULL;

	DST[MAT_IDX(0, 0)] = cosine;
	DST[MAT_IDX(1, 1)] = cosine;
	DST[MAT_IDX(0, 1)] = -sine;
	DST[MAT_IDX(1, 0)] = sine;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_ScaleXYZ(fmat_4x4_base_t DST, const float sizex, const float sizey, const float sizez)
{
	if (NULL == mat_Identity(DST)) return NULL;

	DST[MAT_IDX(0, 0)] = sizex;
	DST[MAT_IDX(1, 1)] = sizey;
	DST[MAT_IDX(2, 2)] = sizez;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_ScaleXYZ_RotateXYZ_TranslateXYZ_SpaceFixed(fmat_4x4_base_t DST, const float scale_x, const float scale_y, const float scale_z, const TURN_T turn_z, const TURN_T turn_x, const TURN_T turn_y, const float translate_x, const float translate_y, const float translate_z)
{
	float cx = turntocos[turn_x & TRIG_TABLE_MASK];
	float sx = turntosin[turn_x & TRIG_TABLE_MASK];
	float cy = turntocos[turn_y & TRIG_TABLE_MASK];
	float sy = turntosin[turn_y & TRIG_TABLE_MASK];
	float cz = turntocos[turn_z & TRIG_TABLE_MASK];
	float sz = turntosin[turn_z & TRIG_TABLE_MASK];

	if (NULL == DST) return NULL;

	DST[MAT_IDX(0, 0)] = scale_x * (cz * cy);
	DST[MAT_IDX(0, 1)] = scale_x * (cz * sy * sx + sz * cx);
	DST[MAT_IDX(0, 2)] = scale_x * (sz * sx - cz * sy * cx);
	DST[MAT_IDX(0, 3)] = 0.0f;

	DST[MAT_IDX(1, 0)] = scale_y * (-sz * cy);
	DST[MAT_IDX(1, 1)] = scale_y * (-sz * sy * sx + cz * cx);
	DST[MAT_IDX(1, 2)] = scale_y * (sz * sy * cx + cz * sx);
	DST[MAT_IDX(1, 3)] = 0.0f;

	DST[MAT_IDX(2, 0)] = scale_z * (sy);
	DST[MAT_IDX(2, 1)] = scale_z * (-cy * sx);
	DST[MAT_IDX(2, 2)] = scale_z * (cy * cx);
	DST[MAT_IDX(2, 3)] = 0.0f;

	DST[MAT_IDX(3, 0)] = translate_x;
	DST[MAT_IDX(3, 1)] = translate_y;
	DST[MAT_IDX(3, 2)] = translate_z;
	DST[MAT_IDX(3, 3)] = 1.0f;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_ScaleXYZ_RotateXYZ_TranslateXYZ_BodyFixed(fmat_4x4_base_t DST, const float scale_x, const float scale_y, const float scale_z, const TURN_T turn_z, const TURN_T turn_x, const TURN_T turn_y, const float translate_x, const float translate_y, const float translate_z)
{
	/// @author BB
	/// @details Transpose the SpaceFixed representation and invert the angles to get the BodyFixed representation

	float cx = turntocos[turn_x & TRIG_TABLE_MASK];
	float sx = turntosin[turn_x & TRIG_TABLE_MASK];
	float cy = turntocos[turn_y & TRIG_TABLE_MASK];
	float sy = turntosin[turn_y & TRIG_TABLE_MASK];
	float cz = turntocos[turn_z & TRIG_TABLE_MASK];
	float sz = turntosin[turn_z & TRIG_TABLE_MASK];

	if (NULL == DST) return NULL;

	DST[MAT_IDX(0, 0)] = scale_x * (cz * cy - sz * sy * sx);
	DST[MAT_IDX(0, 1)] = scale_x * (sz * cy + cz * sy * sx);
	DST[MAT_IDX(0, 2)] = scale_x * (-cx * sy);
	DST[MAT_IDX(0, 3)] = 0.0f;

	DST[MAT_IDX(1, 0)] = scale_y * (-sz * cx);
	DST[MAT_IDX(1, 1)] = scale_y * (cz * cx);
	DST[MAT_IDX(1, 2)] = scale_y * (sx);
	DST[MAT_IDX(1, 3)] = 0.0f;

	DST[MAT_IDX(2, 0)] = scale_z * (cz * sy + sz * sx * cy);
	DST[MAT_IDX(2, 1)] = scale_z * (sz * sy - cz * sx * cy);
	DST[MAT_IDX(2, 2)] = scale_z * (cy * cx);
	DST[MAT_IDX(2, 3)] = 0.0f;

	DST[MAT_IDX(3, 0)] = translate_x;
	DST[MAT_IDX(3, 1)] = translate_y;
	DST[MAT_IDX(3, 2)] = translate_z;
	DST[MAT_IDX(3, 3)] = 1.0f;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_FourPoints(fmat_4x4_base_t DST, const fvec4_base_t ori, const fvec4_base_t wid, const fvec4_base_t frw, const fvec4_base_t up, const float scale)
{
	fvec3_t vWid, vFor, vUp;

	if (NULL == DST) return NULL;

	vWid.x = wid[kX] - ori[kX];
	vWid.y = wid[kY] - ori[kY];
	vWid.z = wid[kZ] - ori[kZ];

	vUp.x = up[kX] - ori[kX];
	vUp.y = up[kY] - ori[kY];
	vUp.z = up[kZ] - ori[kZ];

	vFor.x = frw[kX] - ori[kX];
	vFor.y = frw[kY] - ori[kY];
	vFor.z = frw[kZ] - ori[kZ];

	vWid.normalize();
	vUp.normalize();
	vFor.normalize();

	DST[MAT_IDX(0, 0)] = -scale * vWid.x;  // HUK
	DST[MAT_IDX(0, 1)] = -scale * vWid.y;  // HUK
	DST[MAT_IDX(0, 2)] = -scale * vWid.z;  // HUK
	DST[MAT_IDX(0, 3)] = 0.0f;

	DST[MAT_IDX(1, 0)] = scale * vFor.x;
	DST[MAT_IDX(1, 1)] = scale * vFor.y;
	DST[MAT_IDX(1, 2)] = scale * vFor.z;
	DST[MAT_IDX(1, 3)] = 0.0f;

	DST[MAT_IDX(2, 0)] = scale * vUp.x;
	DST[MAT_IDX(2, 1)] = scale * vUp.y;
	DST[MAT_IDX(2, 2)] = scale * vUp.z;
	DST[MAT_IDX(2, 3)] = 0.0f;

	DST[MAT_IDX(3, 0)] = ori[kX];
	DST[MAT_IDX(3, 1)] = ori[kY];
	DST[MAT_IDX(3, 2)] = ori[kZ];
	DST[MAT_IDX(3, 3)] = 1.0f;

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_View(fmat_4x4_base_t DST,
	const fvec3_t&   from,     // camera location
	const fvec3_t&   at,        // camera look-at target
	const fvec3_t&   world_up,  // world�s up, usually 0, 0, 1
	const float roll)         // clockwise roll around
	//   viewing direction,
	//   in radians
{
	/// @author MN
	/// @details This probably should be replaced by a call to gluLookAt(),
	///          don't see why we need to make our own...

	fvec3_t up, right, view_dir, temp;

	if (NULL == mat_Identity(DST)) return NULL;

	view_dir = at - from;
	view_dir.normalize();
	right = world_up.cross(view_dir);
	up = view_dir.cross(right);
	right.normalize();
	up.normalize();

	DST[MAT_IDX(0, 0)] = right.x;
	DST[MAT_IDX(1, 0)] = right.y;
	DST[MAT_IDX(2, 0)] = right.z;

	DST[MAT_IDX(0, 1)] = up.x;
	DST[MAT_IDX(1, 1)] = up.y;
	DST[MAT_IDX(2, 1)] = up.z;

	DST[MAT_IDX(0, 2)] = view_dir.x;
	DST[MAT_IDX(1, 2)] = view_dir.y;
	DST[MAT_IDX(2, 2)] = view_dir.z;

	DST[MAT_IDX(3, 0)] = -right.dot(from);
	DST[MAT_IDX(3, 1)] = -up.dot(from);
	DST[MAT_IDX(3, 2)] = -view_dir.dot(from);

	if (roll != 0.0f)
	{
		// mat_Multiply function shown above
		fmat_4x4_t tmp1, tmp2;

		mat_Multiply(DST, mat_RotateZ(tmp1.v, -roll), mat_Copy(tmp2.v, DST));
	}

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_Projection(
	fmat_4x4_base_t DST,
	const float near_plane,    // distance to near clipping plane
	const float far_plane,     // distance to far clipping plane
	const float fov,           // vertical field of view angle, in radians
	const float ar)           // aspect ratio
{
	/// @author MN
	/// @details Again, there is a gl function for this, glFrustum or gluPerspective...
	///          does this account for viewport ratio?

	float inv_h = 1 / TAN(fov * 0.5f);
	float inv_w = inv_h / ar;
	float Q = far_plane / (far_plane - near_plane);

	if (NULL == mat_Zero(DST)) return NULL;

	DST[MAT_IDX(0, 0)] = inv_h;         // 0,0
	DST[MAT_IDX(1, 1)] = inv_w;         // 1,1
	DST[MAT_IDX(2, 2)] = Q;         // 2,2
	DST[MAT_IDX(3, 2)] = -1.0f; // 3,2
	DST[MAT_IDX(2, 3)] = Q * near_plane;         // 2,3

	return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_Projection_orig(
	fmat_4x4_base_t DST,
	const float near_plane,    // distance to near clipping plane
	const float far_plane,      // distance to far clipping plane
	const float fov)           // field of view angle, in radians
{
	/// @author MN
	/// @details Again, there is a gl function for this, glFrustum or gluPerspective...
	///          does this account for viewport ratio?

	float c = COS(fov * 0.5f);
	float s = SIN(fov * 0.5f);
	float Q = far_plane / (far_plane - near_plane);

	if (NULL == mat_Zero(DST)) return NULL;

	DST[MAT_IDX(0, 0)] = c / s;       // 0,0
	DST[MAT_IDX(1, 1)] = c / s;       // 1,1
	DST[MAT_IDX(2, 2)] = Q;         // 2,2
	DST[MAT_IDX(3, 2)] = -Q * near_plane; // 3,2
	DST[MAT_IDX(2, 3)] = 1.0f;         // 2,3

	return DST;
}

//--------------------------------------------------------------------------------------------
bool mat_getTranslate(const fmat_4x4_t& mat, fvec3_t& translate)
{
	translate[kX] = mat.v[MAT_IDX(3, 0)];
	translate[kY] = mat.v[MAT_IDX(3, 1)];
	translate[kZ] = mat.v[MAT_IDX(3, 2)];

	return true;
}

//--------------------------------------------------------------------------------------------
bool mat_getChrUp(const fmat_4x4_t& mat, fvec3_t& up)
{
	// for a character
	up[kX] = mat.v[MAT_IDX(2, 0)];
	up[kY] = mat.v[MAT_IDX(2, 1)];
	up[kZ] = mat.v[MAT_IDX(2, 2)];

	return true;
}

//--------------------------------------------------------------------------------------------
bool mat_getChrForward(const fmat_4x4_t& mat, fvec3_t& forward)
{
	// for a character
	forward[kX] = -mat.v[MAT_IDX(0, 0)];
	forward[kY] = -mat.v[MAT_IDX(0, 1)];
	forward[kZ] = -mat.v[MAT_IDX(0, 2)];

	return true;
}

//--------------------------------------------------------------------------------------------
bool mat_getChrRight(const fmat_4x4_t& mat, fvec3_t& right)
{
	// for a character's matrix
	right[kX] = mat.v[MAT_IDX(1, 0)];
	right[kY] = mat.v[MAT_IDX(1, 1)];
	right[kZ] = mat.v[MAT_IDX(1, 2)];

	return true;
}

//--------------------------------------------------------------------------------------------
bool mat_getCamUp(const fmat_4x4_t& mat, fvec3_t& up)
{
	// for the camera
	up[kX] = mat.v[MAT_IDX(0, 1)];
	up[kY] = mat.v[MAT_IDX(1, 1)];
	up[kZ] = mat.v[MAT_IDX(2, 1)];

	return true;
}

//--------------------------------------------------------------------------------------------
bool mat_getCamRight(const fmat_4x4_t& mat, fvec3_t& right)
{
	// for the camera
	right[kX] = -mat.v[MAT_IDX(0, 0)];
	right[kY] = -mat.v[MAT_IDX(1, 0)];
	right[kZ] = -mat.v[MAT_IDX(2, 0)];

	return true;
}

//--------------------------------------------------------------------------------------------
bool mat_getCamForward(const fmat_4x4_t& mat, fvec3_t& forward)
{
	// for the camera
	forward[kX] = -mat.v[MAT_IDX(0, 2)];
	forward[kY] = -mat.v[MAT_IDX(1, 2)];
	forward[kZ] = -mat.v[MAT_IDX(2, 2)];

	return true;
}

//--------------------------------------------------------------------------------------------
fvec3_t mat_getTranslate_v(const fmat_4x4_base_t mat)
{
	fvec3_t pos;

	pos.x = mat[MAT_IDX(3, 0)];
	pos.y = mat[MAT_IDX(3, 1)];
	pos.z = mat[MAT_IDX(3, 2)];

	return pos;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void  mat_TransformVertices(const fmat_4x4_base_t Matrix, const fvec4_t pSourceV[], fvec4_t pDestV[], const Uint32 NumVertor)
{
	/// @author GS
	/// @details This is just a MulVectorMatrix for now. The W division and screen size multiplication
	///                must be done afterward.
	/// @author BB
	/// @details the matrix transformation for OpenGL vertices. Some minor optimizations.
	///      The value pSourceV->w is assumed to be constant for all of the elements of pSourceV

	Uint32    cnt;
	fvec4_t * SourceIt = (fvec4_t *)pSourceV;

	if (1.0f == SourceIt->w)
	{
		for (cnt = 0; cnt < NumVertor; cnt++)
		{
			pDestV->x = SourceIt->x * Matrix[0] + SourceIt->y * Matrix[4] + SourceIt->z * Matrix[8] + Matrix[12];
			pDestV->y = SourceIt->x * Matrix[1] + SourceIt->y * Matrix[5] + SourceIt->z * Matrix[9] + Matrix[13];
			pDestV->z = SourceIt->x * Matrix[2] + SourceIt->y * Matrix[6] + SourceIt->z * Matrix[10] + Matrix[14];
			pDestV->w = SourceIt->x * Matrix[3] + SourceIt->y * Matrix[7] + SourceIt->z * Matrix[11] + Matrix[15];

			pDestV++;
			SourceIt++;
		}
	}
	else if (0.0f == SourceIt->w)
	{
		for (cnt = 0; cnt < NumVertor; cnt++)
		{
			pDestV->x = SourceIt->x * Matrix[0] + SourceIt->y * Matrix[4] + SourceIt->z * Matrix[8];
			pDestV->y = SourceIt->x * Matrix[1] + SourceIt->y * Matrix[5] + SourceIt->z * Matrix[9];
			pDestV->z = SourceIt->x * Matrix[2] + SourceIt->y * Matrix[6] + SourceIt->z * Matrix[10];
			pDestV->w = SourceIt->x * Matrix[3] + SourceIt->y * Matrix[7] + SourceIt->z * Matrix[11];

			pDestV++;
			SourceIt++;
		}
	}
	else
	{
		for (cnt = 0; cnt < NumVertor; cnt++)
		{
			pDestV->x = SourceIt->x * Matrix[0] + SourceIt->y * Matrix[4] + SourceIt->z * Matrix[8] + SourceIt->w * Matrix[12];
			pDestV->y = SourceIt->x * Matrix[1] + SourceIt->y * Matrix[5] + SourceIt->z * Matrix[9] + SourceIt->w * Matrix[13];
			pDestV->z = SourceIt->x * Matrix[2] + SourceIt->y * Matrix[6] + SourceIt->z * Matrix[10] + SourceIt->w * Matrix[14];
			pDestV->w = SourceIt->x * Matrix[3] + SourceIt->y * Matrix[7] + SourceIt->z * Matrix[11] + SourceIt->w * Matrix[15];

			pDestV++;
			SourceIt++;
		}
	}
}

#if 0
namespace Ego {
	namespace Math {

		template <typename Type>
		Type pi();

		template <typename Type>
		Type deg_to_rad(const Type& x);

		template <>
		float pi()
		{
			return 0.0f;
		}

		template <>
		double pi()
		{
			return 0.0;
		}

		template<>
		float deg_to_rad(const float& x)
		{
			return 0.0f;
		}

		template<>
		double deg_to_rad(const double& x)
		{
			return 0.0;
		}

	};
};
#endif



void mat_gluPerspective(fmat_4x4_t &dst, const fmat_4x4_t& src, const float fovy, const float aspect, const float zNear, const float zFar)
{
    fmat_4x4_t M;
	M.makePerspective(fovy, aspect, zNear, zFar);
    mat_Multiply(dst.v, src.v, M.v);
}

void mat_gluLookAt(fmat_4x4_base_t &DST, const fmat_4x4_base_t &src, const float eyeX, const float eyeY, const float eyeZ, const float centerX, const float centerY, const float centerZ, const float upX, const float upY, const float upZ)
{
    fmat_4x4_base_t M, eyeTranslate, tmp;
    fvec3_t f(centerX - eyeX, centerY - eyeY, centerZ - eyeZ);
    fvec3_t up(upX, upY, upZ);
    fvec3_t s;
    fvec3_t u;
    
    f.normalize();
    up.normalize();
    
    s = f.cross(up);
    s.normalize();
    
    u = s.cross(f);
    
    mat_Zero(M);
    mat_Translate(eyeTranslate, -eyeX, -eyeY, -eyeZ);
    
    M[MAT_IDX(0, 0)] = s.x;
    M[MAT_IDX(1, 0)] = s.y;
    M[MAT_IDX(2, 0)] = s.z;
    
    M[MAT_IDX(0, 1)] = u.x;
    M[MAT_IDX(1, 1)] = u.y;
    M[MAT_IDX(2, 1)] = u.z;
    
    M[MAT_IDX(0, 2)] = -f.x;
    M[MAT_IDX(1, 2)] = -f.y;
    M[MAT_IDX(2, 2)] = -f.z;
    
    M[MAT_IDX(3, 3)] = 1;
    
    mat_Multiply(tmp, src, M);
    mat_Multiply(DST, tmp, eyeTranslate);
}

void mat_glRotate(fmat_4x4_base_t &DST, const fmat_4x4_base_t &src, const float angle, const float x, const float y, const float z)
{
    fmat_4x4_base_t M;
    fvec3_t vec(x, y, z);
    float s = std::sin(DEG_TO_RAD(angle));
    float c = std::cos(DEG_TO_RAD(angle));
    
    mat_Zero(M);
    vec.normalize();
    
    M[MAT_IDX(0, 0)] = vec.x * vec.x * (1 - c) + c;
    M[MAT_IDX(1, 0)] = vec.x * vec.y * (1 - c) - vec.z * s;
    M[MAT_IDX(2, 0)] = vec.x * vec.z * (1 - c) + vec.y * s;
    
    M[MAT_IDX(0, 1)] = vec.y * vec.x * (1 - c) + vec.z * s;
    M[MAT_IDX(1, 1)] = vec.y * vec.y * (1 - c) + c;
    M[MAT_IDX(2, 1)] = vec.y * vec.z * (1 - c) - vec.x * s;
    
    M[MAT_IDX(0, 2)] = vec.z * vec.x * (1 - c) - vec.y * s;
    M[MAT_IDX(1, 2)] = vec.z * vec.y * (1 - c) + vec.x * s;
    M[MAT_IDX(2, 2)] = vec.z * vec.z * (1 - c) + c;
    
    M[MAT_IDX(3, 3)] = 1;
    
    mat_Multiply(DST, src, M);
}

void dump_matrix(const fmat_4x4_base_t a)
{
	if (NULL == a) return;

	for (size_t j = 0; j < 4; j++)
	{
		printf("  ");

		for (size_t i = 0; i < 4; i++)
		{
			printf("%f ", a[MAT_IDX(i, j)]);
		}
		printf("\n");
	}
}
