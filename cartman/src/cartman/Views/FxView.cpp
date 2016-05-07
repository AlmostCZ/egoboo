//********************************************************************************************
//*
//*    This file is part of Cartman.
//*
//*    Cartman is free software: you can redistribute it and/or modify it
//*    under the terms of the GNU General Public License as published by
//*    the Free Software Foundation, either version 3 of the License, or
//*    (at your option) any later version.
//*
//*    Cartman is distributed in the hope that it will be useful, but
//*    WITHOUT ANY WARRANTY; without even the implied warranty of
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*    General Public License for more details.
//*
//*    You should have received a copy of the GNU General Public License
//*    along with Cartman.  If not, see <http://www.gnu.org/licenses/>.
//*
//*
//********************************************************************************************

#include "cartman/Views/FxView.hpp"
#include "cartman/cartman_gui.h"
#include "cartman/cartman_functions.h"
#include "cartman/cartman_gfx.h"
#include "cartman/cartman_typedef.h"
#include "cartman/cartman_math.h"

namespace Cartman {

void FxView::render(Gui::Window& window, float zoom_hrz, float zoom_vrt) {
    if (!window.on || !HAS_BITS(window.mode, WINMODE_FX)) return;

    if (NULL == window.pmesh) window.pmesh = &mesh;

    float zoom_fx = (zoom_hrz < 1.0f) ? zoom_hrz : 1.0f;

    glPushAttrib(GL_SCISSOR_BIT | GL_VIEWPORT_BIT | GL_ENABLE_BIT);
    {
        // set the viewport transformation
        Ego::Renderer::get().setViewportRectangle(window.position.getX(),
                                                  sdl_scr.height - (window.position.getY() + window.surfacey), window.surfacex, window.surfacey);

        // clip the viewport
        Ego::Renderer::get().setScissorTestEnabled(true);
        Ego::Renderer::get().setScissorRectangle(window.position.getY(),
                                                 sdl_scr.height - (window.position.getY() + window.surfacey), window.surfacex, window.surfacey);

        cartman_begin_ortho_camera_hrz(window, &cam, zoom_hrz, zoom_hrz);
        {
            int mapxstt = std::floor((cam.x - cam.w  * 0.5f) / Info<float>::Grid::Size()) - 1.0f;
            int mapystt = std::floor((cam.y - cam.h  * 0.5f) / Info<float>::Grid::Size()) - 1.0f;

            int mapxend = std::ceil((cam.x + cam.w  * 0.5f) / Info<float>::Grid::Size()) + 1.0f;
            int mapyend = std::ceil((cam.y + cam.h  * 0.5f) / Info<float>::Grid::Size()) + 1.0f;

            for (int mapy = mapystt; mapy <= mapyend; mapy++) {
                if (mapy < 0 || mapy >= window.pmesh->info.getTileCountY()) continue;
                int y = mapy * Info<int>::Grid::Size();

                for (int mapx = mapxstt; mapx <= mapxend; mapx++) {
                    if (mapx < 0 || mapx >= window.pmesh->info.getTileCountX()) continue;
                    int x = mapx * Info<int>::Grid::Size();

                    int fan = window.pmesh->get_ifan(mapx, mapy);

                    std::shared_ptr<Ego::Texture> tx_tile = NULL;
                    if (VALID_MPD_TILE_RANGE(fan)) {
                        tx_tile = tile_at(window.pmesh, fan);
                    }

                    if (NULL != tx_tile) {
                        ogl_draw_sprite_2d(tx_tile, x, y, Info<int>::Grid::Size(), Info<int>::Grid::Size());

                        // water is whole tile
                        draw_tile_fx(x, y, window.pmesh->fan2[fan].fx, 4.0f * zoom_fx);
                    }
                }
            }
        }
        cartman_end_ortho_camera();

    }
    glPopAttrib();
}

} // namespace Cartman
