#include "world/tiles/tile__ground__stones.h"
#include "defines.h"
#include "defines_weak.h"
#include "world/tile_logic_manager.h"
#include "world/tile_logic_record.h"

void register_tile_handlers_for__stones(
        Tile_Logic_Manager *p_tile_logic_managers) {
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Stone, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Pickaxe, 
                Item_Kind__Pile__Stone__Plenty, 
                1));
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Sandstone, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Pickaxe, 
                Item_Kind__Pile__Sandstone__Plenty, 
                1));
    register_tile_logic_record_for__ground_kind(
            p_tile_logic_managers, 
            Tile_Kind__Stone_Brick, 
            TILE_LOGIC_RECORD(
                0, 
                0, 
                0, 
                0, 
                TILE_LOGIC_FLAGS__NONE, 
                Tool_Kind__Pickaxe, 
                Item_Kind__Pile__Stone_Brick__Plenty, 
                1));
}
