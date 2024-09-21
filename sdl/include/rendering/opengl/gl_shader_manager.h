#ifndef GL_SHADER_MANAGER_H
#define GL_SHADER_MANAGER_H

#include <rendering/opengl/gl_defines.h>

extern Shader_String__Const shader_string__passthrough;
extern Shader_String__Const shader_string__sprite;

///
/// Warning do not call GL_initialize_shader_manager
/// more than once per manager. If you want to
/// call GL_initialize_shader_manager a second time
/// on the same manager, you should first call
/// GL_dispose_shader_manager. Failure to do so
/// will cause a GPU memory leak.
///
void GL_initialize_shader_manager(
        GL_Shader_Manager *p_GL_shader_manager);

///
/// p_c_str can be null.
///
GL_Shader_2D *GL_allocate_shader_with__shader_manager(
        GL_Shader_Manager *p_GL_shader_manager,
        const char* p_c_str);

GL_Shader_2D *GL_get_shader_from__shader_manager(
        GL_Shader_Manager *p_GL_shader_manager,
        const char *p_c_str);

void GL_release_shader_from__shader_manager(
        GL_Shader_Manager *p_GL_shader_manager,
        GL_Shader_2D *p_GL_shader);

void GL_dispose_shader_manager(
        GL_Shader_Manager *p_GL_shader_manager);

#endif
