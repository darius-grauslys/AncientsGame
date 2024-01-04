#ifndef SHADER_H
#define SHADER_H

#include <stdint.h>

typedef struct Shader_2D_t {
    uint32_t handle;

    uint32_t vertex_handle;
    uint32_t fragment_handle;

    uint32_t success_code;
} Shader_2D;

int init_shader_2d(Shader_2D *shader, const char *source_vertex,
        const char *source_fragment);
int use_shader_2d(Shader_2D *shader);
int release_shader_2d(Shader_2D *shader);

#endif 
