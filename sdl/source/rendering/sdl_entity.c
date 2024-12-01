#include "defines_weak.h"
#include "game.h"
#include <rendering/sdl_entity.h>

void PLATFORM_render_entity(
        Entity *p_entity,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

#ifndef NDEBUG
    if (!p_PLATFORM_gfx_context
            ->SDL_gfx_sub_context__wrapper
            .f_SDL_render_entity) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL::PLATFORM_render_entity, f_SDL_render_entity == 0.");
        return;
    }
#endif

    p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_render_entity(
                &p_PLATFORM_gfx_context
                ->SDL_graphics_window__main,
                p_entity);
}
