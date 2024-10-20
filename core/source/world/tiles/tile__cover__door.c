#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "world/tile.h"
#include "world/tile_logic_manager.h"
#include <world/tiles/tile__cover__door.h>

void set_tile_cover_as__door(
        Tile *p_tile,
        Tile_Kind the_kind_of__door,
        bool is_horizontal_or__vertical,
        bool is_closed_or__opened) {
    switch (the_kind_of__door) {
        default:
            debug_error("set_tile_cover_as__door, illegal value for, the_kind_of__door: %d", the_kind_of__door);
            break;
        case Tile_Kind__Diamond:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Diamond
                        : Tile_Cover_Kind__Door__Vertical__Diamond);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Diamond
                        : Tile_Cover_Kind__Door__Vertical__Open__Diamond);
            }
            break;
        case Tile_Kind__Amethyst:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Amethyst
                        : Tile_Cover_Kind__Door__Vertical__Amethyst);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Amethyst
                        : Tile_Cover_Kind__Door__Vertical__Open__Amethyst);
            }
            break;
        case Tile_Kind__Stone:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Stone
                        : Tile_Cover_Kind__Door__Vertical__Stone);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Stone
                        : Tile_Cover_Kind__Door__Vertical__Open__Stone);
            }
            break;
        case Tile_Kind__Stone_Brick:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Stone_Brick
                        : Tile_Cover_Kind__Door__Vertical__Stone_Brick);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Stone_Brick
                        : Tile_Cover_Kind__Door__Vertical__Open__Stone_Brick);
            }
            break;
        case Tile_Kind__Oak_Wood:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Wood
                        : Tile_Cover_Kind__Door__Vertical__Wood);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Wood
                        : Tile_Cover_Kind__Door__Vertical__Open__Wood);
            }
            break;
        case Tile_Kind__Gold:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Gold
                        : Tile_Cover_Kind__Door__Vertical__Gold);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Gold
                        : Tile_Cover_Kind__Door__Vertical__Open__Gold);
            }
            break;
        case Tile_Kind__Iron:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Iron
                        : Tile_Cover_Kind__Door__Vertical__Iron);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Iron
                        : Tile_Cover_Kind__Door__Vertical__Open__Iron);
            }
            break;
        case Tile_Kind__Sandstone:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Sandstone
                        : Tile_Cover_Kind__Door__Vertical__Sandstone);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Sandstone
                        : Tile_Cover_Kind__Door__Vertical__Open__Sandstone);
            }
            break;
        case Tile_Kind__Sand:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Sand
                        : Tile_Cover_Kind__Door__Vertical__Sand);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Sand
                        : Tile_Cover_Kind__Door__Vertical__Open__Sand);
            }
            break;
        case Tile_Kind__Dirt:
            if (is_closed_or__opened) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Dirt
                        : Tile_Cover_Kind__Door__Vertical__Dirt);
            } else {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        (is_horizontal_or__vertical)
                        ? Tile_Cover_Kind__Door__Horizontal__Open__Dirt
                        : Tile_Cover_Kind__Door__Vertical__Open__Dirt);
            }
            break;
    }
}

void f_tile_interact_handler__door(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity) {
    if (is_tile_with__general_purpose_data(p_tile)) {
        // TODO: lock/unlock impl.
        return;
    }

    Tile_Cover_Kind the_kind_of__door =
        get_tile_cover_kind_from__tile(p_tile);

    if (is_tile__unpassable(p_tile)) {
        set_tile__is_unpassable(
                p_tile, 
                false);
        if (the_kind_of__door
                < Tile_Cover_Kind__RESERVED_WALL_SKIP_1) {
            set_tile_cover_kind_of__tile(
                    p_tile, 
                    the_kind_of__door
                    + 3 * 32); // TODO: magic numbers
        } else if (the_kind_of__door
                < Tile_Cover_Kind__RESERVED_WALL_SKIP_3
                && the_kind_of__door
                > Tile_Cover_Kind__RESERVED_WALL_SKIP_2) {
            set_tile_cover_kind_of__tile(
                    p_tile, 
                    the_kind_of__door
                    + 32);
        }
        goto update_chunk;
    }

    set_tile__is_unpassable(
            p_tile, 
            true);
    if (the_kind_of__door
            > Tile_Cover_Kind__RESERVED_WALL_SKIP_1
            && the_kind_of__door
            < Tile_Cover_Kind__RESERVED_WALL_SKIP_2) {
        set_tile_cover_kind_of__tile(
                p_tile, 
                the_kind_of__door
                - 3 * 32); // TODO: magic numbers
    } else if (the_kind_of__door
            > Tile_Cover_Kind__RESERVED_WALL_SKIP_3
            && the_kind_of__door
            < Tile_Cover_Kind__RESERVED_WALL_SKIP_4) {
        set_tile_cover_kind_of__tile(
                p_tile, 
                the_kind_of__door
                - 32);
    }

update_chunk:
    // TODO: do just singular chunk.
    PLATFORM_update_chunks(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            get_p_chunk_manager_from__game(p_game));
}

void register_tile_handlers_for__door(
        Tile_Logic_Manager *p_tile_logic_managers) {
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Wood, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Stone, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Stone_Brick, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Gold, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Iron, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Amethyst, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Diamond, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Sandstone, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Sand, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Dirt, 
            f_tile_interact_handler__door);

    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Wood, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Stone, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Stone_Brick, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Gold, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Iron, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Amethyst, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Diamond, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Sandstone, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Sand, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Dirt, 
            f_tile_interact_handler__door);

    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Wood, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Stone, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Stone_Brick, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Gold, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Iron, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Amethyst, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Diamond, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Sandstone, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Sand, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Dirt, 
            f_tile_interact_handler__door);

    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Wood, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Stone, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Stone_Brick, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Gold, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Iron, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Amethyst, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Diamond, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Sandstone, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Sand, 
            f_tile_interact_handler__door);
    register_tile_cover_handler__interact_in__tile_logic_manager(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Dirt, 
            f_tile_interact_handler__door);
}
