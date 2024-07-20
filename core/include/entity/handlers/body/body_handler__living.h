#ifndef LIVING_BODY_HANDLER_H
#define LIVING_BODY_HANDLER_H

#include <defines.h>

/// 
/// This will manage things such as 
/// health regen, and death
///
void m_entity_body_handler__living(
        Entity *p_this_humanoid,
        Game *p_game);

void m_humanoid_handler__game_action_handler(
        Entity *p_entity_self,
        Game_Action *p_game_action,
        Game *p_game);

#endif
