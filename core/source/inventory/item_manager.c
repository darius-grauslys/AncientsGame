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
#include "inventory/implemented/battleaxe__iron/battleaxe__iron.h"
#include "inventory/implemented/battleaxe__rusted/battleaxe__rusted.h"
#include "inventory/implemented/battleaxe__steel/battleaxe__steel.h"
#include "inventory/implemented/battleaxe__steel__chaos/battleaxe__steel__chaos.h"
#include "inventory/implemented/battleaxe__steel__order/battleaxe__steel__order.h"
#include "inventory/implemented/dagger__iron/dagger__iron.h"
#include "inventory/implemented/dagger__rusted/dagger__rusted.h"
#include "inventory/implemented/dagger__steel/dagger__steel.h"
#include "inventory/implemented/dagger__steel__chaos/dagger__steel__chaos.h"
#include "inventory/implemented/dagger__steel__order/dagger__steel__order.h"
#include "inventory/implemented/hammer__iron/hammer__iron.h"
#include "inventory/implemented/hatchet__iron/hatchet__iron.h"
#include "inventory/implemented/hatchet__rusted/hatchet__rusted.h"
#include "inventory/implemented/hatchet__steel/hatchet__steel.h"
#include "inventory/implemented/hatchet__steel__chaos/hatchet__steel__chaos.h"
#include "inventory/implemented/hatchet__steel__order/hatchet__steel__order.h"
#include "inventory/implemented/pickaxe__iron/pickaxe__iron.h"
#include "inventory/implemented/pile__stone__plenty/pile__stone__plenty.h"
#include "inventory/implemented/pile__stone_brick__plenty/pile__stone_brick__plenty.h"
#include "inventory/implemented/pile__iron__plenty/pile__iron__plenty.h"
#include "inventory/implemented/pile__gold__plenty/pile__gold__plenty.h"
#include "inventory/implemented/pile__amethyst__plenty/pile__amethyst__plenty.h"
#include "inventory/implemented/pile__diamond__plenty/pile__diamond__plenty.h"
#include "inventory/implemented/pile__sand__plenty/pile__sand__plenty.h"
#include "inventory/implemented/pile__dirt__plenty/pile__dirt__plenty.h"
#include "inventory/implemented/pile__wood__plenty/pile__wood__plenty.h"
#include "inventory/implemented/rapier__iron/rapier__iron.h"
#include "inventory/implemented/rapier__rusted/rapier__rusted.h"
#include "inventory/implemented/rapier__steel/rapier__steel.h"
#include "inventory/implemented/rapier__steel__chaos/rapier__steel__chaos.h"
#include "inventory/implemented/scimitar__iron/scimitar__iron.h"
#include "inventory/implemented/scimitar__rusted/scimitar__rusted.h"
#include "inventory/implemented/scimitar__steel/scimitar__steel.h"
#include "inventory/implemented/scimitar__steel__chaos/scimitar__steel__chaos.h"
#include "inventory/implemented/scimitar__steel__order/scimitar__steel__order.h"
#include "inventory/implemented/stick/stick.h"
#include "inventory/implemented/sword__iron/sword__iron.h"
#include "inventory/implemented/sword__rusted/sword__rusted.h"
#include "inventory/implemented/sword__steel/sword__steel.h"
#include "inventory/implemented/sword__steel__chaos/sword__steel__chaos.h"
#include "inventory/implemented/sword__steel__order/sword__steel__order.h"
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

    register_into__item_manager__armor_iron(p_item_manager);
    register_into__item_manager__armor_iron__rusted(p_item_manager);

    register_into__item_manager__armor_gold(p_item_manager);
    register_into__item_manager__armor_gold__chaos(p_item_manager);
    register_into__item_manager__armor_gold__order(p_item_manager);

    register_into__item_manager__armor_steel(p_item_manager);
    register_into__item_manager__armor_steel__chaos(p_item_manager);
    register_into__item_manager__armor_steel__order(p_item_manager);

    register_into__item_manager__stick(p_item_manager);

    register_into__item_manager__battle_axe__iron_into__item_manager(p_item_manager);
    register_into__item_manager__battle_axe__rusted_into__item_manager(p_item_manager);
    register_into__item_manager__battle_axe__steel_into__item_manager(p_item_manager);
    register_into__item_manager__battle_axe__steel__chaos_into__item_manager(p_item_manager);
    register_into__item_manager__battle_axe__steel__order_into__item_manager(p_item_manager);

    register_into__item_manager__dagger__iron_into__item_manager(p_item_manager);
    register_into__item_manager__dagger__rusted_into__item_manager(p_item_manager);
    register_into__item_manager__dagger__steel_into__item_manager(p_item_manager);
    register_into__item_manager__dagger__steel__chaos_into__item_manager(p_item_manager);
    register_into__item_manager__dagger__steel__order_into__item_manager(p_item_manager);

    register_into__item_manager__rapier__iron_into__item_manager(p_item_manager);
    register_into__item_manager__rapier__rusted_into__item_manager(p_item_manager);
    register_into__item_manager__rapier__steel_into__item_manager(p_item_manager);
    register_into__item_manager__rapier__steel__chaos_into__item_manager(p_item_manager);
    register_into__item_manager__dagger__steel__order_into__item_manager(p_item_manager);

    register_into__item_manager__scimitar__iron_into__item_manager(p_item_manager);
    register_into__item_manager__scimitar__rusted_into__item_manager(p_item_manager);
    register_into__item_manager__scimitar__steel_into__item_manager(p_item_manager);
    register_into__item_manager__scimitar__steel__chaos_into__item_manager(p_item_manager);
    register_into__item_manager__scimitar__steel__order_into__item_manager(p_item_manager);

    register_into__item_manager__sword__iron_into__item_manager(p_item_manager);
    register_into__item_manager__sword__rusted_into__item_manager(p_item_manager);
    register_into__item_manager__sword__steel_into__item_manager(p_item_manager);
    register_into__item_manager__sword__steel__chaos_into__item_manager(p_item_manager);
    register_into__item_manager__sword__steel__order_into__item_manager(p_item_manager);

    register_into__item_manager__hammer__iron_into__item_manager(p_item_manager);
    register_into__item_manager__pickaxe__iron_into__item_manager(p_item_manager);

    // TODO: make hatch a tool, not a weapon.
    register_into__item_manager__hatchet__iron_into__item_manager(p_item_manager);
    register_into__item_manager__hatchet__rusted_into__item_manager(p_item_manager);
    register_into__item_manager__hatchet__steel_into__item_manager(p_item_manager);
    register_into__item_manager__hatchet__steel__chaos_into__item_manager(p_item_manager);
    register_into__item_manager__hatchet__steel__order_into__item_manager(p_item_manager);

    register_into__item_manager__pile__stone__plenty_into__item_manager(p_item_manager);
    register_into__item_manager__pile__stone_brick__plenty_into__item_manager(p_item_manager);
    register_into__item_manager__pile__iron__plenty_into__item_manager(p_item_manager);
    register_into__item_manager__pile__gold__plenty_into__item_manager(p_item_manager);
    register_into__item_manager__pile__diamond__plenty_into__item_manager(p_item_manager);
    register_into__item_manager__pile__amethyst__plenty_into__item_manager(p_item_manager);
    register_into__item_manager__pile__dirt__plenty_into__item_manager(p_item_manager);
    register_into__item_manager__pile__sand__plenty_into__item_manager(p_item_manager);
    register_into__item_manager__pile__wood__plenty_into__item_manager(p_item_manager);
}
