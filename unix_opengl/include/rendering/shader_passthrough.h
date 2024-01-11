#ifndef SHADER_PASSTHROUGH_H
#define SHADER_PASSTHROUGH_H

#include <rendering/shader.h>
#include <rendering/texture.h>
#include <rendering/vertex_object.h>

typedef Shader_2D Shader_2D_Passthrough;

void get_source__shader_passthrough(
        const char **source_vertex,
        const char **source_fragment);
void init_shader_2d_as__shader_passthrough(
        Shader_2D_Passthrough *shader);

void inline render_with__shader_passthrough(
        Shader_2D_Passthrough *shader,
        PLATFORM_Texture *texture_source,
        Vertex_Object *vertex_object
        ) {
    use_shader_2d(shader);
    use_vertex_object(vertex_object);
    glBindTexture(GL_TEXTURE_2D, texture_source->handle);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

#endif
