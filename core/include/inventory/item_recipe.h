#ifndef ITEM_RECIPE_H
#define ITEM_RECIPE_H

#include "defines_weak.h"
#include "inventory/item.h"
#include <defines.h>

void initialize_item_as__item_recipe(
        Item *p_item,
        Item_Kind the_kind_of__item_produced,
        Item_Recipe_Flags item_recipe_flags,
        Station_Kind the_kind_of__station_required);

static inline
Item get_item_recipe(
        Item_Kind the_kind_of__item_produced,
        Item_Recipe_Flags item_recipe_flags,
        Station_Kind the_kind_of__station_required) {
    Item item;
    initialize_item_as__item_recipe(
            &item, 
            the_kind_of__item_produced, 
            item_recipe_flags, 
            the_kind_of__station_required);
    return item;
}

static inline
bool is_item_an__item_recipe(
        Item *p_item) {
    return is_item_of__this_kind(
            p_item, 
            Item_Kind__Item_Recipe);
}

static inline
bool is_first_requirement_of__item_recipe__efficent(
        Item_Recipe_Flags item_recipe_flags) {
    return item_recipe_flags
        & ITEM_RECIPE_FLAG__IS_COST_REDUCTION__ONE;
}

static inline
bool is_second_requirement_of__item_recipe__efficent(
        Item_Recipe_Flags item_recipe_flags) {
    return item_recipe_flags
        & ITEM_RECIPE_FLAG__IS_COST_REDUCTION__TWO;
}

static inline
bool is_third_requirement_of__item_recipe__efficent(
        Item_Recipe_Flags item_recipe_flags) {
    return item_recipe_flags
        & ITEM_RECIPE_FLAG__IS_COST_REDUCTION__THREE;
}

static inline
bool is_fourth_requirement_of__item_recipe__efficent(
        Item_Recipe_Flags item_recipe_flags) {
    return item_recipe_flags
        & ITEM_RECIPE_FLAG__IS_COST_REDUCTION__FOUR;
}

static inline
bool is_output_of__item_recipe__doubled(
        Item_Recipe_Flags item_recipe_flags) {
    return item_recipe_flags
        & ITEM_RECIPE_FLAG__DOUBLE_PRODUCITON;
}

static inline
bool is_tool_requirements_of__item_recipe__preserving(
        Item_Recipe_Flags item_recipe_flags) {
    return item_recipe_flags
        & ITEM_RECIPE_FLAG__HALF_TOOL_CONSUMPTION;
}

static inline
bool is_nth_requirement_of__item_recipe__efficent(
        Item_Recipe_Flags  item_recipe_flags,
        Index__u8 index_of__item) {
    return item_recipe_flags
        & (ITEM_RECIPE_FLAG__IS_COST_REDUCTION__ONE
                << index_of__item)
        ;
}

#endif
