#include "world/tiles/tile__ground__woods.h"
#include "world/tile_logic_manager.h"

void register_tile_handlers_for__woods(
        Tile_Logic_Manager *p_tile_logic_managers) {
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Oak_Wood, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Hatchet, 
                Item_Kind__Pile__Wood__Plenty, 
                1));
}
