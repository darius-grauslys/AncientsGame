#ifndef NDS_SPRITE_MANAGER_H
#define NDS_SPRITE_MANAGER_H

#include "debug/debug.h"
#include "defines_weak.h"
#include <nds_defines.h>

///
/// WARNING! You should call this only once. If you have
/// to call it again for whatever reason, be sure to
/// invoke PLATFORM_release_all__sprites(...)
/// prior to re-initializing, or you will leak memory.
///
void NDS_initialize_sprite_manager(
        NDS_Sprite_Manager *p_NDS_sprite_manager);

static inline
PLATFORM_Sprite *NDS_get_p_sprite_with__index_from__sprite_array(
        NDS_Sprite_Array *p_NDS_sprite_array,
        Index__u8 index_of__sprite) {
#ifndef NDEBUG
    if (index_of__sprite > NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE) {
        debug_abort("NDS_get_p_sprite_with__index_from__sprite_array, index out of bounds: %d", index_of__sprite);
        return 0;
    }
#endif
    return &p_NDS_sprite_array->sprites[index_of__sprite];
}

static inline
Quantity__u32 NDS_get_quantity_of__allocated_sprites_on__oam_main(
        NDS_Sprite_Manager *p_NDS_sprite_manager) {
    return p_NDS_sprite_manager
        ->sprites_on__oam_main
        .quantity_of__sprites_allocated;
}

static inline
Quantity__u32 NDS_get_quantity_of__allocated_sprites_on__oam_sub(
        NDS_Sprite_Manager *p_NDS_sprite_manager) {
    return p_NDS_sprite_manager
        ->sprites_on__oam_sub
        .quantity_of__sprites_allocated;
}

static inline
Quantity__u32 NDS_get_quantity_of__allocated_sprites(
        NDS_Sprite_Manager *p_NDS_sprite_manager) {
    return p_NDS_sprite_manager
            ->sprites_on__oam_main
            .quantity_of__sprites_allocated
        + p_NDS_sprite_manager
            ->sprites_on__oam_sub
            .quantity_of__sprites_allocated
        ;
}

static inline
Quantity__u32 NDS_get_quantity_of__available_sprite_allocations_on__oam_main(
        NDS_Sprite_Manager *p_NDS_sprite_manager) {
    return 
        NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE
        - p_NDS_sprite_manager
            ->sprites_on__oam_main
            .quantity_of__sprites_allocated;
}

static inline
Quantity__u32 NDS_get_quantity_of__available_sprite_allocations_on__oam_sub(
        NDS_Sprite_Manager *p_NDS_sprite_manager) {
    return 
        NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE
        - p_NDS_sprite_manager
            ->sprites_on__oam_sub
            .quantity_of__sprites_allocated;
}

#endif
