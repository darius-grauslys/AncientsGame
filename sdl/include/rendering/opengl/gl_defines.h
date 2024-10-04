#ifndef GL_DEFINES_H
#define GL_DEFINES_H

#include "platform_defines.h"
#include "rendering/opengl/glad/glad.h"
#include <SDL2/SDL_video.h>
#include <cglm/types.h>
#include <defines.h>
#include <cglm/mat4.h>
#include <cglm/clipspace/ortho_rh_zo.h>
#include <sdl_defines.h>

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

    uint32_t location_of__translation_mat_4_4;
    uint32_t location_of__projection_mat_4_4;
    uint32_t location_of__scale_mat_4_4;

    GLint success_code;
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
    int location_of__sprite_frame_row_col;
    int location_of__sprite_frame_width_height;
    bool is_sprite__allocated;
} GL_Sprite;

typedef struct GL_Sprite_Manager_t {
    GL_Sprite GL_sprites[MAX_QUANTITY_OF__SPRITES];
} GL_Sprite_Manager;

typedef struct GL_Camera_Data_t {
    mat4 gl_projection__matrix_4_4;
    mat4 gl_translation__matrix_4_4;
    mat4 gl_scale__matrix_4_4;
    bool is_allocated;
} GL_Camera_Data;

#define MAX_QUANTITY_OF__GL_CAMERA_DATA 16

typedef struct GL_Camera_Data_Manager_t {
    GL_Camera_Data gl_camera_datas[MAX_QUANTITY_OF__GL_CAMERA_DATA];
} GL_Camera_Data_Manager;

typedef struct GL_Chunk_Texture_t {
    PLATFORM_Texture GL_chunk_texture;
    const Chunk *p_chunk_owner;
} GL_Chunk_Texture;

#define MAX_QUANTITY_OF__CHUNK_TEXTURES\
    CHUNK_MANAGER__QUANTITY_OF_CHUNKS

typedef struct GL_Chunk_Texture_Manager_t {
    GL_Chunk_Texture GL_chunk_textures[MAX_QUANTITY_OF__CHUNK_TEXTURES];
    const Chunk *p_chunk_owners;
} GL_Chunk_Texture_Manager;

typedef struct GL_Gfx_Sub_Context_t {
    SDL_GLContext GL_context;
    GL_Shader_Manager GL_shader_manager;
    GL_Sprite_Manager GL_sprite_manager;
    GL_Camera_Data_Manager GL_camera_data_manager;
    Camera GL_camera__default;
} GL_Gfx_Sub_Context;

static inline
GL_Shader_Manager *GL_get_p_shader_manager_from__gfx_sub_context(
        GL_Gfx_Sub_Context *p_GL_gfx_sub_context) {
    return &p_GL_gfx_sub_context
        ->GL_shader_manager
        ;
}

static inline
GL_Sprite_Manager *GL_get_p_sprite_manager_from__gfx_sub_context(
        GL_Gfx_Sub_Context *p_GL_gfx_sub_context) {
    return &p_GL_gfx_sub_context
        ->GL_sprite_manager
        ;
}

static inline
GL_Camera_Data_Manager *GL_get_p_camera_data_manager_from__gfx_sub_context(
        GL_Gfx_Sub_Context *p_GL_gfx_sub_context) {
    return &p_GL_gfx_sub_context
        ->GL_camera_data_manager
        ;
}

static inline
GL_Shader_Manager *GL_get_p_shader_manager_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &((GL_Gfx_Sub_Context*)p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .p_SDL_gfx_sub_context)
        ->GL_shader_manager
        ;
}

static inline
GL_Sprite_Manager *GL_get_p_sprite_manager_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &((GL_Gfx_Sub_Context*)p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .p_SDL_gfx_sub_context)
        ->GL_sprite_manager
        ;
}

static inline
GL_Camera_Data_Manager *GL_get_p_camera_data_manager_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &((GL_Gfx_Sub_Context*)p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .p_SDL_gfx_sub_context)
        ->GL_camera_data_manager
        ;
}

#endif
