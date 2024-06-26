#include <inventory/item.h>

const Item _item_void = {
    0, 0, 0, 0
};

void initialize_item(
        Item *p_item,
        m_Item_Use m_item_use_handler,
        m_Item_Protect m_item_protect_handler,
        enum Item_Kind the_kind_of__item,
        Item_Filter_Flags item_filter_flags) {
    p_item->m_item_use_handler =
        m_item_use_handler;
    p_item->m_item_protect_handler =
        m_item_protect_handler;
    p_item->the_kind_of_item__this_item_is =
        the_kind_of__item;
    p_item->item_filter_flags =
        item_filter_flags;
}

void initialize_item__as_void(
        Item *p_item) {
    *p_item = _item_void;
}

Item get_item__void() {
    return _item_void;
}
