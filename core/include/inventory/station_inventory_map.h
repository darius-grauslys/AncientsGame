#ifndef STATION_INVENTORY_MAP_H
#define STATION_INVENTORY_MAP_H

#include <defines.h>

void map_station_inventory(
        Inventory *p_station_inventory,
        Station_Inventory_Map *p_station_inventory_map);

static inline
Item_Kind get_item_kind_of__station_recipe(
        Station_Inventory_Map *p_station_inventory_map) {
    return p_station_inventory_map
        ->p_item_stack__recipe
        ->item
        .the_kind_of_item__this_item_is;
}

static inline
Item_Recipe_Flags get_item_recipe_flags_of__station_recipe(
        Station_Inventory_Map *p_station_inventory_map) {
    return p_station_inventory_map
        ->p_item_stack__recipe
        ->item
        .item_recipe_flags;
}

static inline
Item_Stack *get_p_item_stack_from__station_inventory_map__tool_one(
        Station_Inventory_Map *p_station_inventory_map) {
    return p_station_inventory_map
        ->p_item_stack__tool_one;
}

static inline
Item_Stack *get_p_item_stack_from__station_inventory_map__tool_two(
        Station_Inventory_Map *p_station_inventory_map) {
    return p_station_inventory_map
        ->p_item_stack__tool_two;
}

static inline
Item_Stack *get_p_item_stack_from__station_inventory_map__recipe(
        Station_Inventory_Map *p_station_inventory_map) {
    return p_station_inventory_map
        ->p_item_stack__recipe;
}

static inline
Item_Stack *get_p_item_stack_from__station_inventory_map__required_item(
        Station_Inventory_Map *p_station_inventory_map,
        Index__u8 index_of__required_item) {
#ifndef NDEBUG
    if (index_of__required_item >= ITEM_REQUIREMENT_MAX_QUANTITY_OF) {
        debug_error("get_p_item_stack_from__station_inventory_map__required_item, index out of bounds: %d", index_of__required_item);
        return 0;
    }
#endif
    return &p_station_inventory_map
        ->p_item_stack__required_items[index_of__required_item];
}

#endif
