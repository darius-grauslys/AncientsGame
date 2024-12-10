#ifndef TILE__COVER__TABLE_H
#define TILE__COVER__TABLE_H

#include "defines.h"
#include "defines_weak.h"
#include <world/tile.h>

typedef enum Table_Part_Kind {
    Table_Part_Kind__None,
    Table_Part_Kind__Left_Or_Top,
    Table_Part_Kind__Middle,
    Table_Part_Kind__Right_Or_Bottom,
    Table_Part_Kind__Unknown,
} Table_Part_Kind;

void set_tile_cover_as__table(
        Tile *p_tile,
        Tile_Cover_Kind the_kind_of__table,
        Table_Part_Kind the_kind_of__table_part,
        bool is_horizontal_or__vertical);

void f_tile_interact_handler__table(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity);

bool f_tile_handler__place__table(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32);

bool f_tile_handler__destroy__table(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32);

void register_tile_handlers_for__table(
        Tile_Logic_Manager *p_tile_logic_managers);

#endif
