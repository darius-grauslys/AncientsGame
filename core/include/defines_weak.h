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

typedef uint8_t Index__u8;
typedef uint16_t Index__u16;
typedef uint32_t Index_u32;

typedef int32_t     Fractional_with__4bit__i32;

typedef struct Vector__3i32F4_t Vector__3i32F4;
typedef struct Vector__3i32_t Vector__3i32;
typedef struct Vector__3i32_t Chunk_Vector__3i32;
typedef struct Vector__3i32_t Tile_Vector__3i32;

typedef struct Timer__u32_t Timer__u32;
typedef struct Timer__u16_t Timer__u16;
typedef struct Timer__u8_t Timer__u8;

///
/// SECTION_collisions
///

///
/// SECTION_debug
///

///
/// SECTION_entity
///

enum Entity_Kind {
    Entity_Kind__Particle,
    Entity_Kind__Item,
    Entity_Kind__Player,
    Entity_Kind__Skeleton,
    Entity_Kind__Zombie
};

typedef struct Entity_t Entity;

///
/// SECTION_input
///

typedef struct Input_t Input;

///
/// SECTION_inventory
///

enum Item_Kind {
    Item_Kind__None,
    Item_Kind__Stick,
    Item_Kind__Club,
    Item_Kind__Sword__Rusted,
    Item_Kind__Scimitar__Rusted,
    Item_Kind__Dagger__Rusted,
    Item_Kind__Rapier__Rusted,
    Item_Kind__Battleaxe__Rusted,
    Item_Kind__Hatchet__Rusted,
    Item_Kind__Pickaxe__Rusted,
    Item_Kind__Hoe__Rusted,
    Item_Kind__Shovel__Rusted,
    Item_Kind__Sword__Iron,
    Item_Kind__Scimitar__Iron,
    Item_Kind__Dagger__Iron,
    Item_Kind__Rapier__Iron,
    Item_Kind__Battleaxe__Iron,
    Item_Kind__Hatchet__Iron,
    Item_Kind__Pickaxe__Iron,
    Item_Kind__Hoe__Iron,
    Item_Kind__Shovel__Iron,
    Item_Kind__Sword__Steel,
    Item_Kind__Scimitar__Steel,
    Item_Kind__Dagger__Steel,
    Item_Kind__Rapier__Steel,
    Item_Kind__Battleaxe__Steel,
    Item_Kind__Hatchet__Steel,
    Item_Kind__Pickaxe__Steel,
    Item_Kind__Hoe__Steel,
    Item_Kind__Shovel__Steel,
    Item_Kind__Bow,
    Item_Kind__Composite_Bow,
    Item_Kind__Crossbow,
    Item_Kind__Sling,
    Item_Kind__Crossbow__Steel,
    Item_Kind__Arrow__Iron,
    Item_Kind__Arrow__Steel,
    Item_Kind__Crossbow_Bolt__Iron,
    Item_Kind__Crossbow_Bolt__Steel,
    Item_Kind__Glass_Bottle,
    Item_Kind__Bottle__Water,
    Item_Kind__Bottle__Blood,
    Item_Kind__Bottle__White, //TODO: determine exactly what it is
    Item_Kind__Bottle__Gold, //TODO: determine exactly what it is
    Item_Kind__Bottle__Blue, //TODO: determine exactly what it is
    Item_Kind__Bottle__Purple, //TODO: determine exactly what it is
    Item_Kind__Bottle__Sparkling, //TODO: determine exactly what it is
    Item_Kind__Bottle__Grey, //TODO: determine exactly what it is
    Item_Kind__Bomb,
    Item_Kind__Bread,
    Item_Kind__Seeds,
    Item_Kind__String,
    Item_Kind__Tongs__Iron,
    Item_Kind__Hammer__Iron,
    Item_Kind__Pile__Wood,
    Item_Kind__Pile__Stone_Brick,
    Item_Kind__Pile__Gold,
    Item_Kind__Pile__Iron,
    Item_Kind__Pile__Diamond,
    Item_Kind__Pile__Amethyst,
    Item_Kind__Pile__Sandstone,
    Item_Kind__Pile__Stone,
    Item_Kind__Pile__Dirt,
    Item_Kind__Pile__Sand,
    Item_Kind__Pile__Grass,
    Item_Kind__Pile__Leaves,
    Item_Kind__Pile__Snow,
    Item_Kind__Unknown
};


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

typedef struct Scene_t Scene;
typedef struct Scene_Manager_t Scene_Manager;

///
/// SECTION_ui
///

typedef struct UI_Element_t UI_Element;
typedef struct UI_Manager_t UI_Manager;

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
typedef struct Game_Action_t Game_Action;

///
/// SECTION_platform
///

typedef struct PLATFORM_Gfx_Context_t PLATFORM_Gfx_Context;
typedef struct PLATFORM_Texture_t PLATFORM_Texture;
typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;

#endif
