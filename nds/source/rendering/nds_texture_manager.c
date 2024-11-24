#include "rendering/nds_texture_manager.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/texture.h"
#include "rendering/nds_texture.h"
#include "rendering/gfx_context.h"

static inline
PLATFORM_Texture *NDS_get_texture_by__index_from__texture_manager(
        NDS_Texture_Manager *p_NDS_texture_manager,
        Index__u32 index_of__texture) {
#ifndef NDEBUG
    if (index_of__texture
            >= MAX_QUANTITY_OF__TEXTURES) {
        debug_error("NDS_get_texture_by__index_from__texture_manager, index out of bounds: %d/%d",
                index_of__texture,
                MAX_QUANTITY_OF__TEXTURES);
        return 0;
    }
#endif
    
    return &p_NDS_texture_manager
        ->NDS_textures[index_of__texture];
}

void NDS_initialize_texture_manager(
        NDS_Texture_Manager *p_NDS_texture_manager) {
    for (Index__u32 index_of__texture = 0;
            index_of__texture < MAX_QUANTITY_OF__TEXTURES;
            index_of__texture++) {
        PLATFORM_Texture *p_PLATFORM_texture =
            NDS_get_texture_by__index_from__texture_manager(
                    p_NDS_texture_manager, 
                    index_of__texture);

        NDS_initialize_texture_as__deallocated(
                p_PLATFORM_texture);
    }
}

void PLATFORM_allocate_texture(
        PLATFORM_Texture *texture, 
        Texture_Allocation_Specification *p_texture_allocation_specification) {
    NDS_allocate_texture(
            texture,
            p_texture_allocation_specification);
    return;
    // for (Index__u32 index_of__texture = 0;
    //         index_of__texture < MAX_QUANTITY_OF__TEXTURES;
    //         index_of__texture++) {
    //     PLATFORM_Texture *p_PLATFORM_texture =
    //         NDS_get_texture_by__index_from__texture_manager(
    //                 p_NDS_texture_manager, 
    //                 index_of__texture);

    //     if (is_texture_flags__allocated(
    //                 *PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
    //                     p_PLATFORM_texture))) { 
    //         continue;
    //     }

    //     set_texture_flags_as__allocated(
    //             PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
    //                 p_PLATFORM_texture));
    // }
}

void PLATFORM_release_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Texture *texture) {
    NDS_Texture_Manager *p_NDS_texture_manager =
        NDS_get_p_texture_manager_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);
#ifndef NDEBUG
    Index__u32 index =
        texture
        - p_NDS_texture_manager
        ->NDS_textures
        ;

    if (index
            >= MAX_QUANTITY_OF__TEXTURES) {
        debug_error("NDS::PLATFORM_release_texture, p_PLATFORM_texture not allocated with this NDS_Texture_Manager.");
        return;
    }
#endif
    if(!is_texture_flags__allocated(
                *PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
                    texture))) {
        debug_error("NDS::PLATFORM_release_texture, double free.");
        return;
    }
    if (texture->oam) {
        oamClearSprite(
                texture->oam, 
                texture->oam_index);
        oamFreeGfx(texture->oam, texture->gfx);
    }
    NDS_initialize_texture_as__deallocated(
            texture);
}

void PLATFORM_release_texture_with__p_PLATFORM_sprite(PLATFORM_Sprite *p_PLATFORM_sprite) {
    PLATFORM_release_texture(
            0,
            &p_PLATFORM_sprite->sprite_texture);
}

void PLATFORM_allocate_texture__with_path(
        PLATFORM_Texture *texture,
        Texture_Allocation_Specification
            *p_texture_allocation_specification,
        const char *path) {
    // no-op
    debug_error("allocate_texture__with_path not defined on NDS.");
}

void PLATFORM_allocate_texture__with_size(
        PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height) {
    debug_error("allocate_texture__with_size not supported on NDS.");
}