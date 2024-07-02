#include "debug/debug.h"
#include "defines_weak.h"
#include <rendering/sprite.h>
#include <defines.h>

void initialize_sprite_gfx_allocator__lookup_table_for__entities(
        F_Sprite_Gfx_Allocator__Lookup_Table_For__Entities 
            sprite_gfx_allocator__lookup_table) {
    for (Index__u32 index_of__entity_type = 0;
            index_of__entity_type
            < (Index__u32)Entity_Kind__Unknown;
            index_of__entity_type++) {
        debug_info("~hit");
        sprite_gfx_allocator__lookup_table[index_of__entity_type] =
            f_sprite_gfx_allocator__handler__default;
    }
}

void initialize_sprite_gfx_allocator__lookup_table_for__particles(
        F_Sprite_Gfx_Allocator__Lookup_Table_For__Particles
            sprite_gfx_allocator__lookup_table) {
#warning need to impl for particle enum:
    for (Index__u32 index_of__entity_type = 0;
            index_of__entity_type
            < (Index__u32)Entity_Kind__Unknown;
            index_of__entity_type++) {
        sprite_gfx_allocator__lookup_table[index_of__entity_type] =
            f_sprite_gfx_allocator__handler__default;
    }
}

void f_sprite_gfx_allocator__handler__default(
        PLATFORM_Sprite *p_PLATFORM_sprite, 
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification) {
    debug_warning("sprite allocator not implemented.");
}
