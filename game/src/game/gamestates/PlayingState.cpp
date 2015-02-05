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

/// @file game/gamestates/PlayingState.cpp
/// @details Main state where the players are currently playing a module
/// @author Johan Jansen

#include "game/gamestates/PlayingState.hpp"
#include "game/gamestates/InGameMenuState.hpp"
#include "game/core/GameEngine.hpp"
#include "egolib/egoboo_setup.h"
#include "game/game.h"
#include "game/graphic.h"
#include "game/renderer_2d.h"
#include "game/module/Module.hpp"

//For deconstructor
#include "game/collision.h"
#include "game/profiles/ProfileSystem.hpp"
#include "game/bsp.h"
#include "game/script.h"

PlayingState::PlayingState()
{
	//ctor
}

PlayingState::~PlayingState()
{
	// get rid of all module data
    //game_quit_module();

    // deallocate any dynamically allocated collision memory
    collision_system_end();

    // deallocate any data used by the profile system
    //_profileSystem.end();

    // deallocate the obj_BSP
    obj_BSP_system_end();

    // deallocate any dynamically allocated scripting memory
    scripting_system_end();

    // clean up any remaining models that might have dynamic data
    MadStack_release_all();

    // free the cameras
    _cameraSystem.end();
}

void PlayingState::update()
{
    update_game();
}

void PlayingState::drawContainer()
{
	gfx_system_main();

	DisplayMsg_timechange++;
}

void PlayingState::beginState()
{
	// in-game settings
    SDL_ShowCursor( cfg.hide_mouse ? SDL_DISABLE : SDL_ENABLE );
    SDL_WM_GrabInput( cfg.grab_mouse ? SDL_GRAB_ON : SDL_GRAB_OFF );
}

bool PlayingState::notifyKeyDown(const int keyCode)
{
	switch(keyCode)
	{
		case SDLK_ESCAPE:
			_gameEngine->pushGameState(std::make_shared<InGameMenuState>(this));
		return true;
	}

	return ComponentContainer::notifyKeyDown(keyCode);
}