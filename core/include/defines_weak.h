#ifndef DEFINE_WEAK_H
#define DEFINE_WEAK_H

#include <stdint.h>
#include <stdbool.h>

/// Forward declarations to various types
/// within define.h

///
/// SECTION_default
///

#define BIT(n) (1 << (n))
#define NEXT_BIT(symbol) (symbol << 1)
#define MASK(n) (BIT(n) - 1)


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

typedef int32_t     i32F20;
typedef int16_t     i16F8;
typedef int8_t      i8F8;

typedef int32_t     i32F20;

typedef uint32_t    Texture_Flags;
typedef uint8_t     Sprite_Flags;
typedef uint8_t     Quantity__u8;
typedef uint16_t    Quantity__u16;
typedef uint32_t    Quantity__u32;

typedef uint8_t Index__u8;
typedef uint16_t Index__u16;
typedef uint32_t Index__u32;

typedef int32_t Signed_Index__i32;
typedef int16_t Signed_Index__i16;
typedef int8_t  Signed_Index__i8;

typedef uint32_t Identifier__u32;
typedef uint16_t Identifier__u16;
typedef uint8_t Identifier__u8;

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

enum Entity_Armor_Kind {
    Entity_Armor_Kind__None,
    Entity_Armor_Kind__Cloth,
    Entity_Armor_Kind__Iron,
    Entity_Armor_Kind__Gold,
};

enum Entity_Armor_Modification_Kind {
    Entity_Armor_Modification_Kind__None,
    Entity_Armor_Modification_Kind__Diamond,
    Entity_Armor_Modification_Kind__Amethyst
};

#define RESOURCE_SYMBOL__EMPTY 0
#define RESOURCE_SYMBOL__LOCKED ((uint8_t)-1)

enum Heart_Kind {
    Heart_Kind__Empty = RESOURCE_SYMBOL__EMPTY,
    Heart_Kind__Half_Normal,
    Heart_Kind__Full_Normal,
    Heart_Kind__Half_Poison,
    Heart_Kind__Full_Poison,
    Heart_Kind__Normal_Poison,
    Heart_Kind__Half_Immortal,
    Heart_Kind__Full_Immortal,
    Heart_Kind__Immortal_Normal,
    Heart_Kind__Immortal_Poison,
    Heart_Kind__Locked = RESOURCE_SYMBOL__LOCKED
};

enum Health_State {
    Health_State__None = 0,
    Health_State__Normal,
    Health_State__Hurt,
    Health_State__Injured,
    Health_State__Dying,
    Health_State__Dead,     // health == 0
    Health_State__Unknown = (uint8_t)(-1)
};

enum Energy_Orb_Kind {
    Energy_Orb_Kind__Empty = RESOURCE_SYMBOL__EMPTY,
    Energy_Orb_Kind__Half_Normal,
    Energy_Orb_Kind__Full_Normal,
    Energy_Orb_Kind__Half_Poison,
    Energy_Orb_Kind__Full_Poison,
    Energy_Orb_Kind__Normal_Poison,
    Energy_Orb_Kind__Half_Demonic,
    Energy_Orb_Kind__Full_Demonic,
    Energy_Orb_Kind__Demonic_Normal,
    Energy_Orb_Kind__Demonic_Poison,
    Energy_Orb_Kind__Locked = RESOURCE_SYMBOL__LOCKED
};

enum Energy_State {
    Energy_State__None = 0,
    Energy_State__Normal,
    Energy_State__Tired,
    Energy_State__Exhausted,
    Energy_State__Exerted,      // energy == 0
    Energy_State__Unknown = (uint8_t)(-1)
};

enum Homeostasis_State {
    Homeostasis_State__None = 0,
    Homeostasis_State__Extreme_Burning,
    Homeostasis_State__Burning,
    Homeostasis_State__Hot,
    Homeostasis_State__Neutral,
    Homeostasis_State__Cold,
    Homeostasis_State__Freezing,
    Homeostasis_State__Extreme_Freezing,
    Homeostasis_State__Divine_Providence,
    Homeostasis_State__Soulfull,
    Homeostasis_State__Fleeting_Soul,
    Homeostasis_State__Soulless,
    Homeostasis_State__Lichling,
    Homeostasis_State__Lich,
    Homeostasis_State__Unknown = -1
};

