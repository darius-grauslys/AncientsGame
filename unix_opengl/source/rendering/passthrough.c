#include <rendering/passthrough.h>
#include <rendering/framebuffer.h>

void passthrough__textures(
        Framebuffer *framebuffer,
        Texture *texture_source,
        Texture *texture_target,
        Shader_2D *shader,
        int32_t x, int32_t y) {
    set_framebuffer__color_attachment__with_a_texture__without_unbinding(
            framebuffer, texture_target);

    use_shader_2d(shader);
}
