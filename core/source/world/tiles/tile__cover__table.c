#include "defines_weak.h"
#include "entity/entity_manager.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "platform.h"
#include "serialization/serialized_field.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
#include "world/tile_logic_manager.h"
#include "world/tile_logic_record.h"
#include "world/world.h"
#include <world/tiles/tile__cover__table.h>

static inline
void set_tile_cover_as__table__horizontal(
        Tile *p_tile,
        Tile_Cover_Kind the_kind_of__table,
        Table_Part_Kind the_kind_of__table_part) {
    switch (the_kind_of__table_part) {
        default:
            return;
        case Table_Part_Kind__Left_Or_Top:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Table__Bottom__Left;
            break;
        case Table_Part_Kind__Middle:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Table__Bottom__Middle;
            break;
        case Table_Part_Kind__Right_Or_Bottom:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Table__Bottom__Right;
            break;
    }

    set_tile__is_unpassable(
            p_tile, 
            true);
}

void set_tile_cover_as__table(
        Tile *p_tile,
        Tile_Cover_Kind the_kind_of__table,
        Table_Part_Kind the_kind_of__table_part,
        bool is_horizontal_or__vertical) {
     if (is_horizontal_or__vertical) {
        set_tile_cover_as__table__horizontal(
                p_tile, 
                the_kind_of__table, 
                the_kind_of__table_part);
     }

     // TODO: impl vertical
}

void f_tile_interact_handler__table(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity) {
    // TODO: game action, table interact
    Identifier__u32 uuid =
        get_uuid_for__container(
                tile_vector__3i32);

    initialize_serialized_field_as__unlinked(
            &p_entity->s_humanoid__container_ptr,
            uuid);

    if (!resolve_s_inventory(
                p_game, 
                &p_entity->s_humanoid__container_ptr)) {
        return;
    }

    /// TODO: many things lol, invoke_...(...) for this action type primarily.
    Game_Action game_action_for__station;
    game_action_for__station.the_kind_of_game_action__this_action_is
        = Game_Action_Kind__Inventory__Container__Open;
    game_action_for__station.game_action__container__tile_vector_3i32 =
        tile_vector__3i32;
    initialize_serialized_field_as__unlinked(
            &game_action_for__station
            .s_game_action__inventory__entity_source,
            p_entity->_serialization_header.uuid);

    resolve_p_serialized_entity_ptr_with__entity_manager(
            get_p_entity_manager_from__game(p_game), 
            &game_action_for__station
            .s_game_action__inventory__entity_source);

    PLATFORM_open_ui(
            p_game, 
            UI_Window_Kind__Station,
            &game_action_for__station);
}

bool f_tile_handler__place__table(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {
    // TODO: impl vertical
    Tile *p_tile__left, *p_tile__right;

    Chunk_Manager *p_chunk_manager =
        get_p_chunk_manager_from__game(p_game);

    p_tile__left =
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                p_chunk_manager, 
                add_vectors__3i32(
                    tile_vector__3i32, 
                    VECTOR__3i32__n1_0_0));
    p_tile__right =
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                p_chunk_manager, 
                add_vectors__3i32(
                    tile_vector__3i32, 
                    VECTOR__3i32__1_0_0));

    if (!p_tile__left || !p_tile__right)
        return false;

    if (!is_tile_with__this_kind_of__tile_cover(
                p_tile__left, Tile_Cover_Kind__None)) {
        return false;
    }

    Identifier__u32 uuid =
        get_uuid_for__container(
                tile_vector__3i32);

    if (!allocate_p_inventory_using__this_uuid_in__inventory_manager(
                get_p_inventory_manager_from__game(p_game), 
                uuid)) {
        return false;
    }

    set_tile_cover_as__table__horizontal(
            p_tile__left, 
            Tile_Cover_Kind__Table__Bottom__Left, 
            Table_Part_Kind__Left_Or_Top);

    set_tile_cover_as__table__horizontal(
            p_tile, 
            Tile_Cover_Kind__Table__Bottom__Left, 
            Table_Part_Kind__Middle);

    set_tile_cover_as__table__horizontal(
            p_tile__right, 
            Tile_Cover_Kind__Table__Bottom__Left, 
            Table_Part_Kind__Right_Or_Bottom);

    return true;
}

void register_tile_handlers_for__table(
        Tile_Logic_Manager *p_tile_logic_manager) {
    register_tile_logic_record_for__cover_kind(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Table__Bottom__Middle, 
            TILE_LOGIC_RECORD(
                f_tile_interact_handler__table,
                0,
                f_tile_handler__place__table));
}
