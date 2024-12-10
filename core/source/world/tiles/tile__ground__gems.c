#include "world/tiles/tile__ground__gems.h"
#include "world/tile_logic_manager.h"

void register_tile_handlers_for__gems(
        Tile_Logic_Manager *p_tile_logic_managers) {
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Amethyst, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Pickaxe, 
                Item_Kind__Pile__Amethyst__Plenty, 
                1));
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Diamond, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Pickaxe, 
                Item_Kind__Pile__Diamond__Plenty, 
                1));
}
