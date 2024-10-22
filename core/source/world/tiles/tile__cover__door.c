#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
#include "world/tile_logic_manager.h"
#include "world/tile_logic_record.h"
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

static inline
Tile_Cover_Kind orientate_door_placement(
        Tile_Cover_Kind the_kind_of__tile_cover,
        bool is_vertical_or__horizontal) {
    switch (the_kind_of__tile_cover) {
        default:
            return false;
        case Tile_Cover_Kind__Door__Vertical__Wood:
        case Tile_Cover_Kind__Door__Horizontal__Wood:
            return (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Wood
                : Tile_Cover_Kind__Door__Horizontal__Wood
                ;
        case Tile_Cover_Kind__Door__Vertical__Gold:
        case Tile_Cover_Kind__Door__Horizontal__Gold:
            return 
                (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Gold
                : Tile_Cover_Kind__Door__Horizontal__Gold
                ;
        case Tile_Cover_Kind__Door__Vertical__Diamond:
        case Tile_Cover_Kind__Door__Horizontal__Diamond:
            return 
                (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Diamond
                : Tile_Cover_Kind__Door__Horizontal__Diamond
                ;
        case Tile_Cover_Kind__Door__Vertical__Amethyst:
        case Tile_Cover_Kind__Door__Horizontal__Amethyst:
            return 
                (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Amethyst
                : Tile_Cover_Kind__Door__Horizontal__Amethyst
                ;
        case Tile_Cover_Kind__Door__Vertical__Iron:
        case Tile_Cover_Kind__Door__Horizontal__Iron:
            return 
                (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Iron
                : Tile_Cover_Kind__Door__Horizontal__Iron
                ;
        case Tile_Cover_Kind__Door__Vertical__Open__Wood:
        case Tile_Cover_Kind__Door__Horizontal__Open__Wood:
            return (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Open__Wood
                : Tile_Cover_Kind__Door__Horizontal__Open__Wood
                ;
        case Tile_Cover_Kind__Door__Vertical__Open__Gold:
        case Tile_Cover_Kind__Door__Horizontal__Open__Gold:
            return 
                (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Open__Gold
                : Tile_Cover_Kind__Door__Horizontal__Open__Gold
                ;
        case Tile_Cover_Kind__Door__Vertical__Open__Diamond:
        case Tile_Cover_Kind__Door__Horizontal__Open__Diamond:
            return 
                (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Open__Diamond
                : Tile_Cover_Kind__Door__Horizontal__Open__Diamond
                ;
        case Tile_Cover_Kind__Door__Vertical__Open__Amethyst:
        case Tile_Cover_Kind__Door__Horizontal__Open__Amethyst:
            return 
                (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Open__Amethyst
                : Tile_Cover_Kind__Door__Horizontal__Open__Amethyst
                ;
        case Tile_Cover_Kind__Door__Vertical__Open__Iron:
        case Tile_Cover_Kind__Door__Horizontal__Open__Iron:
            return 
                (is_vertical_or__horizontal)
                ? Tile_Cover_Kind__Door__Vertical__Open__Iron
                : Tile_Cover_Kind__Door__Horizontal__Open__Iron
                ;
    }
    return Tile_Cover_Kind__None;
}

static inline
bool is_door_placement__valid(
        Tile *p_tile__one,
        Tile *p_tile__two,
        Tile_Cover_Kind the_kind_of__tile_cover) {
    return (p_tile__one && p_tile__two
            && is_tile_without_a__cover(p_tile__one)
            && is_tile_without_a__cover(p_tile__two)
            && the_kind_of__tile_cover 
            != Tile_Cover_Kind__None);
}

bool f_tile_handler__place__door(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile *p_tile__south, *p_tile__north;

    World *p_world =
        get_p_world_from__game(p_game);

    p_tile__south =
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__world(p_world), 
                add_vectors__3i32(
                    tile_vector__3i32, 
                    VECTOR__3i32__0_n1_0));
    p_tile__north =
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__world(p_world), 
                add_vectors__3i32(
                    tile_vector__3i32, 
                    VECTOR__3i32__0_1_0));
    
    Tile_Cover_Kind the_kind_of__door_placed =
        orientate_door_placement(
                the_kind_of__tile_cover,
                true);
    if (is_door_placement__valid(
                p_tile__north, 
                p_tile__south, 
                the_kind_of__door_placed)) {
        set_tile_cover_kind_of__tile(
                p_tile, 
                the_kind_of__door_placed);
        set_tile__is_unpassable(
                p_tile, 
                true);
        return true;
    }

    Tile *p_tile__west, *p_tile__east;

    p_tile__west =
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__world(p_world), 
                add_vectors__3i32(
                    tile_vector__3i32, 
                    VECTOR__3i32__n1_0_0));
    p_tile__east =
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__world(p_world), 
                add_vectors__3i32(
                    tile_vector__3i32, 
                    VECTOR__3i32__1_0_0));

    if (is_door_placement__valid(
                p_tile__west, 
                p_tile__east, 
                the_kind_of__door_placed)) {
        set_tile_cover_kind_of__tile(
                p_tile, 
                the_kind_of__door_placed);
        set_tile__is_unpassable(
                p_tile, 
                true);
        return true;
    }

    return false;
}

static inline
void register_default_tile_handlers_for__door(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__door) {
    register_tile_logic_record_for__cover_kind(
            p_tile_logic_manager, 
            the_kind_of__door, 
            TILE_LOGIC_RECORD(
                f_tile_interact_handler__door,
                0,
                f_tile_handler__place__door));
}

void register_tile_handlers_for__door(
        Tile_Logic_Manager *p_tile_logic_managers) {
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Wood);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Gold);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Iron);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Diamond);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Amethyst);
    
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Wood);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Gold);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Iron);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Diamond);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Horizontal__Open__Amethyst);





    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Wood);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Gold);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Iron);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Diamond);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Amethyst);
    
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Wood);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Gold);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Iron);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Diamond);
    register_default_tile_handlers_for__door(
            p_tile_logic_managers, 
            Tile_Cover_Kind__Door__Vertical__Open__Amethyst);
}
