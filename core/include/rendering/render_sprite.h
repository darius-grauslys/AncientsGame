#ifndef RENDER_SPRITE_H
#define RENDER_SPRITE_H

#include <defines.h>

///
/// On NDS, PLATFORM_render_sprite doesn't do anything, and will be
/// optimized out.
///

void PLATFORM_render_sprite(Sprite_Wrapper *sprite);

#endif
