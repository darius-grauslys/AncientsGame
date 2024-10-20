#include "defines_weak.h"
#include "world/tile.h"
#include "world/tiles/tile__cover__chest.h"
#include "world/tiles/tile__cover__door.h"
#include "world/tiles/tile__cover__table.h"
#include <world/tile_logic_manager.h>

void initialize_tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager) {
    for (Index__u32 index_of__tile = 0;
            index_of__tile < Tile_Kind__Unknown;
            index_of__tile++) {
        p_tile_logic_manager
            ->tile_interaction__handlers[index_of__tile] = 0;
        p_tile_logic_manager
            ->tile_touch__handlers[index_of__tile] = 0;
    }

    for (Index__u32 index_of__tile = 0;
            index_of__tile < Tile_Cover_Kind__Unknown;
            index_of__tile++) {
        p_tile_logic_manager
            ->tile_cover_interaction__handlers[index_of__tile] = 0;
        p_tile_logic_manager
            ->tile_cover_touch__handlers[index_of__tile] = 0;
    }
}

void register_tile_handler__interact_in__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile,
        f_Tile_Handler__Interact f_tile_handler__interact) {
    if (is_tile_kind__illegal(the_kind_of__tile)) {
        debug_error("register_tile_handler__interact_in__tile_logic_manager, the_kind_of__tile is illegal: %d",
                the_kind_of__tile);
        return;
    }

    p_tile_logic_manager
        ->tile_interaction__handlers[the_kind_of__tile] =
        f_tile_handler__interact;
}

void register_tile_handler__touch_in__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile,
        f_Tile_Handler__Touch f_tile_handler__touch) {
    if (is_tile_kind__illegal(the_kind_of__tile)) {
        debug_error("register_tile_handler__touch_in__tile_logic_manager, the_kind_of__tile is illegal: %d",
                the_kind_of__tile);
        return;
    }

    p_tile_logic_manager
        ->tile_touch__handlers[the_kind_of__tile] =
        f_tile_handler__touch;
}

void register_tile_cover_handler__interact_in__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover,
        f_Tile_Handler__Interact f_tile_handler__interact) {
    if (is_tile_cover_kind__illegal(the_kind_of__tile_cover)) {
        debug_error("register_tile_cover_handler__interact_in__tile_logic_manager, the_kind_of__tile_cover is illegal: %d",
                the_kind_of__tile_cover);
        return;
    }

    p_tile_logic_manager
        ->tile_cover_interaction__handlers[the_kind_of__tile_cover] =
        f_tile_handler__interact;
}

void register_tile_cover_handler__touch_in__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover,
        f_Tile_Handler__Touch f_tile_handler__touch) {
    if (is_tile_cover_kind__illegal(the_kind_of__tile_cover)) {
        debug_error("register_tile_cover_handler__touch_in__tile_logic_manager, the_kind_of__tile_cover is illegal: %d",
                the_kind_of__tile_cover);
        return;
    }

    p_tile_logic_manager
        ->tile_cover_touch__handlers[the_kind_of__tile_cover] =
        f_tile_handler__touch;
}

bool is_tile_possessing__interact_logic(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile) {
    if (is_tile_kind__illegal(the_kind_of__tile)) {
        debug_error("is_tile_possessing__interact_logic, the_kind_of__tile is illegal: %d",
                the_kind_of__tile);
        return false;
    }

    return p_tile_logic_manager
        ->tile_interaction__handlers[the_kind_of__tile];
}

bool is_tile_cover_possessing__interact_logic(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover) {
    if (is_tile_cover_kind__illegal(the_kind_of__tile_cover)) {
        debug_error("is_tile_cover_possessing__interact_logic, the_kind_of__tile_cover is illegal: %d",
                the_kind_of__tile_cover);
        return false;
    }

    return p_tile_logic_manager
        ->tile_cover_interaction__handlers[the_kind_of__tile_cover];
}

bool is_tile_possessing__touch_logic(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile) {
    if (is_tile_kind__illegal(the_kind_of__tile)) {
        debug_error("is_tile_possessing__touch_logic, the_kind_of__tile is illegal: %d",
                the_kind_of__tile);
        return false;
    }

    return p_tile_logic_manager
        ->tile_touch__handlers[the_kind_of__tile];
}

bool is_tile_cover_possessing__touch_logic(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover) {
    if (is_tile_cover_kind__illegal(the_kind_of__tile_cover)) {
        debug_error("is_tile_cover_possessing__touch_logic, the_kind_of__tile_cover is illegal: %d",
                the_kind_of__tile_cover);
        return false;
    }

    return p_tile_logic_manager
        ->tile_cover_touch__handlers[the_kind_of__tile_cover];
}

void invoke_tile_logic__interact(
        Game *p_game,
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity) {
    if (is_tile_kind__illegal(p_tile->the_kind_of_tile__this_tile_is)) {
        debug_error("invoke_tile_logic__interact, the_kind_of__tile is illegal: %d",
                p_tile->the_kind_of_tile__this_tile_is);
        return;
    }

    p_tile_logic_manager
        ->tile_interaction__handlers[
        p_tile->the_kind_of_tile__this_tile_is](
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
}

void invoke_tile_cover_logic__interact(
        Game *p_game,
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32, 
        Entity *p_entity) {
    if (is_tile_cover_kind__illegal(p_tile->the_kind_of_tile_cover__this_tile_has)) {
        debug_error("invoke_tile_cover_logic__interact, the_kind_of__tile_cover is illegal: %d",
                p_tile->the_kind_of_tile__this_tile_is);
        return;
    }

    p_tile_logic_manager
        ->tile_cover_interaction__handlers[
        p_tile->the_kind_of_tile_cover__this_tile_has](
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
}

void invoke_tile_logic__touch(
        Game *p_game,
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32, 
        Entity *p_entity) {
    if (is_tile_kind__illegal(p_tile->the_kind_of_tile__this_tile_is)) {
        debug_error("invoke_tile_logic__touch, the_kind_of__tile is illegal: %d",
                p_tile->the_kind_of_tile__this_tile_is);
        return;
    }

    p_tile_logic_manager
        ->tile_touch__handlers[
        p_tile->the_kind_of_tile__this_tile_is](
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
}

void invoke_tile_cover_logic__touch(
        Game *p_game,
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32, 
        Entity *p_entity) {
    if (is_tile_cover_kind__illegal(p_tile->the_kind_of_tile_cover__this_tile_has)) {
        debug_error("invoke_tile_cover_logic__touch, the_kind_of__tile_cover is illegal: %d",
                p_tile->the_kind_of_tile__this_tile_is);
        return;
    }

    p_tile_logic_manager
        ->tile_cover_touch__handlers[
        p_tile->the_kind_of_tile_cover__this_tile_has](
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
}

void register_tile_logic_handlers(
        Tile_Logic_Manager *p_tile_logic_manager) {
    register_tile_handlers_for__door(
            p_tile_logic_manager);
    register_tile_handlers_for__chest(
            p_tile_logic_manager);
    register_tile_handlers_for__table(
            p_tile_logic_manager);
}
