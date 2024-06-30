#ifndef DEFINE_WEAK_H
#define DEFINE_WEAK_H

#include <stdint.h>
#include <stdbool.h>

/// Forward declarations to various types
/// within define.h

///
/// SECTION_default
///

typedef int32_t     i32;
typedef int16_t     i16;
typedef int8_t      i8;
typedef uint32_t    u32;
typedef uint16_t    u16;
typedef uint8_t     u8;

typedef int32_t     i32F4;
typedef int16_t     i16F4;
typedef int8_t      i8F4;
typedef uint32_t    u32F4;
typedef uint16_t    u16F4;
typedef uint8_t     u8F4;

typedef int32_t     i32F8;
typedef int16_t     i16F8;
typedef int8_t      i8F8;

typedef int32_t     i32F20;

typedef uint32_t    Texture_Flags;
typedef uint8_t     Quantity__u8;
typedef uint16_t    Quantity__u16;
typedef uint32_t    Quantity__u32;

typedef uint8_t Index__u8;
typedef uint16_t Index__u16;
typedef uint32_t Index__u32;

typedef int32_t Signed_Index__i32;
typedef int16_t Signed_Index__i16;
typedef int8_t  Signed_Index__i8;

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
    Item_Kind__None = 0,
    Item_Kind__Stick,
    Item_Kind__Club,
    Item_Kind__Glass_Bottle,
    Item_Kind__Bottle__Water,
    Item_Kind__Bottle__Blood,
    Item_Kind__Bottle__White, //TODO: determine exactly what it is
    Item_Kind__Bottle__Gold, //TODO: determine exactly what it is
    Item_Kind__Bottle__Blue, //TODO: determine exactly what it is
    Item_Kind__Bottle__Purple, //TODO: determine exactly what it is
    Item_Kind__Bottle__Sparkling, //TODO: determine exactly what it is
    Item_Kind__Bottle__Grey, //TODO: determine exactly what it is
    Item_Kind__Sword__Rusted,
    Item_Kind__Scimitar__Rusted,
    Item_Kind__Dagger__Rusted,
    Item_Kind__Rapier__Rusted,
    Item_Kind__Battleaxe__Rusted,
    Item_Kind__Hatchet__Rusted,
    Item_Kind__Pickaxe__Rusted,
    Item_Kind__Hoe__Rusted,
    Item_Kind__Shovel__Rusted,
    Item_Kind__Sword__Rusted__Broken,
    Item_Kind__Scimitar__Rusted__Broken,
    Item_Kind__Dagger__Rusted__Broken,
    Item_Kind__Rapier__Rusted__Broken,
    Item_Kind__Battleaxe__Rusted__Broken,
    Item_Kind__Hatchet__Rusted__Broken,
    Item_Kind__Pickaxe__Rusted__Broken,
    Item_Kind__Hoe__Rusted__Broken,
    Item_Kind__Shovel__Rusted__Broken,
    Item_Kind__Potion__Empty,
    Item_Kind__Potion__Divine_Providence,
    Item_Kind__Potion__Chaos, 
    Item_Kind__Potion__Order, 
    Item_Kind__Potion__Demonic_Blood, 
    Item_Kind__Potion__Angel_Blood, 
    Item_Kind__Potion__Death, 
    Item_Kind__Potion__Curse, 
    Item_Kind__Potion__Poison__Greater, 
    Item_Kind__Potion__Healing__Greater, 
    Item_Kind__Potion__Energy__Greater, 
    Item_Kind__Potion__Stability__Greater, 
    Item_Kind__Sword__Iron,
    Item_Kind__Scimitar__Iron,
    Item_Kind__Dagger__Iron,
    Item_Kind__Rapier__Iron,
    Item_Kind__Battleaxe__Iron,
    Item_Kind__Hatchet__Iron,
    Item_Kind__Pickaxe__Iron,
    Item_Kind__Hoe__Iron,
    Item_Kind__Shovel__Iron,
    Item_Kind__Sword__Iron__Broken,
    Item_Kind__Scimitar__Iron__Broken,
    Item_Kind__Dagger__Iron__Broken,
    Item_Kind__Rapier__Iron__Broken,
    Item_Kind__Battleaxe__Iron__Broken,
    Item_Kind__Hatchet__Iron__Broken,
    Item_Kind__Pickaxe__Iron__Broken,
    Item_Kind__Hoe__Iron__Broken,
    Item_Kind__Shovel__Iron__Broken,
    Item_Kind__Potion__Poison,
    Item_Kind__Potion__Healing,
    Item_Kind__Potion__Energy, 
    Item_Kind__Potion__Random, 
    Item_Kind__Artifact__Goddess__Heart, 
    Item_Kind__Sword__Steel,
    Item_Kind__Scimitar__Steel,
    Item_Kind__Dagger__Steel,
    Item_Kind__Rapier__Steel,
    Item_Kind__Battleaxe__Steel,
    Item_Kind__Hatchet__Steel,
    Item_Kind__Pickaxe__Steel,
    Item_Kind__Hoe__Steel,
    Item_Kind__Shovel__Steel,
    Item_Kind__Sword__Steel__Broken,
    Item_Kind__Scimitar__Steel__Broken,
    Item_Kind__Dagger__Steel__Broken,
    Item_Kind__Rapier__Steel__Broken,
    Item_Kind__Battleaxe__Steel__Broken,
    Item_Kind__Hatchet__Steel__Broken,
    Item_Kind__Pickaxe__Steel__Broken,
    Item_Kind__Hoe__Steel__Broken,
    Item_Kind__Shovel__Steel__Broken,
    Item_Kind__Bomb,
    Item_Kind__Sword__Steel__Order,
    Item_Kind__Scimitar__Steel__Order,
    Item_Kind__Dagger__Steel__Order,
    Item_Kind__Rapier__Steel__Order,
    Item_Kind__Battleaxe__Steel__Order,
    Item_Kind__Hatchet__Steel__Order,
    Item_Kind__Pickaxe__Steel__Order,
    Item_Kind__Hoe__Steel__Order,
    Item_Kind__Shovel__Steel__Order,
    Item_Kind__Sword__Steel__Order__Broken,
    Item_Kind__Scimitar__Steel__Order__Broken,
    Item_Kind__Dagger__Steel__Order__Broken,
    Item_Kind__Rapier__Steel__Order__Broken,
    Item_Kind__Battleaxe__Steel__Order__Broken,
    Item_Kind__Hatchet__Steel__Order__Broken,
    Item_Kind__Pickaxe__Steel__Order__Broken,
    Item_Kind__Hoe__Steel__Order__Broken,
    Item_Kind__Shovel__Steel__Order__Broken,
    Item_Kind__Tongs__Iron,
    Item_Kind__Tongs__Iron__Holding__Hot,
    Item_Kind__Hammer__Iron,
    Item_Kind__Sword__Steel__Chaos,
    Item_Kind__Scimitar__Steel__Chaos,
    Item_Kind__Dagger__Steel__Chaos,
    Item_Kind__Rapier__Steel__Chaos,
    Item_Kind__Battleaxe__Steel__Chaos,
    Item_Kind__Hatchet__Steel__Chaos,
    Item_Kind__Pickaxe__Steel__Chaos,
    Item_Kind__Hoe__Steel__Chaos,
    Item_Kind__Shovel__Steel__Chaos,
    Item_Kind__Sword__Steel__Chaos__Broken,
    Item_Kind__Scimitar__Steel__Chaos__Broken,
    Item_Kind__Dagger__Steel__Chaos__Broken,
    Item_Kind__Rapier__Steel__Chaos__Broken,
    Item_Kind__Battleaxe__Steel__Chaos__Broken,
    Item_Kind__Hatchet__Steel__Chaos__Broken,
    Item_Kind__Pickaxe__Steel__Chaos__Broken,
    Item_Kind__Hoe__Steel__Chaos__Broken,
    Item_Kind__Shovel__Steel__Chaos__Broken,
    Item_Kind__Bread,
    Item_Kind__Meat__Cooked,
    Item_Kind__Meat__Raw,
    Item_Kind__Frog_Legs__Cooked,
    Item_Kind__Frog_Legs__Raw,
    Item_Kind__Rabbit_Legs__Cooked,
    Item_Kind__Rabbit_Legs__Raw,
    Item_Kind__Meat_Scrap__Cooked,
    Item_Kind__Meat_Scrap__Raw,
    Item_Kind__Bow,
    Item_Kind__Composite_Bow,
    Item_Kind__Crossbow,
    Item_Kind__Sling,
    Item_Kind__Crossbow__Steel,
    Item_Kind__Bow__Broken,
    Item_Kind__Composite_Bow__Broken,
    Item_Kind__Crossbow__Broken,
    Item_Kind__Sling__Broken,
    Item_Kind__Crossbow__Steel__Broken,
    Item_Kind__Artifact__Scepter__Order,
    Item_Kind__Artifact__Scepter__Chaos,
    Item_Kind__Artifact__Scepter,
    Item_Kind__Artifact__Skull__Full,
    Item_Kind__Artifact__Skull__Half,
    Item_Kind__Artifact__Skull,
    Item_Kind__Artifact__Ankh,
    Item_Kind__Artifact__Ankh__Order,
    Item_Kind__Seeds,
    Item_Kind__Arrow__Iron,
    Item_Kind__Arrow__Steel,
    Item_Kind__Crossbow_Bolt__Iron,
    Item_Kind__Crossbow_Bolt__Steel,
    Item_Kind__String,
    Item_Kind__Ingot__Iron,
    Item_Kind__Ingot__Iron__Rusted,
    Item_Kind__Ingot__Steel,
    Item_Kind__Ingot__Gold,
    Item_Kind__Ingot__Hot,
    Item_Kind__Metal_Scraps__Iron,
    Item_Kind__Metal_Scraps__Iron__Rusted,
    Item_Kind__Metal_Scraps__Steel,
    Item_Kind__Metal_Scraps__Gold,
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
    Item_Kind__Bag_Of__Coal,
    Item_Kind__Bag_Of__Diamonds,
    Item_Kind__Bag_Of__Iron,
    Item_Kind__Bag_Of__Amytheyst,
    Item_Kind__Bag_Of__Gold,
    Item_Kind__Bag_Of__Map__Unused,
    Item_Kind__Bag_Of__Map,
    Item_Kind__Bag_Of__Ink_And_Quill,
    Item_Kind__Bag_Of__Drawing_Compass,
    Item_Kind__Pile__Wood__Partial,
    Item_Kind__Pile__Stone_Brick__Partial,
    Item_Kind__Pile__Gold__Partial,
    Item_Kind__Pile__Iron__Partial,
    Item_Kind__Pile__Diamond__Partial,
    Item_Kind__Pile__Amethyst__Partial,
    Item_Kind__Pile__Sandstone__Partial,
    Item_Kind__Pile__Stone__Partial,
    Item_Kind__Pile__Dirt__Partial,
    Item_Kind__Pile__Sand__Partial,
    Item_Kind__Pile__Grass__Partial,
    Item_Kind__Pile__Leaves__Partial,
    Item_Kind__Pile__Snow__Partial,
    Item_Kind__Pile__Book,
    Item_Kind__Pile__Wood__Plenty,
    Item_Kind__Pile__Stone_Brick__Plenty,
    Item_Kind__Pile__Gold__Plenty,
    Item_Kind__Pile__Iron__Plenty,
    Item_Kind__Pile__Diamond__Plenty,
    Item_Kind__Pile__Amethyst__Plenty,
    Item_Kind__Pile__Sandstone__Plenty,
    Item_Kind__Pile__Stone__Plenty,
    Item_Kind__Pile__Dirt__Plenty,
    Item_Kind__Pile__Sand__Plenty,
    Item_Kind__Pile__Grass__Plenty,
    Item_Kind__Pile__Leaves__Plenty,
    Item_Kind__Pile__Snow__Plenty,
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

enum UI_Window_Kind {
    UI_Window_Kind__None = 0,
    UI_Window_Kind__Idle,
    UI_Window_Kind__Equip,
    UI_Window_Kind__Trade,
    UI_Window_Kind__Labor,
    UI_Window_Kind__Typer,

    UI_Window_Kind__Main_Menu,
    UI_Window_Kind__Singleplayer,
    UI_Window_Kind__Multiplayer,
    UI_Window_Kind__Settings
};

///
/// SECTION_world
///

typedef struct Camera_t Camera;
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
