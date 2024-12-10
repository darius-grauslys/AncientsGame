#ifndef TOOL_H
#define TOOL_H

#include "defines.h"
#include "inventory/item.h"

void m_item_use_handler__harvest(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game);

void initialize_item_as__tool(
        Item *p_item__tool,
        enum Item_Kind the_kind_of__item,
        Item_Usage_Flags item_usage_flags,
        i32F20 weight_of_each__item,
        Tool_Kind the_kind_of__tool,
        m_Item_Use m_item_use_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler);

static inline
Item get_tool(
        enum Item_Kind the_kind_of__item,
        Item_Usage_Flags item_usage_flags,
        i32F20 weight_of_each__item,
        Tool_Kind the_kind_of__tool,
        m_Item_Use m_item_use_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler) {
    Item item;
    initialize_item_as__tool(
            &item, 
            the_kind_of__item, 
            item_usage_flags, 
            weight_of_each__item, 
            the_kind_of__tool, 
            m_item_use_handler, 
            m_item_equip_handler, 
            m_item_unequip_handler);
    return item;
}

bool set_item_tool_mode(
        Item *p_item,
        Tool_Mode tool_mode);

void set_item_tool_mode_to__next_tool_mode(
        Item *p_item);

static inline
Tool_Mode get_tool_mode_of__item(
        Item *p_item) {
    return p_item->item_tool_mode;
}

static inline
Tool_Kind get_tool_kind_of__tool(
        Item *p_item) {
    return p_item->the_kind_of__tool;
}

#endif
