#ifndef UI_TILE_MAP_MANAGER_H
#define UI_TILE_MAP_MANAGER_H

#include "defines.h"

void initialize_ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map__manager);

UI_Tile_Map__Wrapper allocate_ui_tile_map_with__ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map_manager,
        UI_Tile_Map_Size catagory_size_of__ui_tile_map);

void release_ui_tile_map_with__ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map_manager,
        UI_Tile_Map__Wrapper ui_tile_map__wrapper);

#endif
