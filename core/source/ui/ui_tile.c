#include "ui/ui_tile.h"

void initialize_ui_tile_as__empty(UI_Tile *p_ui_tile) {
    p_ui_tile->the_kind_of__ui_tile = 0;
    p_ui_tile->ui_tile_flags = UI_TILE_FLAGS__NONE;
}

void initialize_ui_tile(
        UI_Tile *p_ui_tile,
        UI_Tile_Kind the_kind_of__ui_tile,
        UI_Tile_Flags ui_tile_flags) {
    p_ui_tile->the_kind_of__ui_tile =
        the_kind_of__ui_tile;
    p_ui_tile->ui_tile_flags =
        ui_tile_flags;
}
