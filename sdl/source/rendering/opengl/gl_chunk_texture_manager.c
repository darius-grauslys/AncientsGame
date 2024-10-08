#include "defines_weak.h"
#include "platform.h"
#include "rendering/opengl/gl_chunk_texture.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_framebuffer_manager.h"
#include "rendering/opengl/gl_shader_manager.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_texture_manager.h"
#include "rendering/sdl_texture_strings.h"
#include <rendering/opengl/gl_chunk_texture_manager.h>

static inline
GL_Chunk_Texture *GL_get_p_chunk_texture_from__chunk_texture_manager(
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        int index_of__chunk_texture) {
    return &p_GL_chunk_texture_manager
        ->GL_chunk_textures[index_of__chunk_texture];
}

void GL_initialize_chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager) {

    p_GL_chunk_texture_manager
        ->p_PLATFORM_texture_of__tilesheet_cover = 0;
    p_GL_chunk_texture_manager
        ->p_PLATFORM_texture_of__tilesheet_ground = 0;
    p_GL_chunk_texture_manager
        ->p_GL_chunk_shader = 0;
    p_GL_chunk_texture_manager
        ->p_GL_framebuffer__chunk_rendering = 0;

    GL_Shader_2D *p_GL_shader_for__chunk_texture_manager = 
        GL_get_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                shader_string__passthrough);

    if (!p_GL_shader_for__chunk_texture_manager) {
        debug_warning("Did you forget to initialize the GL_Shader_Manager first?");
        debug_abort("SDL::GL::GL_initialize_chunk_texture_manager, failed to find passthrough shader.");
        return;
    }

    GL_Framebuffer *p_GL_framebuffer =
        GL_allocate_framebuffer_with__framebuffer_manager(
                GL_get_p_framebuffer_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context));
    
    if (!p_GL_framebuffer) {
        GL_release_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                p_GL_shader_for__chunk_texture_manager);

        debug_error("SDL::GL::GL_initialize_chunk_texture_manager, failed to allocate framebuffer for GL_Chunk_Manager.");
        return;
    }

    PLATFORM_Texture *p_PLATFORM_texture_of__tilesheet_cover;
    PLATFORM_Texture *p_PLATFORM_texture_of__tilesheet_ground;

    p_PLATFORM_texture_of__tilesheet_cover =
        SDL_get_texture_from__texture_manager(
                SDL_get_p_texture_manager_from__gfx_context(
                    p_PLATFORM_gfx_context), 
                SDL_texture_string__tilesheet_cover);

    if (!p_PLATFORM_texture_of__tilesheet_cover) {
        GL_release_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                p_GL_shader_for__chunk_texture_manager);
        GL_release_framebuffer_from__framebuffer_manager(
                p_PLATFORM_gfx_context, 
                GL_get_p_framebuffer_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                p_GL_framebuffer);
        debug_abort("SDL::GL::GL_initialize_chunk_texture_manager, failed to acquire p_PLATFORM_texture_of__tilesheet_cover");
        return;
    }

    p_PLATFORM_texture_of__tilesheet_ground =
        SDL_get_texture_from__texture_manager(
                SDL_get_p_texture_manager_from__gfx_context(
                    p_PLATFORM_gfx_context), 
                SDL_texture_string__tilesheet_ground);

    if (!p_PLATFORM_texture_of__tilesheet_ground) {
        GL_release_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                p_GL_shader_for__chunk_texture_manager);
        GL_release_framebuffer_from__framebuffer_manager(
                p_PLATFORM_gfx_context, 
                GL_get_p_framebuffer_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                p_GL_framebuffer);
        debug_abort("SDL::GL::GL_initialize_chunk_texture_manager, failed to acquire p_PLATFORM_texture_of__tilesheet_ground");
        return;
    }

    p_GL_chunk_texture_manager->p_PLATFORM_texture_of__tilesheet_cover =
        p_PLATFORM_texture_of__tilesheet_cover;
    p_GL_chunk_texture_manager->p_PLATFORM_texture_of__tilesheet_ground =
        p_PLATFORM_texture_of__tilesheet_ground;
    
    p_GL_chunk_texture_manager
        ->p_GL_framebuffer__chunk_rendering =
        p_GL_framebuffer;

    p_GL_chunk_texture_manager
        ->p_GL_chunk_shader =
        p_GL_shader_for__chunk_texture_manager;

    for (Index__u16 index_of__chunk_texture_record = 0;
            index_of__chunk_texture_record < MAX_QUANTITY_OF__CHUNK_TEXTURES;
            index_of__chunk_texture_record++) {
        GL_Chunk_Texture *p_GL_chunk_texture =
            GL_get_p_chunk_texture_from__chunk_texture_manager(
                    p_GL_chunk_texture_manager, 
                    index_of__chunk_texture_record);

        GL_initialize_chunk_texture_as__deallocated(
                p_GL_chunk_texture);
    }
}

