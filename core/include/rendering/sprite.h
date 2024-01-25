#ifndef SPRITE_H
#define SPRITE_H

#include <defines.h>

typedef struct Entity_t Entity;
typedef struct Sprite_Wrapper_t Sprite_Wrapper;
typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;

void init_sprite_wrapper(Sprite_Wrapper *sprite_wrapper,
        enum Entity_Kind entity_kind);

void PLATFORM_init_sprite(PLATFORM_Sprite *sprite,
        enum Entity_Kind entity_kind);

void PLATFORM_release_sprite(PLATFORM_Sprite *sprite);

#endif
