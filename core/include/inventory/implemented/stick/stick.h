#ifndef STICK_H
#define STICK_H

#include <defines.h>

void register_into__item_manager__stick(
        Item_Manager *p_item_manager);

void m_item_use_handler__stick(
        Item *p_item_self, 
        Entity *p_entity_user, 
        Game *p_game);

#endif 
