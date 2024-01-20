#include <defines.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

///
/// If you're looking to make a new backend for
/// AncientsGame, this is the place to be.
///
/// This file is the comprehensive list of all
/// things which must be defined, and where they
/// should be defined.
///

// debug/PLATFORM_debug.c
void debug_info(const char *msg_fmt, ...) {
#ifndef NDEBUG
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[30;1minfo:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);
    
    printf("\n");
#endif
}
void debug_warning(const char *msg_fmt, ...) {
#ifndef NDEBUG
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[33;1mwarning:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);
    
    printf("\n");
#endif
}
void debug_error(const char *msg_fmt, ...) {
#ifndef NDEBUG
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[31;1merror:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);

    printf("\n");

    // create core dump, but keep going.
    if (!fork()) { abort(); }
#endif
}
void debug_abort(const char *msg_fmt, ...) {
#ifndef NDEBUG
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[31;1mabort:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);

    printf("\n");

    abort();
#endif
}

// rendering/PLATFORM_sprite.c
void PLATFORM_init_sprite(
        PLATFORM_Sprite *sprite,
        Entity *entity) { }
// rendering/PLATFORM_animate_sprite.c
void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *sprite_wrapper) { }
// rendering/PLATFORM_gfx_context.c
void PLATFORM_init_gfx_context(PLATFORM_Gfx_Context *gfx_context) { }
void PLATFORM_init_rendering__menu(PLATFORM_Gfx_Context *gfx_context) { }
void PLATFORM_init_rendering__game(PLATFORM_Gfx_Context *gfx_context) { }
void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager) { }
// rendering/PLATFORM_render_entity.c
void PLATFORM_render_entity(
        Entity *entity,
        Game *game) { }
// input/PLATFORM_input.c
void PLATFORM_poll_input(Game *game) { }
// PLATFORM_game.c
void PLATFORM_pre_render(Game *game) { }
void PLATFORM_post_render(Game *game) { }