enum Homeostasis_Update_Kind {
    Homeostasis_Update_Kind__None = 0,
    Homeostasis_Update_Kind__Increasing,
    Homeostasis_Update_Kind__Decreasing,
    Homeostasis_Update_Kind__Unknown = -1
};

enum Sustenance_Kind {
    Sustenance_Kind__None = 0,
    Sustenance_Kind__Primary = 1,
    Sustenance_Kind__Secondary = 2,
    Sustenance_Kind__Hunger = 1,    // primary
    Sustenance_Kind__Thirst = 2,    // secondary
    Sustenance_Kind__Sanity = 1,    // primary
    Sustenance_Kind__Blood = 2,     // secondary
    Sustenance_Kind__Unknown = (uint8_t)(-1)
};

enum Sustenance_State {
    Sustenance_State__None = 0,
    Sustenance_State__Bloated,
    Sustenance_State__Full,
    Sustenance_State__Satisifed,
    Sustenance_State__Well,
    Sustenance_State__Indifferent,
    Sustenance_State__Wanting,
    Sustenance_State__Needing,
    Sustenance_State__Desperate,
    Sustenance_State__Dying,
    Sustenance_State__Unknown = (uint8_t)(-1)
};

///
/// All possible entity kinds.
/// Feel free to add your own, but put it
/// before Entity_Kind__Unknown. Putting it
/// after Entity_Kind__Unknown will cause
/// undefined behavior.
///
/// Furthermore DO NOT explicitly assign values to
/// any Entity_Kind, even your own.
///
enum Entity_Kind {
    Entity_Kind__None,
    Entity_Kind__Particle,
    Entity_Kind__Item,
    Entity_Kind__Player,
    Entity_Kind__Skeleton,
    Entity_Kind__Zombie,
    // Entity_Kind__Unknown is used as an array size
    // specifier, or if an Entity_Kind enum doesn't
    // match any defined enum.
    Entity_Kind__Unknown
};

enum Particle_Kind {
    Particle_Kind__None = 0,
    Particle_Kind__Unknown
};

typedef struct Entity_t Entity;

///
/// SECTION_input
///

typedef struct Input_t Input;

///
/// SECTION_inventory
///

typedef struct Item_t Item;
typedef struct Item_Stack_t Item_Stack;
typedef struct Inventory_t Inventory;

