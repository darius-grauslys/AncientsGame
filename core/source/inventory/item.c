#include "defines.h"
#include "defines_weak.h"
#include <inventory/item.h>

const Item _item_void = {
    0, 0, 0, 0
};

void initialize_item(
        Item *p_item,
        enum Item_Kind the_kind_of__item,
        Item_Usage_Flags item_usage_flags,
        Item_Filter_Flags item_filter_flags,
        i32F20 weight_of_each__item,
        m_Item_Use m_item_use_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler) {
    p_item->m_item_use_handler =
        m_item_use_handler;
    p_item->m_item_equip_handler=
        m_item_equip_handler;
    p_item->m_item_unequip_handler=
        m_item_unequip_handler;

    p_item->weight_per__item =
        weight_of_each__item;
    p_item->the_kind_of_item__this_item_is =
        the_kind_of__item;
    p_item->item_filter_flags =
        item_filter_flags;

    p_item->item_usage_flags =
        item_usage_flags;

    if (is_item_usable_for__labor(p_item)) {
        p_item->item_tool_mode = Tool_Mode__Labor;
    } else if (is_item_usable_for__combat(p_item)) {
        p_item->item_tool_mode = Tool_Mode__Combat;
    } else {
        p_item->item_tool_mode = Tool_Mode__None;
    }
}

void initialize_item_as__empty(
        Item *p_item) {
    *p_item = _item_void;
}

Item get_item__empty() {
    return _item_void;
}

