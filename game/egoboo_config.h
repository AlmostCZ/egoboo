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

/// @file egoboo_config.h
/// @brief System-dependent global parameters.
///   @todo  move more of the typical config stuff to this file.
///   @todo  add in linux and mac stuff.
///   @todo  some of this stuff is compiler dependent, rather than system dependent.

#include "egoboo_endian.h"
#include "egoboo_platform.h"

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
/// compliation flags

/// object pre-allocations
#define MAX_CHR            512             ///< Maximum number of characters
#define MAX_ENC            200             ///< Maximum number of enchantments
#define TOTAL_MAX_PRT     2048             ///< Maximum number of particles
#define TOTAL_MAX_DYNA      64             ///< Maximum number of dynamic lights

#define MAX_TEXTURE        (MAX_CHR * 4)     ///< Maximum number of textures
#define MAX_ICON           (MAX_TEXTURE + 4) ///< Maximum number of icons

#define MAX_SKIN             4               ///< The maxumum number of skins per model. This must remain hard coded at 4 for the moment.

/// profile pre-allocations
#define MAX_PROFILE        256          ///< Maximum number of object profiles
#define MAX_AI             MAX_PROFILE  ///< Maximum number of scripts

/// per-object pre-allocations
#define MAX_WAVE             30        ///< Maximum number of *.wav/*.ogg per object
#define MAX_PIP_PER_PROFILE  13        ///< Maximum number of part*.txt per object
#define MAX_PIP             (MAX_PROFILE * MAX_PIP_PER_PROFILE)

/// Some macro switches
#define USE_DEBUG (defined(_DEBUG) || !defined(NDEBUG))        ///< a test of whether a debug switch is explicitly or implicitly defined

#undef  OLD_CAMERA_MODE       ///< Use the old camera style
//#undef  USE_LUA_CONSOLE       ///< LUA support for the console
#undef  ENABLE_BODY_GRAB      ///< Enable the grabbing of bodies?
#undef  TEST_NAN_RESULT       ///< Test the result of certain math operations?

#undef  RENDER_HMAP           ///< render the mesh's heightmap?
#undef  DEBUG_MESH_NORMALS    ///< render the mesh normals
#define LOG_TO_CONSOLE        ///< dump all logginfo to file and to the console. Only useful if your compiler generates console for program output. Otherwise the results will end up in a file called stdout.txt

#undef  DEBUG_PROFILE       ///< Display the results for the performance profiling
#undef  DEBUG_PROFILE_MESH  ///< Display the results for the performance profiling of the mesh rendering sub-system
#undef  DEBUG_PROFILE_INIT  ///< Display the results for the performance profiling of the rendering initialization

#undef  DEBUG_PRT_LIST      ///< Track every single deletion from the PrtList to make sure the same element is not deleted twice. Prevents corruption of the PrtList.free_lst
#undef  DEBUG_ENC_LIST      ///< Track every single deletion from the EncList to make sure the same element is not deleted twice. Prevents corruption of the EncList.free_lst
#undef  DEBUG_CHR_LIST      ///< Track every single deletion from the ChrList to make sure the same element is not deleted twice. Prevents corruption of the ChrList.free_lst

#undef  DEBUG_STDIO         ///< Route stdio calls through wrapper functions so that we can track io calls. This needs to be removed.

#define CLIP_LIGHT_FANS     ///< is the light_fans() function going to be throtled?
#undef  CLIP_ALL_LIGHT_FANS  ///< a switch for selecting how the fans will be updated

#define EGOBOO_CONFIG_H