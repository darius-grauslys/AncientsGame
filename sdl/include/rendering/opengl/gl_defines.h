#ifndef GL_DEFINES_H
#define GL_DEFINES_H

#include "platform_defines.h"
#include "rendering/opengl/glad/glad.h"
#include <SDL2/SDL_video.h>
#include <defines.h>
#include <cglm/mat4.h>
#include <cglm/clipspace/ortho_rh_zo.h>

typedef struct GL_Vertex_Object_t {
    u32 handle__vertex_buffer;
    u32 handle__attribute_array;
    u32 handle__element_buffer;
    u32 vertex_count;
} GL_Vertex_Object;

#define MAX_LENGTH_OF__SHADER_STRING 32
typedef char Shader_String[MAX_LENGTH_OF__SHADER_STRING];
typedef const char Shader_String__Const[MAX_LENGTH_OF__SHADER_STRING];

extern Shader_String__Const shader_string__passthrough;
extern Shader_String__Const shader_string__sprite;

typedef struct GL_Shader_2D_t {
    Shader_String GL_shader_string;
    uint32_t handle;

    uint32_t vertex_handle;
    uint32_t fragment_handle;

    mat4 mat4_projection, mat4_view, mat4_model;

    uint32_t success_code;
    bool is_shader__allocated;
} GL_Shader_2D;

#define MAX_QUANTITY_OF__SHADERS 16

typedef struct GL_Shader_Manager_t {
    GL_Shader_2D GL_shaders[MAX_QUANTITY_OF__SHADERS];
    GL_Shader_2D *p_GL_shader__sprite;
    GL_Shader_2D *p_GL_shader__world;
} GL_Shader_Manager;

typedef struct GL_Sprite_t {
    GL_Vertex_Object GL_vertex_object;
    GL_Shader_2D *p_GL_shader;
    float sprite_frame__width;
    float sprite_frame__height;
    int location_of__sprite_frame_row_col;
    int location_of__sprite_frame_width_height;
    bool is_sprite__allocated;
} GL_Sprite;

typedef struct GL_Sprite_Manager_t {
    GL_Sprite GL_sprites[MAX_QUANTITY_OF__SPRITES];
} GL_Sprite_Manager;

typedef struct GL_Gfx_Sub_Context_t {
    SDL_GLContext GL_context;
    GL_Shader_Manager GL_shader_manager;
    GL_Sprite_Manager GL_sprite_manager;
} GL_Gfx_Sub_Context;

#endif
