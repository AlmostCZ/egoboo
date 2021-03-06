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

/// @file egolib/math.c
/// @brief The name's pretty self explanatory, doncha think?
/// @details This is the remainder of non-inlined math functions that deal with initialization

#include "egolib/_math.h"
#include "egolib/TrigonometricTable.hpp"
#include "egolib/Math/Random.hpp"


//--------------------------------------------------------------------------------------------

// conversion functions

const Facing Facing::ATK_FRONT = Facing(0x0000);
const Facing Facing::ATK_RIGHT = Facing(0x4000);
const Facing Facing::ATK_BEHIND = Facing(0x8000);
const Facing Facing::ATK_LEFT = Facing(0xC000);

/// pre defined directions
const Facing Facing::FACE_WEST = Facing(0x0000); ///< Character facings
const Facing Facing::FACE_NORTH = Facing(0x4000);
const Facing Facing::FACE_EAST = Facing(0x8000);
const Facing Facing::FACE_SOUTH = Facing(0xC000);


// limiting functions
    void getadd_flt( const float min, const float value, const float max, float* valuetoadd );

// random functions
    int generate_irand_pair( const IPair num );
    int generate_irand_range( const Ego::Math::Interval<float> num );

// matrix functions


//--------------------------------------------------------------------------------------------
// CONVERSION FUNCTIONS
//--------------------------------------------------------------------------------------------

Facing vec_to_facing( const float dx, const float dy )
{
    return Facing(FACING_T(RadianToFacing(Ego::Math::Radians(std::atan2(dy, dx) + Ego::Math::pi<float>()))));
}

//--------------------------------------------------------------------------------------------
void facing_to_vec( const Facing& facing, float * dx, float * dy )
{
    Facing turn = facing - Facing(0x8000);

    if ( NULL != dx )
    {
        *dx = std::cos(turn);
    }

    if ( NULL != dy )
    {
        *dy = std::sin(turn);
    }
}

//--------------------------------------------------------------------------------------------
// ROTATION FUNCTIONS
//--------------------------------------------------------------------------------------------
Facing rotate(const Facing& source, const Facing& target, const float weight) {
    int32_t delta = static_cast<int32_t>(target) - static_cast<int32_t>(source);

    //Figure out if it is faster to wrap around the other direction
    if(std::abs(delta) > (std::numeric_limits<uint16_t>::max() / 2)) {
        delta = -(delta/2);
    }

    int32_t weightedDelta = static_cast<float>(delta) / weight;

    return Facing(static_cast<int32_t>(source) + weightedDelta);
}

//--------------------------------------------------------------------------------------------
// LIMITING FUNCTIONS
//--------------------------------------------------------------------------------------------
void getadd_flt( const float min, const float value, const float max, float* valuetoadd )
{
    /// @author ZZ
    /// @details This function figures out what value to add should be in order
    ///    to not overflow the min and max bounds

    float newvalue;

    newvalue = value + ( *valuetoadd );
    if ( newvalue < min )
    {
        // Increase valuetoadd to fit
        *valuetoadd = min - value;
        if ( *valuetoadd > 0 )  *valuetoadd = 0;

        return;
    }
    if ( newvalue > max )
    {
        // Decrease valuetoadd to fit
        *valuetoadd = max - value;
        if ( *valuetoadd < 0 )  *valuetoadd = 0;
    }
}

//--------------------------------------------------------------------------------------------
// RANDOM FUNCTIONS
//--------------------------------------------------------------------------------------------
int generate_irand_pair( const IPair num )
{
    /// @author ZZ
    /// @details This function generates a random number

    int tmp;
    int irand = Random::next(std::numeric_limits<uint16_t>::max());

    tmp = num.base;
    if ( num.rand > 1 )
    {
        tmp += irand % num.rand;
    }

    return tmp;
}

//--------------------------------------------------------------------------------------------
int generate_irand_range( const Ego::Math::Interval<float> num )
{
    /// @author ZZ
    /// @details This function generates a random number

    IPair loc_pair = range_to_pair(num);

    return generate_irand_pair( loc_pair );
}
