#include "world/container.h"
#include "defines.h"
#include "defines_weak.h"

Identifier__u32 get_container__uuid(
        Tile_Vector__3i32 tile_vector__3i32) {
    Identifier__u32 uuid = 0;
    uuid |= 
        (tile_vector__3i32
        .x__i32 & MASK((
            INVENTORY_IDENTIFIER_BITS >> 1) + 1))
        << (ITEM_STACK_IDENTIFIER_BITS
                + (INVENTORY_IDENTIFIER_BITS
                    >> 1))
        ;
    uuid |= 
        (tile_vector__3i32
        .y__i32 & MASK((
            INVENTORY_IDENTIFIER_BITS >> 1) + 1))
        << (ITEM_STACK_IDENTIFIER_BITS)
        ;
    return uuid;
}
