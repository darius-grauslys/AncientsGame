#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "nds/arm9/sprite.h"
#include "platform.h"
#include "rendering/nds_gfx_window.h"
#include "rendering/nds_sprite.h"
#include "rendering/sprite.h"
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
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        NDS_Sprite_Manager *p_NDS_sprite_manager,
        Sprite_Allocation_Specification 
            *p_sprite_allocation_specification) {

    if (!p_sprite_allocation_specification
            ->texture_allocation_specification
            .p_PLATFORM_graphics_window) {
            debug_abort("get_next_p_PLATFORM_sprite_from__sprite_manager, p_PLATFORM_graphics_window is null.");
            return 0;
    }

    bool is_allocating_onto__oam_main_or__sub =
        &p_PLATFORM_gfx_context
        ->graphics_window__main ==
        p_sprite_allocation_specification
        ->texture_allocation_specification
        .p_PLATFORM_graphics_window
        ;

    return 
        (is_allocating_onto__oam_main_or__sub)
        ? get_next_p_PLATFORM_sprite_from__sprite_array(
                &p_NDS_sprite_manager->sprites_on__oam_main)
        : get_next_p_PLATFORM_sprite_from__sprite_array(
                &p_NDS_sprite_manager->sprites_on__oam_sub);
        ;
}

void NDS_initialize_sprite_manager(
        NDS_Sprite_Manager *p_NDS_sprite_manager) {
    NDS_initialize_sprite_array(
            &p_NDS_sprite_manager->sprites_on__oam_main);
    NDS_initialize_sprite_array(
            &p_NDS_sprite_manager->sprites_on__oam_sub);
}

PLATFORM_Sprite *PLATFORM_allocate_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Allocation_Specification *p_sprite_allocation_specification) {
    PLATFORM_Sprite *p_PLATFORM_sprite = 
        get_next_p_PLATFORM_sprite_from__sprite_manager(
                p_PLATFORM_gfx_context,
                &p_PLATFORM_gfx_context
                ->nds_sprite_manager, 
                p_sprite_allocation_specification);
    switch (p_sprite_allocation_specification
            ->the_kind_of__sprite_allocation) {
        default:
            debug_abort("PLATFORM_allocate_sprite, unsupported sprite allocation kind: %d", 
                    p_sprite_allocation_specification
                    ->the_kind_of__sprite_allocation);
            return 0;
        case Sprite_Allocation_Kind__Graphics_Pointer:
            ;
            PLATFORM_Texture *p_PLATFORM_texture =
                PLATFORM_allocate_texture(
                        p_PLATFORM_gfx_context,
                        &p_sprite_allocation_specification
                            ->texture_allocation_specification);
                
            dmaCopy(
                    p_sprite_allocation_specification
                        ->p_gfx,
                    p_PLATFORM_texture
                        ->gfx,
                    p_PLATFORM_texture->width
                    * p_PLATFORM_texture->height);
            break;
        case Sprite_Allocation_Kind__Item:
            p_PLATFORM_gfx_context
                ->f_sprite_gfx_allocator__handler_for__items(
                        p_PLATFORM_gfx_context,
                        p_PLATFORM_sprite,
                        p_sprite_allocation_specification);
            break;
        case Sprite_Allocation_Kind__UI:
            p_PLATFORM_gfx_context
                ->f_sprite_gfx_allocator__handler_for__ui(
                        p_PLATFORM_gfx_context,
                        p_PLATFORM_sprite,
                        p_sprite_allocation_specification);
            break;
        case Sprite_Allocation_Kind__Particle:
            ;
            //TODO: bounds check the enum
            enum Particle_Kind the_kind_of__particle =
                p_sprite_allocation_specification
                ->the_kind_of__particle_this__sprite_is;
            p_PLATFORM_gfx_context
                ->F_sprite_gfx_allocator__lookup_table_for__particles[
                    the_kind_of__particle](
                            p_PLATFORM_gfx_context,
                            p_PLATFORM_sprite, 
                            p_sprite_allocation_specification);
            break;
        case Sprite_Allocation_Kind__Entity:
            ;
            //TODO: bounds check the enum
            enum Entity_Kind the_kind_of__entity =
                p_sprite_allocation_specification
                ->the_kind_of__entity_this__sprite_is;
            p_PLATFORM_gfx_context
                ->F_sprite_gfx_allocator__lookup_table_for__entities[
                    the_kind_of__entity](
                            p_PLATFORM_gfx_context,
                            p_PLATFORM_sprite, 
                            p_sprite_allocation_specification);
            break;
    }

#ifndef NDEBUG
    if (!NDS_is_sprite_texture__allocated(
                p_PLATFORM_sprite)) {
        switch (p_sprite_allocation_specification
                ->the_kind_of__sprite_allocation) {
            default:
                debug_error("PLATFORM_allocate_sprite, failed to allocate gfx for None, or %d", 
                        p_sprite_allocation_specification
                        ->the_kind_of__sprite_allocation);
                return 0;
            case Sprite_Allocation_Kind__Graphics_Pointer:
                debug_error("PLATFORM_allocate_sprite, failed to allocate ptr gfx: %p", 
                        p_sprite_allocation_specification
                        ->p_gfx);
                break;
            case Sprite_Allocation_Kind__Item:
                debug_error("PLATFORM_allocate_sprite, failed to allocate item gfx: %d", 
                        p_sprite_allocation_specification
                        ->the_kind_of__item_this__sprite_is);
                break;
            case Sprite_Allocation_Kind__UI:
                debug_error("PLATFORM_allocate_sprite, failed to allocate ui gfx: %d", 
                        p_sprite_allocation_specification
                        ->the_kind_of__ui__this_sprite_is);
                break;
            case Sprite_Allocation_Kind__Particle:
                debug_error("PLATFORM_allocate_sprite, failedt to allocate particle gfx: %d", 
                        p_sprite_allocation_specification
                        ->the_kind_of__particle_this__sprite_is);
                break;
            case Sprite_Allocation_Kind__Entity:
                debug_error("PLATFORM_allocate_sprite, failed to allocate entity gfx: %d", 
                        p_sprite_allocation_specification
                        ->the_kind_of__entity_this__sprite_is);
                break;
        }
        debug_warning("Did you forget to load a sprite_gfx_allocator__lookup_table?");
        return 0;
    }
#endif

    NDS_set_priority_of__PLATFORM_sprite(
            p_PLATFORM_sprite, 
            NDS_get_background_priortiy_of__PLATFORM_gfx_window(
                p_sprite_allocation_specification
                ->texture_allocation_specification
                .p_PLATFORM_graphics_window));

    PLATFORM_update_sprite(p_PLATFORM_sprite);

    NDS_set_sprite_as__allocated(p_PLATFORM_sprite);
    return p_PLATFORM_sprite;
}