enum Item_Kind {
    Item_Kind__None = 0,
    Item_Kind__Stick,
    Item_Kind__Club,
    Item_Kind__RESERVED_0,
    Item_Kind__RESERVED_1,
    Item_Kind__RESERVED_2,
    Item_Kind__RESERVED_3,
    Item_Kind__RESERVED_4,
    Item_Kind__RESERVED_5,
    Item_Kind__RESERVED_6,
    Item_Kind__RESERVED_7,
    Item_Kind__RESERVED_8,
    Item_Kind__RESERVED_9,
    Item_Kind__RESERVED_10,
    Item_Kind__RESERVED_11,
    Item_Kind__RESERVED_12,
    Item_Kind__RESERVED_13,
    Item_Kind__RESERVED_14,
    Item_Kind__RESERVED_15,
    Item_Kind__RESERVED_16,
    Item_Kind__Glass_Bottle,
    Item_Kind__Bottle__Water,
    Item_Kind__Bottle__Blood,
    Item_Kind__Bottle__White, //TODO: determine exactly what it is
    Item_Kind__Bottle__Gold, //TODO: determine exactly what it is
    Item_Kind__Bottle__Blue, //TODO: determine exactly what it is
    Item_Kind__Bottle__Purple, //TODO: determine exactly what it is
    Item_Kind__Bottle__Sparkling, //TODO: determine exactly what it is
    Item_Kind__Bottle__Grey, //TODO: determine exactly what it is
    Item_Kind__RESERVED_17,
    Item_Kind__RESERVED_18,
    Item_Kind__RESERVED_19,
    Item_Kind__RESERVED_20,
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
    Item_Kind__RESERVED_21,
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
    Item_Kind__RESERVED_22,
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
    Item_Kind__RESERVED_23,
    Item_Kind__Potion__Poison,
    Item_Kind__Potion__Healing,
    Item_Kind__Potion__Energy, 
    Item_Kind__Potion__Random, 
    Item_Kind__Artifact__Goddess__Heart, 
    Item_Kind__RESERVED_24,
    Item_Kind__RESERVED_25,
    Item_Kind__RESERVED_26,
    Item_Kind__RESERVED_27,
    Item_Kind__RESERVED_28,
    Item_Kind__RESERVED_29,
    Item_Kind__RESERVED_30,
    Item_Kind__RESERVED_31,
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
    Item_Kind__RESERVED_32,
    Item_Kind__RESERVED_33,
    Item_Kind__Bomb,
    Item_Kind__RESERVED_34,
    Item_Kind__RESERVED_35,
    Item_Kind__RESERVED_36,
    Item_Kind__RESERVED_37,
    Item_Kind__RESERVED_38,
    Item_Kind__RESERVED_39,
    Item_Kind__RESERVED_40,
    Item_Kind__RESERVED_41,
    Item_Kind__RESERVED_42,
    Item_Kind__RESERVED_43,
    Item_Kind__RESERVED_44,
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
    Item_Kind__RESERVED_45,
    Item_Kind__RESERVED_46,
    Item_Kind__Tongs__Iron,
    Item_Kind__Tongs__Iron__Holding__Hot,
    Item_Kind__Hammer__Iron,
    Item_Kind__RESERVED_47,
    Item_Kind__RESERVED_48,
    Item_Kind__RESERVED_49,
    Item_Kind__RESERVED_50,
    Item_Kind__RESERVED_51,
    Item_Kind__RESERVED_52,
    Item_Kind__RESERVED_53,
    Item_Kind__RESERVED_54,
    Item_Kind__RESERVED_55,
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
    Item_Kind__RESERVED_56,
    Item_Kind__RESERVED_57,
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
    Item_Kind__RESERVED_58,
    Item_Kind__RESERVED_59,
    Item_Kind__RESERVED_60,
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
    Item_Kind__RESERVED_61,
    Item_Kind__RESERVED_62,
    Item_Kind__Seeds,
    Item_Kind__RESERVED_63,
    Item_Kind__RESERVED_64,
    Item_Kind__RESERVED_65,
    Item_Kind__RESERVED_66,
    Item_Kind__RESERVED_67,
    Item_Kind__RESERVED_68,
    Item_Kind__RESERVED_69,
    Item_Kind__RESERVED_70,
    Item_Kind__RESERVED_71,
    Item_Kind__RESERVED_72,
    Item_Kind__RESERVED_73,
    Item_Kind__Arrow__Iron,
    Item_Kind__Arrow__Steel,
    Item_Kind__Crossbow_Bolt__Iron,
    Item_Kind__Crossbow_Bolt__Steel,
    Item_Kind__RESERVED_74,
    Item_Kind__RESERVED_75,
    Item_Kind__RESERVED_76,
    Item_Kind__RESERVED_77,
    Item_Kind__RESERVED_78,
    Item_Kind__RESERVED_79,
    Item_Kind__RESERVED_80,
    Item_Kind__RESERVED_81,
    Item_Kind__RESERVED_82,
    Item_Kind__RESERVED_83,
    Item_Kind__RESERVED_84,
    Item_Kind__RESERVED_85,
    Item_Kind__RESERVED_86,
    Item_Kind__RESERVED_87,
    Item_Kind__RESERVED_88,
    Item_Kind__RESERVED_89,
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
    Item_Kind__RESERVED_90,
    Item_Kind__RESERVED_91,
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
    Item_Kind__RESERVED_92,
    Item_Kind__RESERVED_93,
    Item_Kind__Bag_Of__Map__Unused,
    Item_Kind__Bag_Of__Map,
    Item_Kind__Bag_Of__Ink_And_Quill,
    Item_Kind__Bag_Of__Drawing_Compass,
    Item_Kind__RESERVED_94,
    Item_Kind__RESERVED_95,
    Item_Kind__RESERVED_96,
    Item_Kind__RESERVED_97,
    Item_Kind__RESERVED_98,
    Item_Kind__RESERVED_99,
    Item_Kind__RESERVED_100,
    Item_Kind__RESERVED_101,
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
    Item_Kind__RESERVED_102,
    Item_Kind__RESERVED_103,
    Item_Kind__RESERVED_104,
    Item_Kind__RESERVED_105,
    Item_Kind__RESERVED_106,
    Item_Kind__RESERVED_107,
    Item_Kind__RESERVED_108,
    Item_Kind__Pile__Book,
    Item_Kind__RESERVED_109,
    Item_Kind__RESERVED_110,
    Item_Kind__RESERVED_111,
    Item_Kind__RESERVED_112,
    Item_Kind__RESERVED_113,
    Item_Kind__RESERVED_114,
    Item_Kind__RESERVED_115,
    Item_Kind__RESERVED_116,
    Item_Kind__RESERVED_117,
    Item_Kind__RESERVED_118,
    Item_Kind__RESERVED_119,
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
    Item_Kind__RESERVED_120,
    Item_Kind__RESERVED_121,
    Item_Kind__RESERVED_122,
    Item_Kind__RESERVED_123,
    Item_Kind__RESERVED_124,
    Item_Kind__RESERVED_125,
    Item_Kind__RESERVED_126,
    Item_Kind__RESERVED_127,
    Item_Kind__RESERVED_128,
    Item_Kind__RESERVED_129,
    Item_Kind__RESERVED_130,
    Item_Kind__RESERVED_131,
    Item_Kind__RESERVED_132,
    Item_Kind__RESERVED_133,
    Item_Kind__RESERVED_134,
    Item_Kind__RESERVED_135,
    Item_Kind__RESERVED_136,
    Item_Kind__RESERVED_137,
    Item_Kind__RESERVED_138,
    Item_Kind__Armor__Cloth,
    Item_Kind__Armor__Iron,
    Item_Kind__Armor__Iron__Rusted,
    Item_Kind__Armor__Steel,
    Item_Kind__Armor__Steel__Order,
    Item_Kind__Armor__Steel__Chaos,
    Item_Kind__Armor__Gold,
    Item_Kind__Armor__Gold__Order,
    Item_Kind__Armor__Gold__Chaos,
    Item_Kind__Unknown,
    Item_Kind__MAX = BIT(13)
};

