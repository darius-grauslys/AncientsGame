#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "platform.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
#include "world/tile_logic_manager.h"
#include "world/tile_logic_record.h"
#include <world/tiles/tile__cover__chest.h>
#include <serialization/serialized_field.h>

bool set_tile_cover_as__chest(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32) {
    switch (get_tile_cover_kind_from__tile(p_tile)) {
        default:
            break;
        case Tile_Cover_Kind__Chest__Left:
        case Tile_Cover_Kind__Chest__Right:
        case Tile_Cover_Kind__Chest__Left__Locked:
        case Tile_Cover_Kind__Chest__Right__Locked:
        case Tile_Cover_Kind__Chest__Single:
        case Tile_Cover_Kind__Chest__Single__Locked:
            return false;
    }

    Inventory *p_inventory =
        allocate_p_inventory_using__this_uuid_in__inventory_manager(
                get_p_inventory_manager_from__game(p_game),
                get_uuid_for__container(
                    tile_vector__3i32));

    if (!p_inventory) {
        return false;
    }

    // TODO: merge adjacent chests into double.
    set_tile_cover_kind_of__tile(
            p_tile, 
            Tile_Cover_Kind__Chest__Single);
    set_tile__is_unpassable(
            p_tile, 
            true);

    return true;
}

void f_tile_interact_handler__chest(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity) {
    if (!is_entity_of__this_kind(
                p_entity, 
                Entity_Kind__Player)) {
        return;
    }

    // TODO: make a game_action to open the inventory.
    // TODO: that game_action should dispatch a process
    //       which awaits for a inventory UUID resolution.
    // TODO: when the player closes the inventory
    //       it should be closed with a game_action.
    //       This is because we want to dispose the inventory
    //       from the inventory_manager in multiplayer settings.

    // TODO: base on above TODO's, the code below should be removed eventually.
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

    if (!p_inventory) {
        return;
    }

    initialize_serialized_field(
            &p_entity
            ->s_humanoid__container_ptr, 
            p_inventory, 
            uuid);

    PLATFORM_open_ui(
            p_game, 
            UI_Window_Kind__Trade,
            0);
}

bool f_tile_handler__place__chest(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {

    Identifier__u32 uuid =
        get_uuid_for__container(
                tile_vector__3i32);

    Inventory *p_inventory =
        allocate_p_inventory_using__this_uuid_in__inventory_manager(
                get_p_inventory_manager_from__game(p_game), 
                uuid);

    if (!p_inventory)
        return false;

    // TODO: double chests
    set_tile_cover_kind_of__tile(
            p_tile, 
            Tile_Cover_Kind__Chest__Single);

    update_chunk_at__tile_vector__3i32(
            p_game, 
            tile_vector__3i32);

    return true;
}

void register_default_tile_handlers_for__chest(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__chest,
        Quantity__u32 quantity_of__chests) {
    register_tile_logic_record_for__cover_kind(
            p_tile_logic_manager, 
            the_kind_of__chest, 
            TILE_LOGIC_RECORD(
                f_tile_interact_handler__chest,
                0,
                f_tile_handler__place__chest,
                f_tile_handler__destroy__chest,
                TILE_LOGIC_FLAG__IS_UNPASSABLE,
                Tool_Kind__Hatchet,
                Item_Kind__Chest,
                quantity_of__chests));
}

void register_tile_handlers_for__chest(
        Tile_Logic_Manager *p_tile_logic_manager) {
    register_default_tile_handlers_for__chest(
            p_tile_logic_manager,
            Tile_Cover_Kind__Chest__Single,
            1);
    register_default_tile_handlers_for__chest(
            p_tile_logic_manager,
            Tile_Cover_Kind__Chest__Left,
            2);
    register_default_tile_handlers_for__chest(
            p_tile_logic_manager,
            Tile_Cover_Kind__Chest__Right,
            2);
}

bool f_tile_handler__destroy__chest(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {
    switch (the_kind_of__tile_cover) {
        default:
            return false;
        case Tile_Cover_Kind__Chest__Left:
        case Tile_Cover_Kind__Chest__Right:
        case Tile_Cover_Kind__Chest__Single:
            break;
    }

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

    if (p_inventory
            && !is_inventory__empty(p_inventory)) {
        return false;
    }

    Tile *p_tile__left;
    Tile *p_tile__right;

    switch (the_kind_of__tile_cover) {
        default:
            return false;
        case Tile_Cover_Kind__Chest__Left:
            p_tile__left = p_tile;
            p_tile__right = get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                    get_p_chunk_manager_from__game(p_game), 
                    add_vectors__3i32(
                        tile_vector__3i32,
                        VECTOR__3i32__1_0_0));
            break;
        case Tile_Cover_Kind__Chest__Right:
            p_tile__right = p_tile;
            p_tile__left = get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                    get_p_chunk_manager_from__game(p_game), 
                    add_vectors__3i32(
                        tile_vector__3i32,
                        VECTOR__3i32__n1_0_0));
            break;
        case Tile_Cover_Kind__Chest__Single:
            clear_tile_cover(
                    p_tile);
            goto release_inventory;
    }

    if (!p_tile__left || !p_tile__right) {
        return false;
    }

    clear_tile_cover(p_tile__left);
    clear_tile_cover(p_tile__right);

release_inventory:
    if (p_inventory) {
        release_p_inventory_in__inventory_manager(
                get_p_inventory_manager_from__game(p_game), 
                p_inventory);
    }
    return true;
}
