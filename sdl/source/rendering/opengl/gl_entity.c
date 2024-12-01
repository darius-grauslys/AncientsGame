#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_gfx_sub_context.h"
#include "rendering/opengl/gl_numerics.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_sprite.h"
#include <rendering/opengl/gl_entity.h>
#include <sdl_defines.h>
#include "vectors.h"

void GL_render_entity(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Entity *p_entity) {
    GL_render_sprite(
            p_PLATFORM_gfx_window, 
            &p_entity->sprite_wrapper,
            p_entity->hitbox.position__3i32F4);
}
