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

/// @file  game/EncList.h
/// @brief Routines for enchant list management

#pragma once

#include "game/egoboo_typedef.h"

#include "game/egoboo_object.h"
#include "game/enchant.h"

//Forward declarations
struct enc_t;

//--------------------------------------------------------------------------------------------
// looping macros
//--------------------------------------------------------------------------------------------

// Macros automate looping through the EncList. This hides code which defers the creation and deletion of
// objects until the loop terminates, so tha the length of the list will not change during the loop.
#define ENC_BEGIN_LOOP_ACTIVE(IT, PENC)  {int IT##_internal; int enc_loop_start_depth = enc_loop_depth; enc_loop_depth++; for(IT##_internal=0;IT##_internal<EncList.used_count;IT##_internal++) { ENC_REF IT; enc_t * PENC = NULL; IT = (ENC_REF)EncList.used_ref[IT##_internal]; if(!_ACTIVE_ENC (IT)) continue; PENC =  EncList_get_ptr( IT );
#define ENC_END_LOOP() } enc_loop_depth--; EGOBOO_ASSERT(enc_loop_start_depth == enc_loop_depth); EncList_cleanup(); }

//--------------------------------------------------------------------------------------------
// external variables
//--------------------------------------------------------------------------------------------

DECLARE_LIST_EXTERN( enc_t, EncList, MAX_ENC );

extern int enc_loop_depth;

//--------------------------------------------------------------------------------------------
// Function prototypes
//--------------------------------------------------------------------------------------------

void    EncList_ctor();
void    EncList_dtor();

void    EncList_reinit();

ENC_REF EncList_allocate( const ENC_REF override );

bool  EncList_free_one( const ENC_REF ienc );
void    EncList_free_all();

void    EncList_update_used();

void   EncList_cleanup();

bool EncList_add_activation( const ENC_REF ienc );
bool EncList_add_termination( const ENC_REF ienc );
bool EncList_request_terminate( const ENC_REF ienc );

//--------------------------------------------------------------------------------------------
// testing functions
//--------------------------------------------------------------------------------------------
bool _VALID_ENC_RANGE( const ENC_REF IENC );
bool _DEFINED_ENC( const ENC_REF IENC );
bool _ALLOCATED_ENC( const ENC_REF IENC );
bool _ACTIVE_ENC( const ENC_REF IENC );
bool _WAITING_ENC( const ENC_REF IENC );
bool _TERMINATED_ENC( const ENC_REF IENC );

size_t  _GET_INDEX_PENC( const enc_t * PENC );
ENC_REF _GET_REF_PENC( const enc_t * PENC );
bool  _DEFINED_PENC( const enc_t * PENC );
bool  _VALID_ENC_PTR( const enc_t * PENC );
bool  _ALLOCATED_PENC( const enc_t * PENC );
bool  _ACTIVE_PENC( const enc_t * PENC );
bool  _TERMINATED_PENC( const enc_t * PENC );

bool _INGAME_ENC_BASE( const ENC_REF IENC );
bool _INGAME_PENC_BASE( const enc_t * PENC );

bool _INGAME_ENC( const ENC_REF IENC );
bool _INGAME_PENC( const enc_t * PENC );
