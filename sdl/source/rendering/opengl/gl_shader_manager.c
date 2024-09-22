#include "debug/debug.h"
#include "defines_weak.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/gl_shader_sprite.h"
#include <rendering/opengl/gl_shader_manager.h>
#include <stdio.h>
#include <string.h>

Shader_String__Const shader_string__passthrough = "shader__passthrough";
Shader_String__Const shader_string__sprite = "shader__sprite";

void GL_initialize_shader_manager(
        GL_Shader_Manager *p_GL_shader_manager) {
    for (Index__u16 index_of__shader = 0;
            index_of__shader < MAX_QUANTITY_OF__SHADERS;
            index_of__shader++) {
        initialize_shader_2d_as__deallocated(
                &p_GL_shader_manager
                ->GL_shaders[index_of__shader]);
    }

    GL_Shader_2D *p_shader__passthrough = 
        GL_allocate_shader_with__shader_manager(
            p_GL_shader_manager, 
            shader_string__passthrough);

    GL_Shader_2D *p_shader__sprite = 
        GL_allocate_shader_with__shader_manager(
            p_GL_shader_manager, 
            shader_string__sprite);

    initialize_shader_2d_as__shader_passthrough(
            p_shader__passthrough);
    initialize_shader_2d_as__shader_sprite(
            p_shader__sprite);

    p_GL_shader_manager
        ->p_GL_shader__sprite =
        p_shader__sprite;

    //TODO: 
    // p_GL_shader_manager
    //     ->p_GL_shader__world =
    //     p_shader__world;
}

GL_Shader_2D *GL_allocate_shader_with__shader_manager(
        GL_Shader_Manager *p_GL_shader_manager,
        const char *p_c_str) {
    for (Index__u16 index_of__shader = 0;
            index_of__shader < MAX_QUANTITY_OF__SHADERS;
            index_of__shader++) {
        GL_Shader_2D *p_shader =
            &p_GL_shader_manager->GL_shaders[
            index_of__shader];
        if (GL_is_shader__allocated(p_shader))
            continue;
        
        GL_set_shader_as__allocated(
                p_shader);

        memset(
                p_shader->GL_shader_string, 
                0, 
                MAX_LENGTH_OF__SHADER_STRING);
        if (p_c_str) {
            memcpy(
                    p_shader->GL_shader_string, 
                    p_c_str,
                    MAX_LENGTH_OF__SHADER_STRING);
        } else {
            snprintf(p_shader->GL_shader_string,
                    MAX_LENGTH_OF__SHADER_STRING,
                    "shader__%16x",
                    (u32)(uint64_t)p_shader);
        }

        return p_shader;
    }
    return 0;
}

GL_Shader_2D *GL_get_shader_from__shader_manager(
        GL_Shader_Manager *p_GL_shader_manager,
        const char *p_c_str) {
    for (Index__u16 index_of__shader = 0;
            index_of__shader < MAX_QUANTITY_OF__SHADERS;
            index_of__shader++) {
        GL_Shader_2D *p_shader =
            &p_GL_shader_manager->GL_shaders[
            index_of__shader];
        if (!GL_is_shader__allocated(p_shader))
            continue;

        if (strncmp(
                    p_shader->GL_shader_string, 
                    p_c_str, 
                    MAX_LENGTH_OF__SHADER_STRING) != 0) {
            continue;
        }

        return p_shader;
    }

    return 0;
}

void GL_release_shader_from__shader_manager(
        GL_Shader_Manager *p_GL_shader_manager,
        GL_Shader_2D *p_GL_shader) {
    i8 index = p_GL_shader
            - p_GL_shader_manager->GL_shaders;

    if (index < 0 || index >= MAX_QUANTITY_OF__SHADERS) {
        debug_abort("SDL::GL_release_shader_from__shader_manager, p_GL_shader is not allocated with this manager, or is invalid.");
        debug_warning("This might cause a GPU memory leak!");
        return;
    }

    if (p_GL_shader
            == p_GL_shader_manager
            ->p_GL_shader__sprite) {
        debug_warning__verbose("SDL::GL::GL_release_shader_from__shader_manager, p_GL_shader__sprite is released.");
        p_GL_shader_manager
            ->p_GL_shader__sprite = 0;
        debug_abort("SDL::GL::GL_release_shader_from__shader_manager, TODO: impl p_GL_shader__sprite reattachment.");
    }

    if (p_GL_shader
            == p_GL_shader_manager
            ->p_GL_shader__world) {
        debug_warning__verbose("SDL::GL::GL_release_shader_from__shader_manager, p_GL_shader__world is released.");
        p_GL_shader_manager
            ->p_GL_shader__world = 0;
        debug_abort("SDL::GL::GL_release_shader_from__shader_manager, TODO: impl p_GL_shader__world reattachment.");
    }

    release_shader_2d(p_GL_shader);
    GL_set_shader_as__deallocated(
            p_GL_shader);
}

void GL_dispose_shader_manager(
        GL_Shader_Manager *p_GL_shader_manager) {
    for (Index__u16 index_of__shader = 0;
            index_of__shader < MAX_QUANTITY_OF__SHADERS;
            index_of__shader++) {
        GL_Shader_2D *p_shader =
            &p_GL_shader_manager->GL_shaders[
            index_of__shader];
        if (!GL_is_shader__allocated(p_shader))
            continue;

        release_shader_2d(p_shader);
        GL_set_shader_as__deallocated(
                p_shader);
    }

    p_GL_shader_manager
        ->p_GL_shader__sprite = 0;
    p_GL_shader_manager
        ->p_GL_shader__world = 0;
}
