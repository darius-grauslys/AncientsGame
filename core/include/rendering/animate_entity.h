#ifndef RENDER_ENTITY_H
#define RENDER_ENTITY_H

#include <rendering/animate_sprite.h>
#include <defines.h>

void poll_entity_animation__transition(
        Entity *p_entity,
        f_Sprite_Frame_Lookup f_inital_frame__lookup,
        f_Sprite_Frame_Lookup f_final_frame__lookup,
        bool force);

#endif
