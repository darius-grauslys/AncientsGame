#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "input/input.h"
#include "platform.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/gl_vertex_object.h"
#include "sdl_defines.h"

void create_rect(GL_Vertex_Object *vertex_object) {
// void create_rect(unsigned int *vao, unsigned int *vbo, unsigned int *ebo)
    float rect_vertices[] = {
        -1.0f,  1.0f,  0.0f,        0.0f, 1.0f, // top left
         1.0f,  1.0f,  0.0f,        1.0f, 1.0f, // top right
         1.0f, -1.0f,  0.0f,        1.0f, 0.0f, // bottom right
        -1.0f, -1.0f,  0.0f,        0.0f, 0.0f  // bottom left
    };
    unsigned int rect_indices[] = { 0, 1, 2, 0, 2, 3 };

    uint32_t *vao = &vertex_object->handle__attribute_array;
    uint32_t *vbo = &vertex_object->handle__vertex_buffer;
    uint32_t *ebo = &vertex_object->handle__element_buffer;

    initialize_vertex_object(vertex_object);

    buffer_vertex_object(
            vertex_object, 
            sizeof(rect_vertices),
            sizeof(rect_vertices) / (sizeof(float) * 5), 
            rect_vertices);
    buffer_vertex_object__element_buffer(
            vertex_object,
            sizeof(rect_indices),
            rect_indices);
    set_attribute_vertex_object(
            vertex_object, 
            0, 
            3, 
            GL_FLOAT, 
            false, 
            5 * sizeof(float), 
            (void *)0);
    set_attribute_vertex_object(
            vertex_object, 
            1, 
            2, 
            GL_FLOAT, 
            false, 5 * sizeof(float), 
            (void *)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLAPIENTRY
debug_callback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, 
          "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

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
    create_rect(&vertex_object);

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

    glViewport(0,0,800,600);

    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {

        use_shader_2d(&shader);
        PLATFORM_use_texture(&texture);
        use_vertex_object(&vertex_object);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        manage_game(p_game);
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
