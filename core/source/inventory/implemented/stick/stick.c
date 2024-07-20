#include "inventory/implemented/stick/stick.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_manager.h"

void register_into__item_manager__stick(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Stick, 
            ITEM_FILTER_FLAG__INTERACTABLE, 
            1 << 16, 
            m_item_use_handler__stick, 
            0, 0, 0);
}

void m_item_use_handler__stick(
        Item *p_item_self, 
        Entity *p_entity_user, 
        Game *p_game) {
    // TODO: melee wep
}