void PLATFORM_release_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context, 
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    PLATFORM_release_texture(
            p_PLATFORM_gfx_context,
            NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite));
    set_sprite_flags_as__deallocated(
            NDS_get_p_sprite_flags_of__PLATFORM_sprite(
                p_PLATFORM_sprite));
}

void PLATFORM_release_all__sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    PLATFORM_release_all__sprites_using__this_graphics_window(
            p_PLATFORM_gfx_context,
            &p_PLATFORM_gfx_context->graphics_window__main);
    PLATFORM_release_all__sprites_using__this_graphics_window(
            p_PLATFORM_gfx_context,
            &p_PLATFORM_gfx_context->graphics_window__sub);
}

void PLATFORM_release_all__sprites_using__this_graphics_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
    NDS_Sprite_Array *p_NDS_sprite_array =
        (p_PLATFORM_graphics_window ==
         &p_PLATFORM_gfx_context->graphics_window__main)
        ? &p_PLATFORM_gfx_context
            ->nds_sprite_manager
            .sprites_on__oam_main
        : &p_PLATFORM_gfx_context
            ->nds_sprite_manager
            .sprites_on__oam_sub
        ;

    for (Index__u8 index_of__sprite = 0;
            index_of__sprite <
            NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE;
            index_of__sprite++) {
        PLATFORM_Sprite *p_PLATFORM_sprite =
            &p_NDS_sprite_array->sprites[index_of__sprite];
        if (!is_sprite_flags__allocated(
                    p_PLATFORM_sprite->sprite_flags))
            continue;

        PLATFORM_release_sprite(
                p_PLATFORM_gfx_context, 
                p_PLATFORM_sprite);
    }
}
