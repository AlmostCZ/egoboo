#pragma once

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

/// @file egoboo_math.h
/// @details The name's pretty self explanatory, doncha think?

#include "egoboo_typedef.h"

#include <math.h>
#include <float.h>

#if defined(__cplusplus)
extern "C"
{
#endif

    struct s_fmat_4x4;
    typedef struct s_fmat_4x4  fmat_4x4_t;

    union u_fvec2;
    typedef union u_fvec2 fvec2_t;

    union u_fvec3;
    typedef union u_fvec3 fvec3_t;

    union u_fvec4;
    typedef union u_fvec4 fvec4_t;


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// basic constants

#if !defined(PI)
#   define PI                  3.1415926535897932384626433832795f
#endif

#if !defined(INV_PI)
#   define INV_PI              0.31830988618379067153776752674503f
#endif

#if !defined(TWO_PI)
#   define TWO_PI              6.283185307179586476925286766559f
#endif

#if !defined(INV_TWO_PI)
#   define INV_TWO_PI          0.15915494309189533576888376337251f
#endif

#if !defined(PI_OVER_TWO)
#   define PI_OVER_TWO         1.5707963267948966192313216916398f
#endif

#if !defined(PI_OVER_FOUR)
#   define PI_OVER_FOUR         0.78539816339744830961566084581988f
#endif

#if !defined(SQRT_TWO)
#   define SQRT_TWO            1.4142135623730950488016887242097f
#endif

#if !defined(INV_SQRT_TWO)
#   define INV_SQRT_TWO        0.70710678118654752440084436210485f
#endif

#if !defined(RAD_TO_FACING)
#   define RAD_TO_FACING(XX)     ( (XX) * 10430.378350470452724949566316381f )
#endif

#if !defined(FACING_TO_RAD)
#   define FACING_TO_RAD(XX)     ( (XX) * 0.000095873799242852576857380474343257f )
#endif

#if !defined(DEG_TO_RAD)
#   define DEG_TO_RAD(XX)         ( (XX) * 0.017453292519943295769236907684886f )
#endif

#if !defined(RAD_TO_DEG)
#   define RAD_TO_DEG(XX)         ( (XX) * 57.295779513082320876798154814105f )
#endif

#if !defined(ONE_TO_TURN)
#   define ONE_TO_TURN(XX)         CLIP_TO_16BITS(( int )( XX * ( float )0x00010000 ) )
#endif

#if !defined(TURN_TO_ONE)
#   define TURN_TO_ONE(XX)         ( (float) CLIP_TO_16BITS(XX) / ( float )0x00010000 )
#endif

#if !defined(RAD_TO_ONE)
#   define RAD_TO_ONE(XX)         ( (XX) * INV_TWO_PI )
#endif

#if !defined(ONE_TO_RAD)
#   define ONE_TO_RAD(XX)         ( (XX) * TWO_PI )
#endif

//--------------------------------------------------------------------------------------------
// the lookup tables for sine and cosine

#define TRIG_TABLE_BITS   14
#define TRIG_TABLE_SIZE   (1<<TRIG_TABLE_BITS)
#define TRIG_TABLE_MASK   (TRIG_TABLE_SIZE-1)
#define TRIG_TABLE_OFFSET (TRIG_TABLE_SIZE>>2)

/// @note - Aaron uses two terms without much attention to their meaning
///         I think that we should use "face" or "facing" to mean the fill 16-bit value
///         and use "turn" to be the TRIG_TABLE_BITS-bit value

    extern float turntosin[TRIG_TABLE_SIZE];           ///< Convert TURN_T == FACING_T>>2...  to sine
    extern float turntocos[TRIG_TABLE_SIZE];           ///< Convert TURN_T == FACING_T>>2...  to cosine

/// pre defined directions
#define FACE_WEST    0x0000
#define FACE_NORTH   0x4000                                 ///< Character facings
#define FACE_EAST    0x8000
#define FACE_SOUTH   0xC000

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// Just define ABS, MIN, and MAX using macros for the moment. This is likely to be the
// fastest and most cross-platform solution

#if !defined(ABS)
#    define ABS(X)  (((X) > 0) ? (X) : -(X))
#endif

#if !defined(SGN)
#    define SGN(X)  ((0 == (X)) ? 0 : (((X) > 0) ? 1 : -1) )
#endif

#if !defined(MIN)
#    define MIN(x, y)  (((x) > (y)) ? (y) : (x))
#endif

#if !defined(MAX)
#    define MAX(x, y)  (((x) > (y)) ? (x) : (y))
#endif

#if !defined(SQR)
#    define SQR(A) ((A)*(A))
#endif

#if !defined(SQRT)
#    define SQRT(A) ((float)sqrt((float)(A)))
#endif

#if !defined(LOG)
#    define LOG(A) ((float)log((float)(A)))
#endif

#if !defined(SIN)
#    define SIN(A) ((float)sin((float)(A)))
#endif

#if !defined(COS)
#    define COS(A) ((float)cos((float)(A)))
#endif

#if !defined(ACOS)
#    define ACOS(A) ((float)acos((float)(A)))
#endif

#if !defined(TAN)
#    define TAN(A) ((float)tan((float)(A)))
#endif

#if !defined(ATAN)
#    define ATAN(A) ((float)atan((float)(A)))
#endif

#if !defined(POW)
#    define POW(A, B) ((float)pow((float)(A), (float)(B)))
#endif

#if !defined(ATAN2)
#    define ATAN2(A, B) ((float)atan2((float)(A), (float)(B)))
#endif

#if !defined(CLIP)
#    define CLIP(VAL,VMIN,VMAX) MIN(MAX(VAL,VMIN),VMAX)
#endif

#if !defined(SWAP)
#    define SWAP(TYPE, A, B) { TYPE temp; memmove( &temp, &(A), sizeof(TYPE) ); memmove( &(A), &(B), sizeof(TYPE) ); memmove( &(B), &temp, sizeof(TYPE) ); }
#endif

#if !defined(CEIL)
#    define CEIL(VAL) ( (float)ceil((float)VAL) )
#endif

#if !defined(FLOOR)
#    define FLOOR(VAL) ( (float)floor((float)VAL) )
#endif

#define MAT_IDX(I,J) (4*(I)+(J))
#define CNV(I,J)     v[MAT_IDX(I,J)]
#define CopyMatrix( pMatrixDest, pMatrixSource ) memmove( pMatrixDest, pMatrixSource, sizeof( *pMatrixDest ) )

//--------------------------------------------------------------------------------------------
// FAST CONVERSIONS

#if !defined(INV_FF)
#   define INV_FF              0.003921568627450980392156862745098f
#endif

#if !defined(INV_0100)
#   define INV_0100            0.00390625f
#endif

#if !defined(INV_FFFF)
#   define INV_FFFF            0.000015259021896696421759365224689097f
#endif

#define FF_TO_FLOAT( V1 )  ( (float)(V1) * INV_FF )

#define FFFF_TO_FLOAT( V1 )  ( (float)(V1) * INV_FFFF )
#define FLOAT_TO_FFFF( V1 )  ( ((V1) * 0xFFFF) )

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// vector definitions

    enum { kX = 0, kY, kZ, kW };             ///< Enumerated indices for the elements of the base vector types

    typedef float fmat_4x4_base_t[16];       ///< the basic 4x4 floating point matrix type
    typedef float fvec2_base_t[2];           ///< the basic floating point 2-vector type
    typedef float fvec3_base_t[3];           ///< the basic floating point 3-vector type
    typedef float fvec4_base_t[4];           ///< the basic floating point 4-vector type

    typedef double dmat_4x4_base_t[16];      ///< the basic 4x4 double precision matrix type
    typedef double dvec2_base_t[2];          ///< the basic double precision 2-vector type
    typedef double dvec3_base_t[3];          ///< the basic double precision 3-vector type
    typedef double dvec4_base_t[4];          ///< the basic double precision 4-vector type

/// A wrapper for fmat_4x4_base_t
/// Necessary in c so that the function return can be assigned to another matrix more simply.
    struct s_fmat_4x4  { fmat_4x4_base_t  v; };

/// A 2-vector type that allows more than one form of access
    union  u_fvec2 { fvec2_base_t v; struct { float x, y; }; struct { float s, t; }; };

/// A 3-vector type that allows more than one form of access
    union  u_fvec3 { fvec3_base_t v; struct { float x, y, z; }; struct { float r, g, b; }; };

/// A 4-vector type that allows more than one form of access
    union  u_fvec4     { fvec4_base_t v; struct { float x, y, z, w; }; struct { float r, g, b, a; }; };

// macros for initializing vectors to zero
#define ZERO_VECT2   { {0.0f,0.0f} }
#define ZERO_VECT3   { {0.0f,0.0f,0.0f} }
#define ZERO_VECT4   { {0.0f,0.0f,0.0f,0.0f} }
#define ZERO_MAT_4X4 { {0.0f,0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f} }

// Macros for initializing vectors to specific values. Most C compilers will allow you to initialize
// to non-constant values, but they do complain.
#define VECT2(XX,YY) { {XX,YY} }
#define VECT3(XX,YY,ZZ) { {XX,YY,ZZ} }
#define VECT4(XX,YY,ZZ,WW) { {XX,YY,ZZ,WW} }

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// My lil' random number table

// swig chokes on the definition below
#if defined(SWIG)
#    define RANDIE_BITS    12
#    define RANDIE_COUNT 4096
#else
#    define RANDIE_BITS   12
#    define RANDIE_COUNT (1 << RANDIE_BITS)
#endif

#define RANDIE_MASK  ((Uint32)(RANDIE_COUNT - 1))
#define RANDIE       randie[randindex & RANDIE_MASK ];  randindex++; randindex &= RANDIE_MASK

    extern Uint32  randindex;
    extern Uint16  randie[RANDIE_COUNT];   ///< My lil' random number table

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// prototypes of other math functions

    void make_turntosin( void );
    void make_randie( void );

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#define _egoboo_math_h
