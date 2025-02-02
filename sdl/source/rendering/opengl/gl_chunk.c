#include "debug/debug.h"
#include "defines_weak.h"
#include "numerics.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/opengl/gl_chunk_texture_manager.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_framebuffer.h"
#include "rendering/opengl/gl_gfx_sub_context.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_manager.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/gl_vertex_object.h"
#include "rendering/opengl/gl_viewport.h"
#include "vectors.h"
#include "world/tile.h"
#include <GL/gl.h>
#include <rendering/opengl/gl_chunk.h>

void GL_render_chunk(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager =
        GL_get_p_chunk_texture_manager_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);
    GL_Chunk_Texture *p_GL_chunk_texture =
        GL_dehash_chunk_to__chunk_texture(
                p_GL_chunk_texture_manager,
                p_chunk_map_node->p_chunk__here);

    if (!p_GL_chunk_texture) {
        debug_warning("You need to call PLATFORM_update_chunk(s) for this chunk at least once.");
        debug_error("SDL::GL::GL_render_chunk, failed to acquire p_chunk's GL_Chunk_Texture.");
        return;
    }

    // TODO: magic numbers
    Vector__3i32F4 chunk_pos_in__world__3i32f4 =
        vector_3i32_to__vector_3i32F4(
                p_chunk_map_node->position_of__chunk_3i32);

    chunk_pos_in__world__3i32f4.x__i32F4 *= 64;
    chunk_pos_in__world__3i32f4.y__i32F4 *= 64;
    chunk_pos_in__world__3i32f4.x__i32F4 += i32_to__i32F4(32);
    chunk_pos_in__world__3i32f4.y__i32F4 += i32_to__i32F4(28);
    chunk_pos_in__world__3i32f4.z__i32F4 = 
        i32_to__i32F4(10);

    GL_Shader_2D *p_GL_shader__chunk =
        GL_get_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context),
                shader_string__chunk);

    // TODO: null checks

    Camera *p_camera =
        p_PLATFORM_gfx_window
        ->p_active_camera
        ;

    GL_Gfx_Sub_Context *p_GL_gfx_sub_context =
        GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);
    use_vertex_object(&p_GL_gfx_sub_context->GL_vertex_object__unit_square);

    use_shader_2d(p_GL_shader__chunk);

    GL_link_data_to__shader(
            p_PLATFORM_gfx_context,
            p_GL_shader__chunk,
            p_camera,
            chunk_pos_in__world__3i32f4,
            i32_to__i32F4(4));
    
    PLATFORM_use_texture(
            p_PLATFORM_gfx_context, 
            p_GL_chunk_texture->p_GL_chunk_texture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    chunk_pos_in__world__3i32f4.y__i32F4 += i32_to__i32F4(8);
    chunk_pos_in__world__3i32f4.z__i32F4 = 
        i32_to__i32F4(0);

    if (GL_does_shader_utilize__model_mat_4_4(
                p_GL_shader__chunk)) {
        GL_link_model_data_to__shader(
                p_GL_shader__chunk, 
                chunk_pos_in__world__3i32f4, 
                i32_to__i32F4(4));
    }

    PLATFORM_use_texture(
            p_PLATFORM_gfx_context, 
            p_GL_chunk_texture->p_GL_chunk_texture__sprite_cover);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GL_update_chunk(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager =
        GL_get_p_chunk_texture_manager_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);
    GL_Chunk_Texture *p_GL_chunk_texture =
        GL_dehash_chunk_to__chunk_texture(
                p_GL_chunk_texture_manager,
                p_chunk_map_node->p_chunk__here);

    if (!p_GL_chunk_texture) {
        GL_allocate_chunk_texture_with__chunk_texture_manager(
                p_PLATFORM_gfx_context, 
                p_GL_chunk_texture_manager, 
                p_chunk_map_node->p_chunk__here);
        p_GL_chunk_texture =
            GL_dehash_chunk_to__chunk_texture(
                    p_GL_chunk_texture_manager,
                    p_chunk_map_node->p_chunk__here);
        if (!p_GL_chunk_texture) {
            debug_error("SDL::GL::GL_update_chunk failed to allocate chunk texture.");
            return;
        }
    }

    GL_Shader_2D *p_GL_shader__passthrough=
        GL_get_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                shader_string__passthrough);

    if (!p_GL_shader__passthrough) {
        debug_warning("Did you forget to attach a chunk shader?");
        debug_error("SDL::GL::GL_update_chunk, p_GL_chunk_texture_manager has p_GL_shader__chunk == 0.");
        return;
    }

    GL_Framebuffer *p_GL_framebuffer =
        p_GL_chunk_texture_manager
        ->p_GL_framebuffer__chunk_rendering;

    float clear_color[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, clear_color);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    GL_use_framebuffer_as__target(
            p_GL_framebuffer);
    GL_bind_texture_to__framebuffer(
            p_GL_framebuffer, 
            p_GL_chunk_texture
            ->p_GL_chunk_texture__sprite_cover);
    glClear(GL_COLOR_BUFFER_BIT);
    GL_bind_texture_to__framebuffer(
            p_GL_framebuffer, 
            p_GL_chunk_texture
            ->p_GL_chunk_texture);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(
            clear_color[0],
            clear_color[1],
            clear_color[2],
            clear_color[3]);

    GL_Viewport_Stack *p_GL_viewport_stack =
        GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);

    use_shader_2d(
            p_GL_shader__passthrough);

    Chunk *p_chunk = 
        p_chunk_map_node
        ->p_chunk__here;

    GL_Vertex_Object *p_GL_vertex_object =
        &GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context)
        ->GL_vertex_object__unit_square;

    PLATFORM_Texture *p_PLATFORM_texture_of__tilesheet_ground =
        p_GL_chunk_texture_manager
        ->p_PLATFORM_texture_of__tilesheet_ground;
    PLATFORM_Texture *p_PLATFORM_texture_of__tilesheet_cover =
        p_GL_chunk_texture_manager
        ->p_PLATFORM_texture_of__tilesheet_cover;

    // TODO: magic numbers
    float width_of__uv  = 1.0 / (256.0 / 8);
    float height_of__uv = 1.0 / (256.0 / 8);

    use_vertex_object(p_GL_vertex_object);

    for (Index__u8 index_of__y_tile = 0;
            index_of__y_tile < CHUNK_WIDTH__IN_TILES;
            index_of__y_tile++) {
        for (Index__u8 index_of__x_tile = 0;
                index_of__x_tile < CHUNK_WIDTH__IN_TILES;
                index_of__x_tile++) {
            GL_push_viewport(
                    p_GL_viewport_stack, 
                    index_of__x_tile * TILE_WIDTH__IN_PIXELS, 
                    index_of__y_tile * TILE_WIDTH__IN_PIXELS, 
                    TILE_WIDTH__IN_PIXELS, 
                    TILE_WIDTH__IN_PIXELS);

            Tile *p_tile =
                &p_chunk->tiles[
                index_of__x_tile
                    + (CHUNK_WIDTH__IN_TILES - 1 - index_of__y_tile) 
                    * CHUNK_WIDTH__IN_TILES];

            Local_Tile_Vector__3u8 local_tile_vector = {
                index_of__x_tile, 
                (7 - index_of__y_tile), 0};

            Tile_Render_Result render_result =
                get_tile_render_result(
                        p_chunk_map_node,
                        local_tile_vector);

            switch (p_tile->the_kind_of_tile__this_tile_is) {
                case Tile_Kind__None:
                    break;
                default:
                    ;
                    int index =
                        render_result.tile_index__ground
                        - 1;
                    GL_bind_texture_to__framebuffer(
                            p_GL_framebuffer, 
                            p_GL_chunk_texture
                            ->p_GL_chunk_texture);
                    PLATFORM_use_texture(
                            p_PLATFORM_gfx_context, 
                            p_GL_chunk_texture_manager
                            ->p_PLATFORM_texture_of__tilesheet_ground);
                    GL_render_with__shader__passthrough_using__index_sampling(
                            p_GL_shader__passthrough, 
                            index % 32, 
                            (int)(index / 32), 
                            width_of__uv, 
                            height_of__uv,
                            false,
                            false);
                    break;
            }

            switch (p_tile->the_kind_of_tile_cover__this_tile_has) {
                case Tile_Cover_Kind__None:
                    break;
                default:
                    ;
                    int index = 
                        (render_result.tile_index__cover
                        & MASK(10))
                        - 1
                        ;
                    GL_bind_texture_to__framebuffer(
                            p_GL_framebuffer, 
                            p_GL_chunk_texture
                            ->p_GL_chunk_texture);
                    PLATFORM_use_texture(
                            p_PLATFORM_gfx_context, 
                            p_GL_chunk_texture_manager
                            ->p_PLATFORM_texture_of__tilesheet_cover);
                    GL_render_with__shader__passthrough_using__index_sampling(
                            p_GL_shader__passthrough, 
                            index % 32, 
                            (int)(index / 32), 
                            width_of__uv, 
                            height_of__uv,
                            does_wall_adjacency_require__vflip(
                                render_result.wall_adjacency),
                            false);
                    break;
            }

            switch (p_tile->the_kind_of_tile_cover__this_tile_has) {
                case Tile_Cover_Kind__None:
                    break;
                default:
                    ;
                    int index = 
                        (render_result.tile_index__sprite_cover
                        & MASK(10))
                        - 1
                        ;
                    GL_bind_texture_to__framebuffer(
                            p_GL_framebuffer, 
                            p_GL_chunk_texture
                            ->p_GL_chunk_texture__sprite_cover);
                    PLATFORM_use_texture(
                            p_PLATFORM_gfx_context, 
                            p_GL_chunk_texture_manager
                            ->p_PLATFORM_texture_of__tilesheet_cover);
                    GL_render_with__shader__passthrough_using__index_sampling(
                            p_GL_shader__passthrough, 
                            index % 32, 
                            (int)(index / 32), 
                            width_of__uv, 
                            height_of__uv,
                            does_wall_adjacency_require__vflip(
                                render_result.wall_adjacency),
                            false);
                    break;
            }

            GL_pop_viewport(p_GL_viewport_stack);
        }
    }

    GL_unbind_framebuffer();
}

void GL_update_chunks(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager *p_chunk_manager) {
    Chunk_Manager__Chunk_Map_Node *p_current__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *p_current_sub__chunk_map_node;

    for (uint8_t y=0; 
            y 
            < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            y++) {
        p_current_sub__chunk_map_node =
            p_current__chunk_map_node;
        for (uint8_t x=0; 
                x 
                < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
                x++) {
            PLATFORM_update_chunk(
                    p_PLATFORM_gfx_context, 
                    p_chunk_manager, 
                    p_current_sub__chunk_map_node);

            p_current_sub__chunk_map_node =
                p_current_sub__chunk_map_node->p_east__chunk_map_node;
        }
        p_current__chunk_map_node =
            p_current__chunk_map_node->p_south__chunk_map_node;
    }
}
