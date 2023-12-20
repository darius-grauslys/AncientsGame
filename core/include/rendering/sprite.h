#ifndef SPRITE_H
#define SPRITE_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include <defines.h>

///
/// Returns nullptr (0) if fails.
///
Sprite* get_new_sprite(void);
void set_position_of_sprite(Sprite* sprite, int x, int y);
void offset_position_of_sprite(Sprite* sprite, int dx, int dy);
void release_sprite(Sprite* sprite);
unsigned int get_id_of_sprite(Sprite* sprite);

#endif
