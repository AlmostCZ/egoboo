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

/// @file game/GUI/CharacterStatus.hpp
/// @author Johan Jansen

#pragma once

#include "game/GUI/Component.hpp"

class Object;
namespace Ego { namespace GUI { class ProgressBar; } }

namespace Ego {
namespace GUI {

class CharacterStatus : public Component {
public:
    CharacterStatus(const std::shared_ptr<Object> &object);

    virtual void draw(DrawingContext& drawingContext) override;

    std::shared_ptr<Object> getObject() const { return _object.lock(); }

private:
    float draw_one_xp_bar(float x, float y, Uint8 ticks);
    float draw_character_xp_bar(const ObjectRef character, float x, float y);
    float draw_one_bar(Uint8 bartype, float x, float y, int ticks, int maxticks);
    void  draw_one_character_icon(const ObjectRef item, float x, float y, bool draw_ammo, Uint8 sparkle_override);
    std::weak_ptr<Object> _object;
    std::shared_ptr<GUI::ProgressBar> _chargeBar;
};

} // namespace GUI
} // namespace Ego
