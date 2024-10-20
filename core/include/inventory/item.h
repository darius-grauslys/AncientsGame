#ifndef ITEM_H
#define ITEM_H

#include "defines_weak.h"
#include <defines.h>

void initialize_item(
        Item *p_item,
        enum Item_Kind the_kind_of__item,
        Item_Usage_Flags item_usage_flags,
        Item_Filter_Flags item_filter_flags,
        i32F20 weight_of_each__item,
        m_Item_Use m_item_use_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler
        );

void initialize_item_as__empty(
        Item *p_item);

Item get_item__empty();

void set_item_tool_mode_to__next_tool_mode(
        Item *p_item);

bool set_item_tool_mode(
        Item *p_item,
        Tool_Mode tool_mode);

static inline
Item_Kind get_item_kind_of__item(
        Item *p_item) {
    return p_item->the_kind_of_item__this_item_is;
}

static inline
Item get_item(
        enum Item_Kind the_kind_of__item,
        Item_Usage_Flags item_usage_flags,
        Item_Filter_Flags item_filter_flags,
        i32F20 weight_of_each__item,
        m_Item_Use m_item_use_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler) {
    Item item;
    initialize_item(
            &item, 
            the_kind_of__item, 
            item_usage_flags,
            item_filter_flags, 
            weight_of_each__item, 
            m_item_use_handler, 
            m_item_equip_handler, 
            m_item_unequip_handler);
    return item;
}

static inline
bool is_p_item__empty(
        Item *p_item) {
    return p_item->the_kind_of_item__this_item_is
        == Item_Kind__None;
}


static inline
bool is_item_of__this_kind(
        Item *p_item,
        Item_Kind the_kind_of__item) {
    return p_item->the_kind_of_item__this_item_is
        == the_kind_of__item;
}

// TODO: rename to be same item_kind
static inline
bool is_p_items__equal(
        Item *p_item__one,
        Item *p_item__two) {
    return
        p_item__one->the_kind_of_item__this_item_is
        == p_item__two->the_kind_of_item__this_item_is
        ;
}

static inline
bool does_item_have__equip_handler(
        Item *p_item) {
    return p_item->m_item_equip_handler;
}

static inline
bool does_item_have__unequip_handler(
        Item *p_item) {
    return p_item->m_item_unequip_handler;
}

static inline
bool does_item_have__use_handler(
        Item *p_item) {
    return p_item->m_item_use_handler;
}

static inline
bool is_item_usable_for__labor(
        Item *p_item) {
    return p_item->item_usage_flags 
        & ITEM_USAGE_FLAG__IS_LABOR;
}

static inline
bool is_item_usable_for__combat(
        Item *p_item) {
    return p_item->item_usage_flags 
        & ITEM_USAGE_FLAG__IS_COMBAT;
}

static inline
bool is_item_possessing__secondary_labor(
        Item *p_item) {
    return p_item->item_usage_flags 
        & ITEM_USAGE_FLAG__IS_LABOR__SECONDARY;
}

static inline
bool is_item_tool_mode__labor(
        Item *p_item) {
    return p_item->item_tool_mode
        == Tool_Mode__Labor;
}

static inline
bool is_item_tool_mode__labor_secondary(
        Item *p_item) {
    return p_item->item_tool_mode
        == Tool_Mode__Labor_Secondary;
}

static inline
bool is_item_tool_mode__combat(
        Item *p_item) {
    return p_item->item_tool_mode
        == Tool_Mode__Combat;
}

static inline
bool is_item_tool_mode__combat_lockon(
        Item *p_item) {
    return p_item->item_tool_mode
        == Tool_Mode__Combat_Lockon;
}

static inline
bool is_item_tool_mode_a__combat_mode(
        Item *p_item) {
    return (is_item_tool_mode__combat(p_item)
            || is_item_tool_mode__combat_lockon(p_item));
}

#endif