/// 
/// SECTION_multiplayer
///

/// 
/// SECTION_rendering
///

typedef struct Font_Letter_t Font_Letter;
typedef struct Font_t Font;
typedef struct Typer_t Typer;

///
/// This is an abstraction for a "sub-context" for graphics.
///
typedef struct PLATFORM_Graphics_Window_t PLATFORM_Graphics_Window;

///
/// Types of graphical window abstractions
/// supported. There can possibly be multiple
/// Graphics_Window_Kind__UI windows open on a
/// given platform, while there is likely only
/// one Graphics_Window_Kind__World window context.
///
enum Graphics_Window_Kind {
    Graphics_Window_Kind__None,
    Graphics_Window_Kind__World,
    Graphics_Window_Kind__UI
};

enum Sprite_Animation_Kind {
    Sprite_Animation_Kind__None,
    Sprite_Animation_Kind__Idle,
    Sprite_Animation_Kind__Humanoid__Walk,
    Sprite_Animation_Kind__Humanoid__Use,
    Sprite_Animation_Kind__Humanoid__Hurt,
    Sprite_Animation_Kind__Humanoid__Die,
    Sprite_Animation_Kind__Player__Sleep,
};

enum Sprite_Allocation_Kind {
    Sprite_Allocation_Kind__None,
    Sprite_Allocation_Kind__Entity,
    Sprite_Allocation_Kind__Item,
    Sprite_Allocation_Kind__UI,
    Sprite_Allocation_Kind__Particle,
    Sprite_Allocation_Kind__Graphics_Pointer
};

