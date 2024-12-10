#include "inventory/container.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "serialization/serialized_field.h"

Inventory *get_inventory_of__container(
        Game *p_game,
        Tile_Vector__3i32 tile_vector__3i32) {
    Identifier__u32 uuid = 
        get_uuid_for__container(tile_vector__3i32);
    Serialized_Field s_inventory_ptr;
    initialize_serialized_field_as__unlinked(
            &s_inventory_ptr, 
            uuid);

    Inventory *p_inventory =
        resolve_s_inventory(
                p_game, 
                &s_inventory_ptr);

    return p_inventory;
}
