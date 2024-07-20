#include "inventory/item_manager.h"
#include "defines_weak.h"
#include "inventory/implemented/armor__cloth/armor__cloth.h"
#include "inventory/implemented/armor__gold/armor__gold.h"
#include "inventory/implemented/armor__gold__chaos/armor__gold__chaos.h"
#include "inventory/implemented/armor__gold__order/armor__gold__order.h"
#include "inventory/implemented/armor__iron/armor__iron.h"
#include "inventory/implemented/armor__iron__rusted/armor__iron__rusted.h"
#include "inventory/implemented/armor__steel/armor__steel.h"
#include "inventory/implemented/armor__steel__chaos/armor__steel__chaos.h"
#include "inventory/implemented/armor__steel__order/armor__steel__order.h"
#include "inventory/implemented/stick/stick.h"
#include "inventory/item.h"

void initialize_item_manager(
        Item_Manager *p_item_manager) {
    for (Index__u32 index_of__item_template = 0;
            index_of__item_template
            < (u16)Item_Kind__Unknown;
            index_of__item_template++) {
        p_item_manager->item_templates[index_of__item_template] =
            get_item__empty();
    }
}

Item get_item_from__item_manager(
        Item_Manager *p_item_manager,
        enum Item_Kind the_kind_of__item) {
#ifndef NDEBUG
    if (the_kind_of__item >= Item_Kind__Unknown) {
        debug_error("get_item_from__item_manager, out of bounds: %d",
                the_kind_of__item);
        return get_item__empty();
    }
#endif
    return p_item_manager->item_templates[the_kind_of__item];
}

void load_core_items_into__item_manager(
        Item_Manager *p_item_manager) {
    // behold, the core items:
    register_into__item_manager__armor_cloth(p_item_manager);
    register_into__item_manager__armor_gold(p_item_manager);
    register_into__item_manager__armor_gold__chaos(p_item_manager);
    register_into__item_manager__armor_gold__order(p_item_manager);
    register_into__item_manager__armor_iron(p_item_manager);
    register_into__item_manager__armor_iron__rusted(p_item_manager);
    register_into__item_manager__armor_steel(p_item_manager);
    register_into__item_manager__armor_steel__chaos(p_item_manager);
    register_into__item_manager__armor_steel__order(p_item_manager);
    register_into__item_manager__stick(p_item_manager);
}