typedef struct Sprite_Wrapper_t Sprite_Wrapper;
typedef struct Sprite_Allocation_Specification_t 
               Sprite_Allocation_Specification;
typedef struct Texture_Allocation_Specification_t
               Texture_Allocation_Specification;

///
/// SECTION_scene
///

typedef struct Scene_t Scene;
typedef struct Scene_Manager_t Scene_Manager;

///
/// SECTION_serialization
///


typedef struct Serialized_Field_t Serialized_Field;
typedef struct Serialized_Field_t Serialized_Item_Stack_Ptr;
typedef struct Serialized_Field_t Serialized_Inventory_Ptr;
typedef struct Serialized_Field_t Serialized_Entity_Ptr;
typedef struct Serialized_Field_t Serialized_Chunk_Ptr;

///
/// SECTION_sort
///

///
/// SECTION_ui
///

enum UI_Sprite_Kind {
    UI_Sprite_Kind__None = 0,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close_Below__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near_Below__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far_Below__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close_Above__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near_Above__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far_Above__Hostile,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close_Below__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near_Below__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far_Below__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close_Above__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near_Above__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far_Above__Friendly,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close_Below__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near_Below__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far_Below__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__Close_Above__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__Near_Above__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__Far_Above__Neutral,
    UI_Sprite_Kind__8x8__Nav__Indicator__North,
    UI_Sprite_Kind__8x8__Nav__Indicator__East,
    UI_Sprite_Kind__8x8__Nav__Indicator__South,
    UI_Sprite_Kind__8x8__Nav__Indicator__West,
    UI_Sprite_Kind__8x8__Nav__Indicator__Notch_Large,
    UI_Sprite_Kind__8x8__Nav__Indicator__Notch_Small,
    UI_Sprite_Kind__8x8,
    UI_Sprite_Kind__16x16__Nav__Cap 
        = UI_Sprite_Kind__8x8,
    UI_Sprite_Kind__16x16__Slider__Horizontal,
    UI_Sprite_Kind__16x16__Slider__Vertical,
    UI_Sprite_Kind__16x16,
    UI_Sprite_Kind__32x32__Item_Stack__Iron_Border__3_Digit 
        = UI_Sprite_Kind__16x16,
    UI_Sprite_Kind__32x32__Item_Stack__Iron_Border__2_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Iron_Border__1_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Iron_Border__0_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Diamond_Border__3_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Diamond_Border__2_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Diamond_Border__1_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Diamond_Border__0_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Gold_Border__3_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Gold_Border__2_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Gold_Border__1_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Gold_Border__0_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Amethyst_Border__3_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Amethyst_Border__2_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Amethyst_Border__1_Digit,
    UI_Sprite_Kind__32x32__Item_Stack__Amethyst_Border__0_Digit,
    UI_Sprite_Kind__32x32__Keyboard_Button__Up__28px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Up__20px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Up__16px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Up__12px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Select__28px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Select__20px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Select__16px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Select__12px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Down__28px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Down__20px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Down__16px,
    UI_Sprite_Kind__32x32__Keyboard_Button__Down__12px,
    UI_Sprite_Kind__32x32,
    UI_Sprite_Kind__Unknown = UI_Sprite_Kind__32x32
};

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

enum UI_Element_Kind {
    UI_Element_Kind__None,
    UI_Element_Kind__Button,
    UI_Element_Kind__Draggable,
    UI_Element_Kind__Slider,
    UI_Element_Kind__Drop_Zone,
};

