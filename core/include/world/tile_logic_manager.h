#ifndef TILE_LOGIC_MANAGER_H
#define TILE_LOGIC_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager);

void register_tile_logic_record_for__ground_kind(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile,
        Tile_Logic_Record tile_logic_record);

void register_tile_logic_record_for__cover_kind(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Logic_Record tile_logic_record);

Tile_Logic_Record 
*get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile);

Tile_Logic_Record 
*get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover);

void register_core_tile_logic_handlers(
        Tile_Logic_Manager *p_tile_logic_manager);

#endif
