#ifndef ITEM_H
#define ITEM_H

#include <defines.h>

void initialize_item(
        Item *p_item,
        m_Item_Use m_item_use_handler,
        m_Item_Protect m_item_protect_handler,
        enum Item_Kind the_kind_of__item,
        Item_Filter_Flags item_filter_flags);

void initialize_item__as_void(
        Item *p_item);

Item get_item__void();

static inline
bool is_p_item__void(
        Item *p_item) {
    return p_item->the_kind_of_item__this_item_is
        == Item_Kind__None;
}

#endif