///
/// SECTION_world
///

// TODO: change this to reflect new tileset
enum Tile_Kind {
    Tile_Kind__None,
    Tile_Kind__Oak_Wood,
    Tile_Kind__Stone_Brick,
    Tile_Kind__Gold,
    Tile_Kind__Iron,
    Tile_Kind__Diamond,
    Tile_Kind__Amethyst,
    Tile_Kind__Sandstone,
    Tile_Kind__Stone,
    Tile_Kind__Dirt,
    Tile_Kind__Sand,
    Tile_Kind__Grass,
    Tile_Kind__Leaves,
    Tile_Kind__Snow,
    Tile_Kind__Water,
    Tile_Kind__MAX = MASK(10)
};

// TODO: change this to reflect new tileset
enum Tile_Cover_Kind {
    Tile_Cover_Kind__None               = 0b00000,
    Tile_Cover_Kind__Plant              = (22*32 + 19 + 5),
    Tile_Cover_Kind__Flower_Red         = (22*32 + 19 + 6),
    Tile_Cover_Kind__Flower_Blue        = (22*32 + 19 + 7),
    Tile_Cover_Kind__Flower_Yellow      = (22*32 + 19 + 8),
    Tile_Cover_Kind__Cactus             = (22*32 + 19 + 9),
    Tile_Cover_Kind__Chest_Single       = (29*32 + 19),
    Tile_Cover_Kind__Wall__Oak_Wood     = 0b1000000001,
    Tile_Cover_Kind__Wall__Stone_Brick  = 0b1000000010,
    Tile_Cover_Kind__Wall__Gold         = 0b1000000011,
    Tile_Cover_Kind__Wall__Iron         = 0b1000000100,
    Tile_Cover_Kind__Wall__Diamond      = 0b1000000101,
    Tile_Cover_Kind__Wall__Amethyst     = 0b1000000110,
    Tile_Cover_Kind__Wall__Sandstone    = 0b1000000111,
    Tile_Cover_Kind__Wall__Stone        = 0b1000001000,
    Tile_Cover_Kind__Wall__Dirt         = 0b1000001001,
    Tile_Cover_Kind__Wall__Sand         = 0b1000001010,
};

///
/// These specify the various kinds of Game_Actions
/// which can exist. m_Game_Action_Handler will
/// manage the game actions. 
///
/// See m_Game_Action_Handler for how you should
/// implement such a handler.
///
/// Extending:
/// You can add new kinds, but it must be of value greater
/// than zero, and less than the value of Game_Action_Kind__Unknown.
///
enum Game_Action_Kind {
    Game_Action_Kind__None = 0,
    Game_Action_Kind__Entity__Allocate,
    Game_Action_Kind__Entity__Flags__Set,
    Game_Action_Kind__Entity__Hitbox__Apply_Velocity,
    Game_Action_Kind__Entity__Hitbox__Set_Velocity,
    Game_Action_Kind__Entity__Health__Apply_Damage,
    Game_Action_Kind__Entity__Health__Apply_Healing,
    Game_Action_Kind__Entity__Health__Set,
    Game_Action_Kind__Entity__Energy__Apply_Damage,
    Game_Action_Kind__Entity__Energy__Apply_Healing,
    Game_Action_Kind__Entity__Energy__Set,
    Game_Action_Kind__Entity__Sustenance__Increase,
    Game_Action_Kind__Entity__Sustenance__Decrease,
    Game_Action_Kind__Entity__Homeostasis__Increase,
    Game_Action_Kind__Entity__Homeostasis__Decrease,
    Game_Action_Kind__Entity__Place_Tile,
    Game_Action_Kind__Entity__Item_Stack__Pick_Up,
    Game_Action_Kind__Entity__Item_Stack__Drop,
    Game_Action_Kind__Entity__Item_Stack__Consume,
    Game_Action_Kind__Entity__Item_Stack__Equip,
    Game_Action_Kind__Unknown
};

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
