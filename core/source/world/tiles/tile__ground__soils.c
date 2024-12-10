#include "world/tile_logic_manager.h"
#include "world/tiles/tile__ground__soil.h"

void register_tile_handlers_for__soils(
        Tile_Logic_Manager *p_tile_logic_managers) {
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Dirt, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Shovel, 
                Item_Kind__Pile__Dirt__Plenty, 
                1));
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Sand, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Shovel, 
                Item_Kind__Pile__Sand__Plenty, 
                1));
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Grass, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Shovel, 
                Item_Kind__Pile__Grass__Plenty, 
                1));
}
