#ifndef INPUT_H
#define INPUT_H

#include <defines.h>

void PLATFORM_poll_input(Input *input);

void clear_input(Input *input);

bool is_input__forward(Input *input);
bool is_input__left(Input *input);
bool is_input__right(Input *input);
bool is_input__backwards(Input *input);

bool is_input__game_settings(Input *input);
bool is_input__inventory(Input *input);
bool is_input__use(Input *input);

#endif
