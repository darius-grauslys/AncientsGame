#ifndef DEFINE_WEAK_H
#define DEFINE_WEAK_H

#include <stdint.h>
#include <stdbool.h>

/// Forward declarations to various types
/// within define.h

///
/// SECTION_default
///

typedef uint32_t    Texture_Flags;
typedef uint8_t     Quantity__u8;
typedef uint16_t    Quantity__u16;
typedef uint32_t    Quantity__u32;

typedef int32_t     Fractional_with__4bit__i32;

///
/// SECTION_collisions
///

///
/// SECTION_debug
///

///
/// SECTION_entity
///

typedef struct Entity_t Entity;

///
/// SECTION_input
///

///
/// SECTION_inventory
///

/// 
/// SECTION_multiplayer
///

/// 
/// SECTION_rendering
///

typedef struct Sprite_Wrapper_t Sprite_Wrapper;

///
/// SECTION_scene
///

///
/// SECTION_ui
///

///
/// SECTION_world
///

typedef struct Chunk_Manager_t Chunk_Manager;
typedef struct Chunk_t Chunk;
typedef struct Tile_t Tile;

///
/// SECTION_core
///

typedef struct Game_t Game;

///
/// SECTION_platform
///

typedef struct PLATFORM_Gfx_Context_t PLATFORM_Gfx_Context;
typedef struct PLATFORM_Texture_t PLATFORM_Texture;

#endif
