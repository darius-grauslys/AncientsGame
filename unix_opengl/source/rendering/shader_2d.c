#include <rendering/shader.h>
#include <rendering/glad/glad.h>
#include <debug/debug.h>
#include <stddef.h>

int initialize_shader_2d(Shader_2D *shader, const char *source_vertex,
        const char *source_fragment) {
    shader->handle = 0;
    shader->vertex_handle = 0;
    shader->fragment_handle = 0;

    debug_info("compiling vertex shader...");
    shader->vertex_handle = 
        glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->vertex_handle, 1, &source_vertex, NULL);
    glCompileShader(shader->vertex_handle);

    glGetShaderiv(shader->vertex_handle, GL_COMPILE_STATUS,
            &shader->success_code);
    if (!shader->success_code) {
        char log[512];
        glGetShaderInfoLog(shader->vertex_handle, 512, NULL, log);
        debug_error("Failed to load vertex shader: %s", log);
        glDeleteShader(shader->vertex_handle);
        return shader->success_code;
    }

    debug_info("compiling fragment shader...");
    shader->fragment_handle = 
        glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->fragment_handle, 1, &source_fragment, NULL);
    glCompileShader(shader->fragment_handle);

    glGetShaderiv(shader->fragment_handle, GL_COMPILE_STATUS,
            &shader->success_code);
    if (!shader->success_code) {
        char log[512];
        glGetShaderInfoLog(shader->fragment_handle, 512, NULL, log);
        debug_error("Failed to load fragment shader: %s", log);
        glDeleteShader(shader->vertex_handle);
        glDeleteShader(shader->fragment_handle);
        return shader->success_code;
    }

    debug_info("linking program...");
    shader->handle = glCreateProgram();
    glAttachShader(shader->handle, shader->vertex_handle);
    glAttachShader(shader->handle, shader->fragment_handle);
    glLinkProgram(shader->handle);

    glGetProgramiv(shader->handle, GL_LINK_STATUS, &shader->success_code);
    if(!shader->success_code) {
        char log[512];
        glGetProgramInfoLog(shader->fragment_handle, 512, NULL, log);
        debug_error("Failed to link shader: %s", log);
        glDeleteShader(shader->vertex_handle);
        glDeleteShader(shader->fragment_handle);
        return shader->success_code;
    }

    glDeleteShader(shader->vertex_handle);
    glDeleteShader(shader->fragment_handle);
}

int use_shader_2d(Shader_2D *shader) {
    glUseProgram(shader->handle);
}

int release_shader_2d(Shader_2D *shader) {
    if (!shader->handle) return 1;
    glDeleteProgram(shader->handle);
    shader->handle = 0;
}
