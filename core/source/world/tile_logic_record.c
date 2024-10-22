#include <world/tile_logic_record.h>

void initialize_tile_logic_record(
        Tile_Logic_Record *p_tile_logic_record,
        f_Tile_Handler__Interact f_tile_handler__interact,
        f_Tile_Handler__Touch f_tile_handler__touch,
        f_Tile_Handler__Place f_tile_handler__place) {
    p_tile_logic_record
        ->f_tile_handler__interact =
        f_tile_handler__interact;
    p_tile_logic_record
        ->f_tile_handler__touch =
        f_tile_handler__touch;
    p_tile_logic_record
        ->f_tile_handler__place =
        f_tile_handler__place;
}
