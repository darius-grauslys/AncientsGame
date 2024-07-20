#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <defines.h>

void initialize_item_manager(
        Item_Manager *p_item_manager);

void register_item_in__item_manager(
        Item_Manager *p_item_manager,
        enum Item_Kind the_kind_of__item,
        Item_Filter_Flags item_filter_flags,
        i32F20 weight_per__item,
        m_Item_Use m_item_use_handler,
        m_Item_Protect m_item_protect_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler);

Item get_item_from__item_manager(
        Item_Manager *p_item_manager,
        enum Item_Kind the_kind_of__item);

void load_core_items_into__item_manager(
        Item_Manager *p_item_manager);

#endif
