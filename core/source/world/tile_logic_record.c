#include "defines.h"
#include <world/tile_logic_record.h>

void initialize_tile_logic_record(
        Tile_Logic_Record *p_tile_logic_record,
        f_Tile_Handler__Interact f_tile_handler__interact,
        f_Tile_Handler__Touch f_tile_handler__touch,
        f_Tile_Handler__Place f_tile_handler__place,
        f_Tile_Handler__Destroy f_tile_handler__destroy,
        Tile_Logic_Flags__u8 tile_logic_flags__u8,
        Tool_Kind     the_kind_of__tool_for__harvesting,
        Item_Kind     the_kind_of__resource_when__harvested,
        Quantity__u32 quantity_of__resources_harvested) {
    p_tile_logic_record
        ->f_tile_handler__interact =
        f_tile_handler__interact;
    p_tile_logic_record
        ->f_tile_handler__touch =
        f_tile_handler__touch;
    p_tile_logic_record
        ->f_tile_handler__place =
        f_tile_handler__place;
    p_tile_logic_record
        ->f_tile_handler__destroy =
        f_tile_handler__destroy;
    p_tile_logic_record
        ->tile_logic_flags__u8 =
        tile_logic_flags__u8;
    p_tile_logic_record
        ->the_kind_of__tool_for__harvesting =
        the_kind_of__tool_for__harvesting;
    p_tile_logic_record
        ->the_kind_of__resource_when__harvested =
        the_kind_of__resource_when__harvested;
    p_tile_logic_record
        ->quantity_of__resources_harvested =
        quantity_of__resources_harvested;
}
