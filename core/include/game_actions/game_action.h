#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include <defines.h>

static bool inline is_game_action_using__id_or_ptr(
        Game_Action_Flags game_action_flags) {
    return (bool)(game_action_flags 
            & GAME_ACTION_FLAGS__BIT_IS_ID_OR_PTR);
}

#endif
