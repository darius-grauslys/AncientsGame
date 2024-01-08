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

    glGenTextures(1, &texture->handle);
    glBindTexture(GL_TEXTURE_2D, texture->handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void init_texture__with_size(Texture *texture,
        uint32_t width, uint32_t height) {
    glGenTextures(1, &texture->handle);
    texture->width = width;
    texture->height = height;
    texture->channel_count = 0;

    glBindTexture(GL_TEXTURE_2D, texture->handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D (
        GL_TEXTURE_2D, 
        0, 
        GL_RGB, 
        width, 
        height, 
        0, 
        GL_RGB, 
        GL_UNSIGNED_BYTE,
        NULL
    );
}

void init_texture__with_path(Texture *texture, 
        const char *path) {
    glGenTextures(1, &texture->handle);
    texture->channel_count = 0;

    glBindTexture(GL_TEXTURE_2D, texture->handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(
            path, 
            &texture->width, &texture->height, 
            &texture->channel_count, 0);

    if (bytes) {
        glTexImage2D (
            GL_TEXTURE_2D, 
            0, 
            GL_RGB, 
            texture->width, 
            texture->height, 
            0, 
            GL_RGB, 
            GL_UNSIGNED_BYTE,
            bytes
        );
        stbi_image_free(bytes);
    } else {
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

void use_texture(Texture *texture) {
    if (!texture->handle) {
        debug_error("Cannot use uninitalized texture.");
        return;
    }
    glBindTexture(GL_TEXTURE_2D, texture->handle);
}
