#ifndef ENTITY__ZOMBIE_H
#define ENTITY__ZOMBIE_H

#include <defines.h>

void initialize_entity_as__zombie(
        Game *p_game,
        PLATFORM_Graphics_Window
            *p_PLATFORM_graphics_window,
        Entity *p_entity,
        Vector__3i32F4 position__3i32F4);

#endif
