#ifndef ITEM_H
#define ITEM_H

#include <defines.h>

void initialize_item(
        Item *p_item,
        enum Item_Kind the_kind_of__item,
        Item_Filter_Flags item_filter_flags,
        i32F20 weight_of_each__item,
        m_Item_Use m_item_use_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler
        );

void initialize_item_as__empty(
        Item *p_item);

Item get_item__empty();

static inline
Item get_item(
        enum Item_Kind the_kind_of__item,
        Item_Filter_Flags item_filter_flags,
        i32F20 weight_of_each__item,
        m_Item_Use m_item_use_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler) {
    Item item;
    initialize_item(
            &item, 
            the_kind_of__item, 
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

#endif
