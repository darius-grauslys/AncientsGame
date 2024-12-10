#include "defines.h"
#include "defines_weak.h"
#include "world/tile.h"
#include "world/tile_logic_manager.h"
#include "world/tile_logic_record.h"
#include <world/tiles/tile__cover__tree.h>

void set_tile_cover_as__tree(
        Tile *p_tile,
        u8 variation) {
    variation %= 3;
    switch(variation) {
        default:
        case 0:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Stump;
            break;
        case 1:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Tree__Oak;
            break;
        case 2:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Tree__Pine;
            break;
    }

    set_tile__is_unpassable(p_tile, true);
}

void register_tile_handlers_for__trees(
        Tile_Logic_Manager *p_tile_logic_manager) {
    register_tile_logic_record_for__cover_kind(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Tree__Oak, 
            TILE_LOGIC_RECORD(
                0, 0, 0, 0, 
                TILE_LOGIC_FLAG__IS_UNPASSABLE, 
                Tool_Kind__Hatchet, 
                Item_Kind__Pile__Wood__Plenty, 
                8));
    register_tile_logic_record_for__cover_kind(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Tree__Pine, 
            TILE_LOGIC_RECORD(
                0, 0, 0, 0, 
                TILE_LOGIC_FLAG__IS_UNPASSABLE, 
                Tool_Kind__Hatchet, 
                Item_Kind__Pile__Wood__Plenty, 
                8));
    register_tile_logic_record_for__cover_kind(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Stump, 
            TILE_LOGIC_RECORD(
                0, 0, 0, 0, 
                TILE_LOGIC_FLAG__IS_UNPASSABLE, 
                Tool_Kind__Hatchet, 
                Item_Kind__Pile__Wood__Plenty, 
                8));
    register_tile_logic_record_for__cover_kind(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Tree__Trunk, 
            TILE_LOGIC_RECORD(
                0, 0, 0, 0, 
                TILE_LOGIC_FLAG__IS_UNPASSABLE, 
                Tool_Kind__Hatchet, 
                Item_Kind__Pile__Wood__Plenty, 
                8));
}
