#include "world/tiles/tile__ground__metals.h"
#include "world/tile_logic_manager.h"

void register_tile_handlers_for__metals(
        Tile_Logic_Manager *p_tile_logic_managers) {
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Gold, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Pickaxe, 
                Item_Kind__Pile__Gold__Plenty, 
                1));
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Iron, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Pickaxe, 
                Item_Kind__Pile__Iron__Plenty, 
                1));
}
