#ifndef GL_DEFINES_H
#define GL_DEFINES_H

#include <defines.h>
#include <cglm/mat4.h>
#include <cglm/clipspace/ortho_rh_zo.h>

#define GL_GLEXT_PROTOTYPES 1

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>

typedef struct GL_Vertex_Object_t {
    u32 handle__vertex_buffer;
    u32 handle__attribute_array;
    u32 handle__element_buffer;
    u32 vertex_count;
} GL_Vertex_Object;

typedef struct GL_Shader_2D_t {
    uint32_t handle;

    uint32_t vertex_handle;
    uint32_t fragment_handle;

    mat4 mat4_projection, mat4_view, mat4_model;

    uint32_t success_code;
} GL_Shader_2D;

#endif
