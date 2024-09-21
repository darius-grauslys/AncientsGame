#include "debug/debug.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_gfx_sub_context.h"
#include "rendering/opengl/gl_texture.h"
#include <SDL2/SDL_render.h>
#include <defines.h>
#include <rendering/sdl_gfx_context.h>
#include <sdl_defines.h>

PLATFORM_Gfx_Context __SDL_Gfx_Context;

void f_NONE_Allocate_Texture(
        PLATFORM_Texture *p_PLATFORM_texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {}

void f_NONE_Allocate_Texture__With_Path(
        PLATFORM_Texture *p_PLATFORM_texture,
        Texture_Allocation_Specification 
            *p_texture_allocation_specification,
        const char *path) {}

void f_NONE_Use_Texture(
        PLATFORM_Texture *p_PLATFORM_texture) {}

void f_NONE_Release_Texture(
        PLATFORM_Texture *p_PLATFORM_texture) {}

void SDL_initialize_gfx_context(
        Game *p_game,
        SDL_Gfx_Sub_Context__Kind the_kind_of__sub_context) {
    
    if (!get_p_PLATFORM_gfx_context_from__game(p_game)) {
        p_game->p_PLATFORM_gfx_context =
            &__SDL_Gfx_Context;
    }

    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    SDL_Gfx_Sub_Context__Wrapper *p_SDL_gfx_sub_context__wrapper =
        &p_PLATFORM_gfx_context->SDL_gfx_sub_context__wrapper;

    if (p_SDL_gfx_sub_context__wrapper
            ->p_SDL_gfx_sub_context) {
        SDL_dispose_gfx_context(
                p_PLATFORM_gfx_context);
    }

    switch (the_kind_of__sub_context) {
        case SDL_Gfx_Sub_Context__Vulcan:
            debug_abort("SDL::SDL_initialize_gfx_context, Vulcan is not yet supported.");
            return;
        case SDL_Gfx_Sub_Context__OpenGL_1_2:
            debug_abort("SDL::SDL_initialize_gfx_context, OpenGL_1_2 is not yet supported.");
            return;
        default:
        case SDL_Gfx_Sub_Context__None:
            debug_warning("SDL::SDL_initialize_gfx_context, graphics backend set to SDL_Gfx_Sub_Context__None. No graphics will be rendered!");
            break;
        case SDL_Gfx_Sub_Context__OpenGL_3_0:

            SDL_GL_SetAttribute(
                    SDL_GL_CONTEXT_MAJOR_VERSION, 
                    3);
            SDL_GL_SetAttribute(
                    SDL_GL_CONTEXT_MINOR_VERSION, 
                    0);
            SDL_GL_SetAttribute(
                    SDL_GL_CONTEXT_PROFILE_MASK, 
                    SDL_GL_CONTEXT_PROFILE_CORE);  

            SDL_Window *p_SDL_window = 
                SDL_CreateWindow(
                    "AncientsGame", 0, 0, 800, 600, 
                    SDL_WINDOW_OPENGL
                    | SDL_WINDOW_SHOWN);

            p_PLATFORM_gfx_context
                ->p_SDL_window =
                p_SDL_window;

            p_SDL_gfx_sub_context__wrapper
                ->p_SDL_gfx_sub_context = 
                malloc(sizeof(GL_Gfx_Sub_Context));
            debug_info__verbose("SDL::SDL_initialize_gfx_context, OpenGL_3_0 (malloc)");

            if (!p_SDL_gfx_sub_context__wrapper
                    ->p_SDL_gfx_sub_context) {
                debug_abort("SDL::SDL_initialize_gfx_context, failed to allocate sub context.");
                return;
            }

            p_SDL_gfx_sub_context__wrapper
                ->f_SDL_clear_screen =
                GL_clear_screen;

            p_SDL_gfx_sub_context__wrapper
                ->f_SDL_allocate_texture =
                GL_allocate_texture;
            p_SDL_gfx_sub_context__wrapper
                ->f_SDL_allocate_texture__with_path =
                GL_allocate_texture__with_path;
            p_SDL_gfx_sub_context__wrapper
                ->f_SDL_use_texture =
                GL_use_texture;
            p_SDL_gfx_sub_context__wrapper
                ->f_SDL_release_texture =
                GL_release_texture;

            GL_initialize_gfx_sub_context(
                    p_PLATFORM_gfx_context,
                    (GL_Gfx_Sub_Context*)
                    p_SDL_gfx_sub_context__wrapper
                    ->p_SDL_gfx_sub_context);

            break;
    }

    p_SDL_gfx_sub_context__wrapper
        ->the_kind_of__sub_context =
        the_kind_of__sub_context;
}

void SDL_dispose_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {

    SDL_Gfx_Sub_Context *p_SDL_gfx_sub_context =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .p_SDL_gfx_sub_context
        ;

    switch (p_PLATFORM_gfx_context
            ->SDL_gfx_sub_context__wrapper
            .the_kind_of__sub_context) {
        default:
            debug_abort("SDL::SDL_dispose_gfx_context, unsupported context.");
            return;
        case SDL_Gfx_Sub_Context__None:
            break;
        case SDL_Gfx_Sub_Context__OpenGL_3_0:
            GL_dispose_gfx_sub_context(
                    (GL_Gfx_Sub_Context*)p_SDL_gfx_sub_context);
            free(p_SDL_gfx_sub_context);
            debug_info__verbose(
                    "SDL::SDL_dispose_gfx_context, OpenGL_3_0 (free)");
            break;
    }

    SDL_DestroyWindow(p_PLATFORM_gfx_context
            ->p_SDL_window);

    p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .the_kind_of__sub_context =
        SDL_Gfx_Sub_Context__None;
}

void SDL_clear_screen(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    __SDL_Gfx_Context
        .SDL_gfx_sub_context__wrapper
        .f_SDL_clear_screen(
                p_PLATFORM_gfx_context);
}

void PLATFORM_allocate_texture(
        PLATFORM_Texture *texture, 
        Texture_Allocation_Specification 
            *p_texture_allocation_specification) {
    __SDL_Gfx_Context
        .SDL_gfx_sub_context__wrapper
        .f_SDL_allocate_texture(
                texture,
                p_texture_allocation_specification);
}

void PLATFORM_allocate_texture__with_path(
        PLATFORM_Texture *texture, 
        Texture_Allocation_Specification 
            *p_texture_allocation_specification, 
        const char *path) {
    __SDL_Gfx_Context
        .SDL_gfx_sub_context__wrapper
        .f_SDL_allocate_texture__with_path(
                texture,
                p_texture_allocation_specification,
                path);
}

void PLATFORM_use_texture(PLATFORM_Texture *texture) {
    __SDL_Gfx_Context
        .SDL_gfx_sub_context__wrapper
        .f_SDL_use_texture(
                texture);
}

void PLATFORM_release_texture(
        PLATFORM_Texture *texture) {
    __SDL_Gfx_Context
        .SDL_gfx_sub_context__wrapper
        .f_SDL_release_texture(
                texture);
}
