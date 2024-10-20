#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <defines.h>

void initialize_item_manager(
        Item_Manager *p_item_manager);

static inline
void register_item_in__item_manager(
        Item_Manager *p_item_manager,
        enum Item_Kind the_kind_of__item,
        Item item) {
#ifndef NDEBUG
    if (the_kind_of__item >= Item_Kind__Unknown) {
        debug_error("register_item_in__item_manager, out of bounds: %d",
                the_kind_of__item);
        return;
    }
#endif
    p_item_manager->item_templates[the_kind_of__item] =
        item;
}

Item get_item_from__item_manager(
        Item_Manager *p_item_manager,
        enum Item_Kind the_kind_of__item);

void register_core_items_into__item_manager(
        Item_Manager *p_item_manager);

#endif
