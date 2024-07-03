#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "rendering/nds_sprite.h"
#include "rendering/texture.h"
#include "rendering/nds_texture.h"
#include <nds_defines.h>

void NDS_initialize_sprite_array(
        NDS_Sprite_Array *p_NDS_sprite_array) {
    for (Index__u8 index_of__sprite = 0;
            index_of__sprite
            < NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE;
            index_of__sprite++) {
        PLATFORM_Sprite *p_PLATFORM_sprite =
            &p_NDS_sprite_array
            ->sprites[index_of__sprite];
        PLATFORM_Texture *p_PLATFORM_texture =
            &p_PLATFORM_sprite
            ->sprite_texture;

        set_texture_flags_as__deallocated(
                NDS_get_p_texture_flags_from__PLATFORM_texture(
                    p_PLATFORM_texture));
        NDS_initialize_sprite(
                p_PLATFORM_sprite,
                SPRITE_FLAGS__NONE);
    }
}

PLATFORM_Sprite *get_next_p_PLATFORM_sprite_from__sprite_array(
        NDS_Sprite_Array *p_sprite_array) {
    Quantity__u32 quantity_of__allocated_sprites =
        p_sprite_array->quantity_of__sprites_allocated;
    if (NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE
            <= quantity_of__allocated_sprites) {
        debug_abort("get_next_p_PLATFORM_sprite_from__sprite_manager, no more available pointers.");
        return 0;
    }

    for (Index__u8 index_of__sprite = 0;
            index_of__sprite 
            < NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE;
            index_of__sprite++) {
        PLATFORM_Sprite *p_PLATFORM_sprite =
            &p_sprite_array->sprites[index_of__sprite];
        if (!NDS_is_sprite__allocated(p_PLATFORM_sprite))
            return p_PLATFORM_sprite;
    }
    return 0;
}

PLATFORM_Sprite *get_next_p_PLATFORM_sprite_from__sprite_manager(
        NDS_Sprite_Manager *p_NDS_sprite_manager,
        Sprite_Allocation_Specification 
            *p_sprite_allocation_specification) {
    Texture_Flags render_method_flags =
        get_texture_flags__rendering_method(
                p_sprite_allocation_specification
                ->texture_allocation_specification
                .texture_flags);

    switch (render_method_flags) {
        default:
            debug_abort("get_next_p_PLATFORM_sprite_from__sprite_manager, invalid render_method: %d", render_method_flags);
            return 0;
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_MAIN:
            return get_next_p_PLATFORM_sprite_from__sprite_array(
                    &p_NDS_sprite_manager->sprites_on__oam_main);
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_SUB:
            return get_next_p_PLATFORM_sprite_from__sprite_array(
                    &p_NDS_sprite_manager->sprites_on__oam_sub);
    }
}

void NDS_initialize_sprite_manager(
        NDS_Sprite_Manager *p_NDS_sprite_manager) {
    NDS_initialize_sprite_array(
            &p_NDS_sprite_manager->sprites_on__oam_main);
    NDS_initialize_sprite_array(
            &p_NDS_sprite_manager->sprites_on__oam_sub);
}

void NDS_initialize_sprite_for__entity(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification) {
    // drop the size flags
    Texture_Flags *p_texture_flags =
        &p_sprite_allocation_specification
        ->texture_allocation_specification
        .texture_flags;
    *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
    *p_texture_flags |= TEXTURE_FLAG__USE_OAM;
    *p_texture_flags |= TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB;

    enum Entity_Kind the_kind_of__entity =
        p_sprite_allocation_specification
        ->the_kind_of__entity_this__sprite_is;

    // while (DMA_CR(p_PLATFORM_sprite->sprite_texture.dma_channel) & DMA_BUSY);
    if (the_kind_of__entity >= Entity_Kind__Unknown) {
            debug_abort("Entity_Kind %d not implemented for PLATFORM_initialize_sprite_for__entity.",
            the_kind_of__entity);
        return;
    }

    p_PLATFORM_gfx_context
        ->F_sprite_gfx_allocator__lookup_table_for__entities[
            the_kind_of__entity]
        (p_PLATFORM_sprite, 
         p_sprite_allocation_specification);

#ifndef NDEBUG
    if (!is_texture_flags__allocated(
                p_PLATFORM_sprite
                ->sprite_texture
                .flags)) {
        debug_error("Failed to allocate sprite gfx for: %d",
                the_kind_of__entity);
        debug_warning("Did you forget to load a sprite_gfx_allocator__lookup_table?");
    }
#endif

    PLATFORM_update_sprite(p_PLATFORM_sprite);
}

void NDS_initialize_sprite_for__item(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Sprite_Allocation_Specification 
            *p_sprite_allocation_specification) {
    p_PLATFORM_gfx_context
        ->f_sprite_gfx_allocator__handler_for__items(
                p_PLATFORM_sprite,
                p_sprite_allocation_specification);

#ifndef NDEBUG
    if (!is_texture_flags__allocated(
                p_PLATFORM_sprite
                ->sprite_texture
                .flags)) {
        debug_error("Failed to allocate sprite gfx for: %d",
                p_sprite_allocation_specification
                ->the_kind_of__item_this__sprite_is);
        debug_warning("Did you forget to load a sprite_gfx_allocator__lookup_table?");
    }
#endif

    PLATFORM_update_sprite(p_PLATFORM_sprite);
}

PLATFORM_Sprite *PLATFORM_allocate_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Allocation_Specification *p_sprite_allocation_specification) {
    PLATFORM_Sprite *p_PLATFORM_sprite = 
        get_next_p_PLATFORM_sprite_from__sprite_manager(
                &p_PLATFORM_gfx_context
                ->nds_sprite_manager, 
                p_sprite_allocation_specification);
    switch (p_sprite_allocation_specification
            ->the_kind_of__sprite_allocation) {
        default:
#warning impl particles:
            //TODO: impl particles
        case Sprite_Allocation_Kind__Particle:
            debug_abort("PLATFORM_allocate_sprite, unsupported sprite allocation kind: %d", 
                    p_sprite_allocation_specification
                    ->the_kind_of__sprite_allocation);
            return 0;
        case Sprite_Allocation_Kind__Item:
            NDS_initialize_sprite_for__item(
                    p_PLATFORM_gfx_context, 
                    p_PLATFORM_sprite,
                    p_sprite_allocation_specification);
            break;
        case Sprite_Allocation_Kind__Entity:
            NDS_initialize_sprite_for__entity(
                    p_PLATFORM_gfx_context, 
                    p_PLATFORM_sprite,
                    p_sprite_allocation_specification);
            break;
    }

    NDS_set_sprite_as__allocated(p_PLATFORM_sprite);
    return p_PLATFORM_sprite;
}

void PLATFORM_release_all__sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {

}

void PLATFORM_release_all__sprites_using__this_render_method(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags_for__render_method) {

}
