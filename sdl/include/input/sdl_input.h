#ifndef SDL_INPUT_H
#define SDL_INPUT_H

#include <defines.h>

void SDL_initialize_input_bindings();

static inline 
bool SDL_is_input__equip_released(Input *p_input) {
    return p_input->input_flags__released & SDL_INPUT_EQUIP;
}

static inline 
bool SDL_is_input__equip_pressed(Input *p_input) {
    return p_input->input_flags__pressed & SDL_INPUT_EQUIP;
}

static inline 
bool is_input__equip_held(Input *p_input) {
    return p_input->input_flags__held & SDL_INPUT_EQUIP;
}

#endif
