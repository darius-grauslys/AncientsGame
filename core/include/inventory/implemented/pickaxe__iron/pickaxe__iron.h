#ifndef PICKAXE__IRON_H
#define PICKAXE__IRON_H

#include <defines.h>

void register_into__item_manager__pickaxe__iron_into__item_manager(
        Item_Manager *p_item_manager);

void m_item_use_handler__pickaxe__iron(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game);

#endif
