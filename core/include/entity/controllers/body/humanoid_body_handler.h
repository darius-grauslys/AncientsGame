#ifndef CONTROLLER_HUMANOID_H
#define CONTROLLER_HUMANOID_H

#include <defines.h>

/// 
/// This will manage things such as 
/// health regen, and death
///
void m_handler_for__body_living(
        Entity *p_this_humanoid,
        Game *p_game);

#endif