GL_Chunk_Texture *_GL_dehash_chunk_to__chunk_texture(
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        const Chunk *p_chunk__hash,
        const Chunk *p_chunk__key) {
    int index = ((u32)(long)p_chunk__hash) % MAX_QUANTITY_OF__CHUNK_TEXTURES;
    int index__resolved = index;
    GL_Chunk_Texture *p_GL_chunk_texture = 0;
    do {
        GL_Chunk_Texture *p_GL_chunk_texture__check =
            GL_get_p_chunk_texture_from__chunk_texture_manager(
                    p_GL_chunk_texture_manager, 
                    index__resolved++);
        if (p_GL_chunk_texture__check->p_chunk_owner
                == p_chunk__key) {
            p_GL_chunk_texture =
                p_GL_chunk_texture__check;
            break;
        }
        index__resolved %= MAX_QUANTITY_OF__CHUNK_TEXTURES;
    } while (index__resolved != index);
    return p_GL_chunk_texture;
}

GL_Chunk_Texture *GL_dehash_chunk_to__chunk_texture(
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        const Chunk *p_chunk) {
    return _GL_dehash_chunk_to__chunk_texture(
            p_GL_chunk_texture_manager, 
            p_chunk, 
            p_chunk);
}

void GL_allocate_chunk_texture_with__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        Chunk *p_chunk) {
    GL_Chunk_Texture *p_GL_chunk_texture =
        _GL_dehash_chunk_to__chunk_texture(
                p_GL_chunk_texture_manager,
                p_chunk,
                0);
    if (!p_GL_chunk_texture) {
        debug_error("SDL::GL::GL_allocate_chunk_texture_with__chunk_texture_manager, failed to find available GL_Chunk_Texture.");
        return;
    }
    p_GL_chunk_texture->p_chunk_owner = p_chunk;
    GL_allocate_chunk_texture__texture_data(
            p_PLATFORM_gfx_context, 
            p_GL_chunk_texture);

    // TODO: error check.
}

void GL_allocate_chunk_textures_for__chunk_manager_with__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        Chunk_Manager *p_chunk_manager) {
    for (Index__u16 index_of__chunk = 0;
            index_of__chunk < sizeof(p_chunk_manager->chunks)
            / sizeof(Chunk);
            index_of__chunk++) {
        Chunk *p_chunk =
            &p_chunk_manager->chunks[index_of__chunk];
        GL_allocate_chunk_texture_with__chunk_texture_manager(
                p_PLATFORM_gfx_context, 
                p_GL_chunk_texture_manager, 
                p_chunk);
    }
}

void GL_deallocate_all_chunk_textures_from__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager) {
    for (Index__u16 index_of__chunk_texture_record = 0;
            index_of__chunk_texture_record < MAX_QUANTITY_OF__CHUNK_TEXTURES;
            index_of__chunk_texture_record++) {
        GL_Chunk_Texture *p_GL_chunk_texture =
            GL_get_p_chunk_texture_from__chunk_texture_manager(
                    p_GL_chunk_texture_manager, 
                    index_of__chunk_texture_record);

        GL_deallocate_chunk_texture__texture_data(
                p_PLATFORM_gfx_context, 
                p_GL_chunk_texture);
        GL_initialize_chunk_texture_as__deallocated(
                p_GL_chunk_texture);
    }
}

void GL_deallocate_chunk_textures_for__chunk_manager_from__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        Chunk_Manager *p_chunk_manager) {
    for (Index__u16 index_of__chunk = 0;
            index_of__chunk < sizeof(p_chunk_manager->chunks)
            / sizeof(Chunk);
            index_of__chunk++) {
        Chunk *p_chunk =
            &p_chunk_manager->chunks[index_of__chunk];
        GL_deallocate_chunk_texture_from__chunk_texture_manager(
                p_PLATFORM_gfx_context, 
                p_GL_chunk_texture_manager, 
                p_chunk);
    }
}

void GL_deallocate_chunk_texture_from__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        Chunk *p_chunk) {
    GL_Chunk_Texture *p_GL_chunk_texture =
        _GL_dehash_chunk_to__chunk_texture(
                p_GL_chunk_texture_manager, 
                p_chunk, 
                p_chunk);

    if (!p_GL_chunk_texture) {
        debug_warning("Did you forget to create a chunk_texture for this chunk?");
        debug_error("SDL::GL::GL_deallocate_chunk_texture_from__chunk_texture_manager, failed to find p_GL_chunk_texture for given p_chunk.");
        return;
    }

    GL_deallocate_chunk_texture__texture_data(
            p_PLATFORM_gfx_context, 
            p_GL_chunk_texture);
    GL_initialize_chunk_texture_as__deallocated(
            p_GL_chunk_texture);
}
