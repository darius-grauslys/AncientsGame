#include "defines.h"
#include "defines_weak.h"
#include "world/tile.h"
#include "world/tile_logic_record.h"
#include "world/tiles/tile__cover__chest.h"
#include "world/tiles/tile__cover__door.h"
#include "world/tiles/tile__cover__ore.h"
#include "world/tiles/tile__cover__table.h"
#include "world/tiles/tile__cover__tree.h"
#include "world/tiles/tile__cover__walls.h"
#include "world/tiles/tile__ground__gems.h"
#include "world/tiles/tile__ground__metals.h"
#include "world/tiles/tile__ground__soil.h"
#include "world/tiles/tile__ground__stones.h"
#include "world/tiles/tile__ground__woods.h"
#include <world/tile_logic_manager.h>

static inline
Tile_Logic_Record
*get_p_tile_logic_record_for__ground_kind_by__index_from__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Index__u32 index_of__record) {
    return &p_tile_logic_manager
        ->tile_logic_records_for__ground_kinds[
            index_of__record];
}

static inline
Tile_Logic_Record
*get_p_tile_logic_record_for__cover_kind_by__index_from__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Index__u32 index_of__record) {
    return &p_tile_logic_manager
        ->tile_logic_records_for__cover_kinds[
            index_of__record];
}

Tile_Logic_Record 
*get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile) {
#ifndef NDEBUG
    if (the_kind_of__tile < 0
            || the_kind_of__tile >= Tile_Kind__Unknown) {
        debug_error("get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager, the_kind_of__tile out of bounds: %d", the_kind_of__tile);
        return 0;
    }
#endif
    return get_p_tile_logic_record_for__ground_kind_by__index_from__tile_logic_manager(
            p_tile_logic_manager, 
            the_kind_of__tile);
}

Tile_Logic_Record 
*get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover) {
#ifndef NDEBUG
    if (the_kind_of__tile_cover < 0
            || the_kind_of__tile_cover >= Tile_Cover_Kind__Unknown) {
        debug_error("get_p_tile_logic_record_for__ground_kind_from__tile_cover_logic_manager, the_kind_of__tile out of bounds: %d", the_kind_of__tile_cover);
        return 0;
    }
#endif
    return get_p_tile_logic_record_for__cover_kind_by__index_from__tile_logic_manager(
            p_tile_logic_manager, 
            the_kind_of__tile_cover);
}

void initialize_tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager) {
    for (Index__u32 index_of__tile = 0;
            index_of__tile < Tile_Kind__Unknown;
            index_of__tile++) {
        Tile_Logic_Record *p_tile_logic_record =
            get_p_tile_logic_record_for__ground_kind_by__index_from__tile_logic_manager(
                    p_tile_logic_manager, 
                    index_of__tile);
        initialize_tile_logic_record_as__unused(
                p_tile_logic_record);
    }

    for (Index__u32 index_of__tile = 0;
            index_of__tile < Tile_Cover_Kind__Unknown;
            index_of__tile++) {
        Tile_Logic_Record *p_tile_logic_record =
            get_p_tile_logic_record_for__cover_kind_by__index_from__tile_logic_manager(
                    p_tile_logic_manager, 
                    index_of__tile);
        initialize_tile_logic_record_as__unused(
                p_tile_logic_record);
    }
}

void register_tile_logic_record_for__ground_kind(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile,
        Tile_Logic_Record tile_logic_record) {
    Tile_Logic_Record *p_tile_logic_record =
        get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                p_tile_logic_manager, 
                the_kind_of__tile);

    *p_tile_logic_record =
        tile_logic_record;
}

void register_tile_logic_record_for__cover_kind(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Logic_Record tile_logic_record) {
    Tile_Logic_Record *p_tile_logic_record =
        get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
                p_tile_logic_manager, 
                the_kind_of__tile_cover);

    *p_tile_logic_record =
        tile_logic_record;
}

void register_core_tile_logic_handlers(
        Tile_Logic_Manager *p_tile_logic_manager) {
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_manager, 
            Tile_Kind__None, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAG__IS_UNPASSABLE,
                Tool_Kind__None,
                0, 0));

    register_tile_handlers_for__ore(
            p_tile_logic_manager);
    register_tile_handlers_for__door(
            p_tile_logic_manager);
    register_tile_handlers_for__chest(
            p_tile_logic_manager);
    register_tile_handlers_for__table(
            p_tile_logic_manager);
    register_tile_handlers_for__trees(
            p_tile_logic_manager);

    register_tile_handlers_for__woods(
            p_tile_logic_manager);
    register_tile_handlers_for__gems(
            p_tile_logic_manager);
    register_tile_handlers_for__metals(
            p_tile_logic_manager);
    register_tile_handlers_for__stones(
            p_tile_logic_manager);
    register_tile_handlers_for__soils(
            p_tile_logic_manager);

    register_tile_handlers_for__walls(
            p_tile_logic_manager);
}

void determine_tile_flags(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile) {
    Tile_Logic_Record *p_tile_logic_record__ground;
    Tile_Logic_Record *p_tile_logic_record__cover;

    p_tile_logic_record__ground =
        get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                p_tile_logic_manager, 
                get_tile_kind_from__tile(p_tile));
    p_tile_logic_record__cover =
        get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
                p_tile_logic_manager, 
                get_tile_cover_kind_from__tile(p_tile));

    bool is_sight_blocking__ground =
        is_tile_logic_record__sight_blocking(
                p_tile_logic_record__ground);
    bool is_sight_blocking__cover =
        is_tile_logic_record__sight_blocking(
                p_tile_logic_record__cover);

    bool is_unpassable__ground =
        is_tile_logic_record__unpassable(
                p_tile_logic_record__ground);
    bool is_unpassable__cover =
        is_tile_logic_record__unpassable(
                p_tile_logic_record__cover);

    set_tile__is_sight_blocking(
            p_tile, 
            is_sight_blocking__cover
            || is_sight_blocking__ground);
    set_tile__is_unpassable(
            p_tile, 
            is_unpassable__cover
            || is_unpassable__ground);
}
