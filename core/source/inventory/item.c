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

void set_item_tool_mode_to__next_tool_mode(
        Item *p_item) {
    if (p_item->item_usage_flags
            == ITEM_USAGE_FLAGS__NONE) {
        return;
    }

    switch (p_item->item_tool_mode) {
        default:
            p_item->item_tool_mode =
                Tool_Mode__None;
            break;
        case Tool_Mode__Labor:
            if (set_item_tool_mode(
                        p_item, 
                        Tool_Mode__Labor_Secondary)) {
                break;
            }
        case Tool_Mode__Labor_Secondary:
            if (set_item_tool_mode(
                        p_item, 
                        Tool_Mode__Combat)) {
                break;
            }
        case Tool_Mode__Combat:
        case Tool_Mode__Combat_Lockon:
            if (set_item_tool_mode(
                        p_item, 
                        Tool_Mode__Labor)) {
                break;
            }
    }
}

bool set_item_tool_mode(
        Item *p_item,
        Tool_Mode tool_mode) {
    if (tool_mode < Tool_Mode__None
            || tool_mode >= Tool_Mode__Unknown) {
        return false;
    }
    switch (tool_mode) {
        default:
        case Tool_Mode__None:
            if (p_item->item_usage_flags
                    == ITEM_USAGE_FLAGS__NONE) {
                break;
            }
            return false;
        case Tool_Mode__Labor:
            if (is_item_usable_for__labor(p_item)) {
                break;
            }
            return false;
        case Tool_Mode__Labor_Secondary:
            if (is_item_possessing__secondary_labor(p_item)) {
                break;
            }
            return false;
        case Tool_Mode__Combat:
            if (is_item_usable_for__combat(p_item)) {
                break;
            }
            return false;
        case Tool_Mode__Combat_Lockon:
            if (is_item_usable_for__combat(p_item)) {
                break;
            }
            return false;
    }
    p_item->item_tool_mode =
        tool_mode;
    // TODO: remove, this is here out of a lack of UI
    switch (tool_mode) {
        default:
            debug_info("TOOL MODE: Unknown");
            break;
        case Tool_Mode__Labor:
            debug_info("TOOL MODE: Labor");
            break;
        case Tool_Mode__Labor_Secondary:
            debug_info("TOOL MODE: Labor Secondary");
            break;
        case Tool_Mode__Combat:
            debug_info("TOOL MODE: Combat");
            break;
        case Tool_Mode__Combat_Lockon:
            debug_info("TOOL MODE: Combat Lockon");
            break;
    }
    return true;
}
