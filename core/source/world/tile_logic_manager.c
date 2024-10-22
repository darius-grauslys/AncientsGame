#include "defines.h"
#include "defines_weak.h"
#include "world/tile.h"
#include "world/tile_logic_record.h"
#include "world/tiles/tile__cover__chest.h"
#include "world/tiles/tile__cover__door.h"
#include "world/tiles/tile__cover__table.h"
#include <world/tile_logic_manager.h>

Tile_Logic_Record 
*get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile) {
    if (the_kind_of__tile
            == Tile_Kind__None) {
        return 0;
    }
#ifndef NDEBUG
    if (the_kind_of__tile < 0
            || the_kind_of__tile >= Tile_Kind__Unknown) {
        debug_error("get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager, the_kind_of__tile out of bounds: %d", the_kind_of__tile);
        return 0;
    }
#endif
    return &p_tile_logic_manager
        ->tile_logic_records_for__ground_kinds[
        the_kind_of__tile];
}

Tile_Logic_Record 
*get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover) {
    if (the_kind_of__tile_cover
            == Tile_Cover_Kind__None) {
        return 0;
    }
#ifndef NDEBUG
    if (the_kind_of__tile_cover < 0
            || the_kind_of__tile_cover >= Tile_Cover_Kind__Unknown) {
        debug_error("get_p_tile_logic_record_for__ground_kind_from__tile_cover_logic_manager, the_kind_of__tile out of bounds: %d", the_kind_of__tile_cover);
        return 0;
    }
#endif
    return &p_tile_logic_manager
        ->tile_logic_records_for__cover_kinds[
        the_kind_of__tile_cover];
}

void initialize_tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager) {
    for (Index__u32 index_of__tile = 0;
            index_of__tile < Tile_Kind__Unknown;
            index_of__tile++) {
        Tile_Logic_Record *p_tile_logic_record =
            get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                    p_tile_logic_manager, 
                    index_of__tile);
        initialize_tile_logic_record_as__unused(
                p_tile_logic_record);
    }

    for (Index__u32 index_of__tile = 0;
            index_of__tile < Tile_Cover_Kind__Unknown;
            index_of__tile++) {
        Tile_Logic_Record *p_tile_logic_record =
            get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
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
    register_tile_handlers_for__door(
            p_tile_logic_manager);
    register_tile_handlers_for__chest(
            p_tile_logic_manager);
    register_tile_handlers_for__table(
            p_tile_logic_manager);
}
