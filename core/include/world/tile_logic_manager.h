#ifndef TILE_LOGIC_MANAGER_H
#define TILE_LOGIC_MANAGER_H

#include <defines.h>

void initialize_tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager);

void register_tile_handler__interact_in__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile,
        f_Tile_Handler__Interact f_tile_handler__interact);

void register_tile_handler__touch_in__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile,
        f_Tile_Handler__Touch f_tile_handler__touch);

void register_tile_cover_handler__interact_in__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile,
        f_Tile_Handler__Interact f_tile_handler__interact);

void register_tile_cover_handler__touch_in__tile_logic_manager(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile,
        f_Tile_Handler__Touch f_tile_handler__touch);

bool does_tile_have__interact_logic(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile);

bool does_tile_cover_have__interact_logic(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover);

bool does_tile_have__touch_logic(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Kind the_kind_of__tile);

bool does_tile_cover_have__touch_logic(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__tile_cover);

void invoke_tile_logic__interact(
        Game *p_game,
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile,
        Entity *p_entity);

void invoke_tile_cover_logic__interact(
        Game *p_game,
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile,
        Entity *p_entity);

void invoke_tile_logic__touch(
        Game *p_game,
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile,
        Entity *p_entity);

void invoke_tile_cover_logic__touch(
        Game *p_game,
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile *p_tile,
        Entity *p_entity);

#endif