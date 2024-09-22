#include "defines_weak.h"
#include "platform_defines.h"
#include "rendering/opengl/gl_gfx_sub_context.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_sprite.h"
#include <rendering/opengl/gl_sprite_manager.h>
#include <sdl_defines.h>

void GL_initialize_sprite_manager(
        GL_Sprite_Manager *p_GL_sprite_manager) {
    for (Index__u16 index_of__sprite = 0;
            index_of__sprite < MAX_QUANTITY_OF__SPRITES;
            index_of__sprite++) {
        GL_set_sprite_as__deallocated(
                &p_GL_sprite_manager
                ->GL_sprites[index_of__sprite]);
    }
}

GL_Sprite *GL_allocate_sprite_with__sprite_manager(
        GL_Sprite_Manager *p_GL_sprite_manager) {
    for (Index__u16 index_of__sprite = 0;
            index_of__sprite < MAX_QUANTITY_OF__SPRITES;
            index_of__sprite++) {
        GL_Sprite *p_GL_sprite =
            &p_GL_sprite_manager
            ->GL_sprites[index_of__sprite];

        if (GL_is_sprite__allocated(p_GL_sprite))
            continue;

        GL_set_sprite_as__allocated(p_GL_sprite);
        return p_GL_sprite;
    }
    return 0;
}

void GL_allocate_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    p_PLATFORM_sprite
        ->p_SDL_sprite =
        GL_allocate_sprite_with__sprite_manager(
                &GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context)
                ->GL_sprite_manager);
}

void GL_release_sprite_from__sprite_manager(
        GL_Sprite_Manager *p_GL_sprite_manager,
        GL_Sprite *p_GL_sprite) {
    i16 index = 
        p_GL_sprite
        - p_GL_sprite_manager
        ->GL_sprites
        ;
    
    if (index < 0 || index >= MAX_QUANTITY_OF__SPRITES) {
        debug_abort("SDL::GL_release_sprite_from__sprite_manager, p_GL_sprite is not allocated with this manager, or is invalid.");
        debug_warning("This might cause a GPU memory leak!");
        return;
    }

    GL_set_sprite_as__deallocated(p_GL_sprite);
    GL_release_sprite_vertext_object(p_GL_sprite);
}

void GL_release_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    GL_Sprite *p_GL_sprite =
        GL_get_p_sprite_from__PLATFORM_sprite(
                p_PLATFORM_sprite);
    GL_release_sprite_vertext_object(p_GL_sprite);
    GL_release_sprite_from__sprite_manager(
            &GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context)
            ->GL_sprite_manager, 
            p_GL_sprite);
}

void GL_dispose_sprite_manager(
        GL_Sprite_Manager *p_GL_sprite_manager) {
    for (Index__u16 index_of__sprite = 0;
            index_of__sprite < MAX_QUANTITY_OF__SPRITES;
            index_of__sprite++) {
        GL_Sprite *p_GL_sprite =
                &p_GL_sprite_manager
                ->GL_sprites[index_of__sprite];
        if (!GL_is_sprite__allocated(p_GL_sprite))
            continue;
        GL_release_sprite_vertext_object(p_GL_sprite);
        GL_set_sprite_as__deallocated(p_GL_sprite);
    }
}
