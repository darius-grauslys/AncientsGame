#include <debug/opengl/gl_debug.h>
#include <rendering/opengl/gl_defines.h>

void GLAPIENTRY
GL_debug_callback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    switch (type) {
        default:
            debug_warning("GL::debug_callback - %s",
                    message);
            break;
        case GL_DEBUG_TYPE_ERROR:
            debug_warning("GL::debug_callback - %s",
                    message);
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            debug_warning("GL::debug_callback - %s",
                    message);
            break;
    }
}

void GL_debug_init(void) {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GL_debug_callback, 0);
}
