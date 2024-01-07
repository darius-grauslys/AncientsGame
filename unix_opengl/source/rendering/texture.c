#include <rendering/texture.h>
#include <GL/gl.h>
#include <rendering/stb_image.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <debug/debug.h>

void init_texture(Texture *texture) {
    texture->handle = 0;
    texture->width = 0;
    texture->height = 0;
    texture->channel_count = 0;
}

void init_texture__with_path(Texture *texture, 
        const char *path) {
    if (!texture->handle) {
        glGenTextures(1, &texture->handle);
    }
    glBindTexture(GL_TEXTURE_2D, texture->handle);
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(
            path, &width, &height, &channels, 0);

    if (bytes)
    {
        glTexImage2D
        (
            GL_TEXTURE_2D, 
            0, 
            GL_RGB, 
            width, 
            height, 
            0, 
            GL_RGB, 
            GL_UNSIGNED_BYTE,
            bytes
        );
    }
    else
    {
        debug_error("failed to load image: %s", path);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void release_texture(Texture *texture) {
    if (!texture->handle) {
        debug_warning("released texture without handle.");
        return;
    }

    glDeleteTextures(1, &texture->handle);
}
