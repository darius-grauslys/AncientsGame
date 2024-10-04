#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "input/input.h"
#include "numerics.h"
#include "platform.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/gl_vertex_object.h"
#include "sdl_defines.h"
#include "world/sdl_camera.h"

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {
    
    GL_Shader_2D_Passthrough shader;
    initialize_shader_2d_as__shader_passthrough(
            &shader);
    GL_Vertex_Object vertex_object;
    initialize_vertex_object_as__unit_square(&vertex_object);

    PLATFORM_Texture texture;
    Texture_Allocation_Specification texture_alloc_spec;
    texture_alloc_spec.p_PLATFORM_graphics_window =
        &get_p_PLATFORM_gfx_context_from__game(p_game)
        ->graphics_window__main_window;
    texture_alloc_spec.texture_flags =
        TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_64x64,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__2);

    PLATFORM_allocate_texture__with_path(
            &texture, 
            &texture_alloc_spec, 
            "/home/shalidor/Projects/AncientsGame/core/assets/entities/entity_sprite__16x16/player.png");

    Sprite_Allocation_Specification sprite_alloc_spec;

    sprite_alloc_spec.the_kind_of__sprite_allocation =
        Sprite_Allocation_Kind__Entity;
    sprite_alloc_spec.the_kind_of__entity_this__sprite_is =
        Entity_Kind__Player;
    
    Entity entity;
    entity.sprite_wrapper.p_sprite =
        PLATFORM_allocate_sprite(
                get_p_PLATFORM_gfx_context_from__game(p_game), 
                &sprite_alloc_spec);
    entity.sprite_wrapper.frame__current = 0;


    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context = 
        get_p_PLATFORM_gfx_context_from__game(p_game);
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {

        manage_game__pre_render(p_game);

        PLATFORM_render_entity(
                &entity,
                p_game);

        if (is_input__forward_released(
                    get_p_input_from__game(p_game))) {
            entity.sprite_wrapper.frame__current =
                (entity.sprite_wrapper.frame__current+1)
                % 255;
        }

        // use_shader_2d(&shader);
        // PLATFORM_use_texture(
        //         get_p_PLATFORM_gfx_context_from__game(p_game),
        //         &texture);
        // use_vertex_object(&vertex_object);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        manage_game__post_render(p_game);
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}

// PLATFORM_Graphics_Window 
// *PLATFORM_get_p_graphics_window_with__graphics_window_kind(
//         PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
//         enum Graphics_Window_Kind the_kind_of__graphics_window,
//         Identifier__u32 identifier_of__graphics_window) {
//     return 0;
// }
// 
// PLATFORM_Gfx_Context *PLATFORM_get_p_gfx_context_from__graphics_window(
//         PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
//     return 0;
// }
//
// void PLATFORM_render_chunk(
//         PLATFORM_Gfx_Context *context,
//         Chunk *chunk) {}
// 
