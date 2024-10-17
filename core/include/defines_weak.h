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
/// SECTION_audio
///

typedef u8 Audio_Flags__u8;
typedef struct Audio_Effect_t Audio_Effect;

enum Audio_Effect_Kind {
    Audio_Effect_Kind__None,
    Audio_Effect_Kind__Test,
    Audio_Effect_Kind__Footstep__Wood,
    Audio_Effect_Kind__Footstep__Rock,
    Audio_Effect_Kind__Footstep__Metal,
    Audio_Effect_Kind__Footstep__Gem,
    Audio_Effect_Kind__Footstep__Dirt,
    Audio_Effect_Kind__Footstep__Sand,
    Audio_Effect_Kind__Footstep__Grass,
    Audio_Effect_Kind__Weapon__Melee,
    Audio_Effect_Kind__Weapon__Ranged__Thrown,
    Audio_Effect_Kind__Weapon__Ranged__Shot,
    Audio_Effect_Kind__Eat__Crunch,
    Audio_Effect_Kind__Eat__Chew,
    Audio_Effect_Kind__Drink,
    Audio_Effect_Kind__Humanoid__Male__Effort,
    Audio_Effect_Kind__Humanoid__Male__Hurt,
    Audio_Effect_Kind__Humanoid__Male__Die,
    Audio_Effect_Kind__Humanoid__Female__Effort,
    Audio_Effect_Kind__Humanoid__Female__Hurt,
    Audio_Effect_Kind__Humanoid__Female__Die,
    Audio_Effect_Kind__Monster__Zombie__Idle,
    Audio_Effect_Kind__Monster__Zombie__Alert,
    Audio_Effect_Kind__Monster__Zombie__Hurt,
    Audio_Effect_Kind__Monster__Zombie__Attack,
    Audio_Effect_Kind__Monster__Zombie__Die,
    Audio_Effect_Kind__Monster__Skeleton__Idle,
    Audio_Effect_Kind__Monster__Skeleton__Alert,
    Audio_Effect_Kind__Monster__Skeleton__Hurt,
    Audio_Effect_Kind__Monster__Skeleton__Attack,
    Audio_Effect_Kind__Monster__Skeleton__Die,
    Audio_Effect_Kind__Animal__Cow__Idle,
    Audio_Effect_Kind__Animal__Cow__Hurt,
    Audio_Effect_Kind__Animal__Cow__Die,
    Audio_Effect_Kind__Animal__Pig__Idle,
    Audio_Effect_Kind__Animal__Pig__Hurt,
    Audio_Effect_Kind__Animal__Pig__Die,
    Audio_Effect_Kind__Animal__Rabbit__Idle,
    Audio_Effect_Kind__Animal__Rabbit__Hurt,
    Audio_Effect_Kind__Animal__Rabbit__Die,
    Audio_Effect_Kind__Animal__Bird__Idle,
    Audio_Effect_Kind__Animal__Bird__Hurt,
    Audio_Effect_Kind__Animal__Bird__Die,
    Audio_Effect_Kind__Animal__Frog__Idle,
    Audio_Effect_Kind__Animal__Frog__Hurt,
    Audio_Effect_Kind__Animal__Frog__Die,
    Audio_Effect_Kind__Unknown,
    Audio_Effect_Kind__MAX = 128
};

enum Audio_Stream_Kind {
    Audio_Stream_Kind__None,
    Audio_Stream_Kind__Track_1,
    Audio_Stream_Kind__Track_2,
    Audio_Stream_Kind__Track_3,
    Audio_Stream_Kind__Track_4,
    Audio_Stream_Kind__Unknown
};

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
    Entity_Armor_Kind__Steel,
    Entity_Armor_Kind__Gold,
};

enum Entity_Armor_Modification_Kind {
    Entity_Armor_Modification_Kind__None,
    Entity_Armor_Modification_Kind__Rusted,
    Entity_Armor_Modification_Kind__Diamond,
    Entity_Armor_Modification_Kind__Amethyst
};

enum Entity_Equipment_Slot_Kind {
    Entity_Equipment_Slot_Kind__Armor,
    Entity_Equipment_Slot_Kind__Main_Hand,
    Entity_Equipment_Slot_Kind__Off_Hand,
    Entity_Equipment_Slot_Kind__Consumable_1,
    Entity_Equipment_Slot_Kind__Consumable_2,
    Entity_Equipment_Slot_Kind__Consumable_3
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
    Entity_Kind__Trigger_Box,
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

typedef enum Item_Kind {
    Item_Kind__None = 0,
    Item_Kind__Stick,
    Item_Kind__Club,
    Item_Kind__Stone,
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
    Item_Kind__Sword__Rusted,
    Item_Kind__Scimitar__Rusted,
    Item_Kind__Dagger__Rusted,
    Item_Kind__Rapier__Rusted,
    Item_Kind__Battleaxe__Rusted,
    Item_Kind__Hatchet__Rusted,
    Item_Kind__Pickaxe__Rusted,
    Item_Kind__Hoe__Rusted,
    Item_Kind__Shovel__Rusted,
    Item_Kind__Hammer__Rusted,
    Item_Kind__Sword__Rusted__Broken,
    Item_Kind__Scimitar__Rusted__Broken,
    Item_Kind__Dagger__Rusted__Broken,
    Item_Kind__Rapier__Rusted__Broken,
    Item_Kind__Battleaxe__Rusted__Broken,
    Item_Kind__Hatchet__Rusted__Broken,
    Item_Kind__Pickaxe__Rusted__Broken,
    Item_Kind__Hoe__Rusted__Broken,
    Item_Kind__Shovel__Rusted__Broken,
    Item_Kind__Hammer__Rusted__Broken,
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
    Item_Kind__Hammer__Iron,
    Item_Kind__Sword__Iron__Broken,
    Item_Kind__Scimitar__Iron__Broken,
    Item_Kind__Dagger__Iron__Broken,
    Item_Kind__Rapier__Iron__Broken,
    Item_Kind__Battleaxe__Iron__Broken,
    Item_Kind__Hatchet__Iron__Broken,
    Item_Kind__Pickaxe__Iron__Broken,
    Item_Kind__Hoe__Iron__Broken,
    Item_Kind__Shovel__Iron__Broken,
    Item_Kind__Hammer__Iron__Broken,
    Item_Kind__Potion__Poison,
    Item_Kind__Potion__Healing,
    Item_Kind__Potion__Energy, 
    Item_Kind__Potion__Random, 
    Item_Kind__Artifact__Goddess__Heart, 
    Item_Kind__RESERVED_20,
    Item_Kind__RESERVED_21,
    Item_Kind__RESERVED_22,
    Item_Kind__RESERVED_23,
    Item_Kind__RESERVED_24,
    Item_Kind__RESERVED_25,
    Item_Kind__RESERVED_26,
    Item_Kind__Sword__Steel,
    Item_Kind__Scimitar__Steel,
    Item_Kind__Dagger__Steel,
    Item_Kind__Rapier__Steel,
    Item_Kind__Battleaxe__Steel,
    Item_Kind__Hatchet__Steel,
    Item_Kind__Pickaxe__Steel,
    Item_Kind__Hoe__Steel,
    Item_Kind__Shovel__Steel,
    Item_Kind__Hammer__Steel,
    Item_Kind__Sword__Steel__Broken,
    Item_Kind__Scimitar__Steel__Broken,
    Item_Kind__Dagger__Steel__Broken,
    Item_Kind__Rapier__Steel__Broken,
    Item_Kind__Battleaxe__Steel__Broken,
    Item_Kind__Hatchet__Steel__Broken,
    Item_Kind__Pickaxe__Steel__Broken,
    Item_Kind__Hoe__Steel__Broken,
    Item_Kind__Shovel__Steel__Broken,
    Item_Kind__Hammer__Steel__Broken,
    Item_Kind__RESERVED_27,
    Item_Kind__Bomb,
    Item_Kind__Key,
    Item_Kind__Lock,
    Item_Kind__Keyring,
    Item_Kind__Lockpick,
    Item_Kind__Lockwrench,
    Item_Kind__RESERVED_28,
    Item_Kind__RESERVED_29,
    Item_Kind__RESERVED_30,
    Item_Kind__RESERVED_31,
    Item_Kind__RESERVED_32,
    Item_Kind__Sword__Steel__Order,
    Item_Kind__Scimitar__Steel__Order,
    Item_Kind__Dagger__Steel__Order,
    Item_Kind__Rapier__Steel__Order,
    Item_Kind__Battleaxe__Steel__Order,
    Item_Kind__Hatchet__Steel__Order,
    Item_Kind__Pickaxe__Steel__Order,
    Item_Kind__Hoe__Steel__Order,
    Item_Kind__Shovel__Steel__Order,
    Item_Kind__Hammer__Steel__Order,
    Item_Kind__Sword__Steel__Order__Broken,
    Item_Kind__Scimitar__Steel__Order__Broken,
    Item_Kind__Dagger__Steel__Order__Broken,
    Item_Kind__Rapier__Steel__Order__Broken,
    Item_Kind__Battleaxe__Steel__Order__Broken,
    Item_Kind__Hatchet__Steel__Order__Broken,
    Item_Kind__Pickaxe__Steel__Order__Broken,
    Item_Kind__Hoe__Steel__Order__Broken,
    Item_Kind__Shovel__Steel__Order__Broken,
    Item_Kind__Hammer__Steel__Order__Broken,
    Item_Kind__RESERVED_33,
    Item_Kind__Tongs__Tool,
    Item_Kind__Tongs__Tool_Hot,
    Item_Kind__Hammer__Tool,
    Item_Kind__Saw__Iron,
    Item_Kind__Chisel__Iron,
    Item_Kind__Mortar_And_Pedstal,
    Item_Kind__Circle_Flask,
    Item_Kind__Crucible,
    Item_Kind__Ingot_Mold,
    Item_Kind__Bow_Saw,
    Item_Kind__Scisors,
    Item_Kind__Sword__Steel__Chaos,
    Item_Kind__Scimitar__Steel__Chaos,
    Item_Kind__Dagger__Steel__Chaos,
    Item_Kind__Rapier__Steel__Chaos,
    Item_Kind__Battleaxe__Steel__Chaos,
    Item_Kind__Hatchet__Steel__Chaos,
    Item_Kind__Pickaxe__Steel__Chaos,
    Item_Kind__Hoe__Steel__Chaos,
    Item_Kind__Shovel__Steel__Chaos,
    Item_Kind__Hammer__Steel__Chaos,
    Item_Kind__Sword__Steel__Chaos__Broken,
    Item_Kind__Scimitar__Steel__Chaos__Broken,
    Item_Kind__Dagger__Steel__Chaos__Broken,
    Item_Kind__Rapier__Steel__Chaos__Broken,
    Item_Kind__Battleaxe__Steel__Chaos__Broken,
    Item_Kind__Hatchet__Steel__Chaos__Broken,
    Item_Kind__Pickaxe__Steel__Chaos__Broken,
    Item_Kind__Hoe__Steel__Chaos__Broken,
    Item_Kind__Shovel__Steel__Chaos__Broken,
    Item_Kind__Hammer__Steel__Chaos__Broken,
    Item_Kind__RESERVED_34,
    Item_Kind__Bread,
    Item_Kind__Meat__Cooked,
    Item_Kind__Frog_Legs__Cooked,
    Item_Kind__Rabbit_Legs__Cooked,
    Item_Kind__Meat_Scrap__Cooked,
    Item_Kind__Pasta__Raw,
    Item_Kind__Pumpkin_Pie,
    Item_Kind__RESERVED_35,
    Item_Kind__RESERVED_36,
    Item_Kind__RESERVED_37,
    Item_Kind__RESERVED_38,
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
    Item_Kind__RESERVED_39,
    Item_Kind__RESERVED_40,
    Item_Kind__RESERVED_41,
    Item_Kind__Feather,
    Item_Kind__Meat__Raw,
    Item_Kind__Frog_Legs__Raw,
    Item_Kind__Rabbit_Legs__Raw,
    Item_Kind__Meat_Scrap__Raw,
    Item_Kind__Pasta,
    Item_Kind__RESERVED_42,
    Item_Kind__RESERVED_43,
    Item_Kind__RESERVED_44,
    Item_Kind__RESERVED_45,
    Item_Kind__RESERVED_46,
    Item_Kind__Arrow__Iron,
    Item_Kind__Arrow__Steel,
    Item_Kind__Crossbow_Bolt__Iron,
    Item_Kind__Crossbow_Bolt__Steel,
    Item_Kind__Shuriken__Iron,
    Item_Kind__Shuriken__Steel,
    Item_Kind__RESERVED_47,
    Item_Kind__RESERVED_48,
    Item_Kind__RESERVED_49,
    Item_Kind__RESERVED_50,
    Item_Kind__RESERVED_51,
    Item_Kind__RESERVED_52,
    Item_Kind__RESERVED_53,
    Item_Kind__RESERVED_54,
    Item_Kind__RESERVED_55,
    Item_Kind__RESERVED_56,
    Item_Kind__RESERVED_57,
    Item_Kind__RESERVED_58,
    Item_Kind__RESERVED_59,
    Item_Kind__RESERVED_60,
    Item_Kind__RESERVED_61,
    Item_Kind__Seed__Wheat,
    Item_Kind__Seed__Pumpkin,
    Item_Kind__Seed__Watermelon,
    Item_Kind__Seed__Corn,
    Item_Kind__Seed__Tomatoe,
    Item_Kind__Wheat,
    Item_Kind__Tomatoe,
    Item_Kind__Pumpkin,
    Item_Kind__Watermelon,
    Item_Kind__Corn,
    Item_Kind__RESERVED_62,
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
    Item_Kind__RESERVED_63,
    Item_Kind__RESERVED_64,
    Item_Kind__RESERVED_65,
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
    Item_Kind__RESERVED_66,
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
    Item_Kind__Pile__Flower,
    Item_Kind__RESERVED_67,
    Item_Kind__RESERVED_68,
    Item_Kind__RESERVED_69,
    Item_Kind__RESERVED_70,
    Item_Kind__RESERVED_71,
    Item_Kind__RESERVED_72,
    Item_Kind__RESERVED_73,
    Item_Kind__Map__Unused,
    Item_Kind__Map,
    Item_Kind__Ink_And_Quill,
    Item_Kind__Drawing_Compass,
    Item_Kind__Ruler,
    Item_Kind__Rolling_Pin,
    Item_Kind__Saucer,
    Item_Kind__Magnifying_Glass,
    Item_Kind__RESERVED_74,
    Item_Kind__RESERVED_75,
    Item_Kind__RESERVED_76,
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
    Item_Kind__RESERVED_77,
    Item_Kind__RESERVED_78,
    Item_Kind__RESERVED_79,
    Item_Kind__RESERVED_80,
    Item_Kind__RESERVED_81,
    Item_Kind__RESERVED_82,
    Item_Kind__RESERVED_83,
    Item_Kind__RESERVED_84,
    Item_Kind__Book,
    Item_Kind__Book_Open,
    Item_Kind__RESERVED_85,
    Item_Kind__RESERVED_86,
    Item_Kind__RESERVED_87,
    Item_Kind__RESERVED_88,
    Item_Kind__RESERVED_89,
    Item_Kind__RESERVED_91,
    Item_Kind__RESERVED_92,
    Item_Kind__RESERVED_93,
    Item_Kind__RESERVED_94,
    Item_Kind__Armor__Cloth,
    Item_Kind__Armor__Iron,
    Item_Kind__Armor__Iron__Rusted,
    Item_Kind__Armor__Steel,
    Item_Kind__Armor__Steel__Order,
    Item_Kind__Armor__Steel__Chaos,
    Item_Kind__Armor__Gold,
    Item_Kind__Armor__Gold__Order,
    Item_Kind__Armor__Gold__Chaos,
    Item_Kind__RESERVED_95,
    Item_Kind__RESERVED_96,
    Item_Kind__RESERVED_97,
    Item_Kind__RESERVED_98,
    Item_Kind__RESERVED_99,
    Item_Kind__RESERVED_100,
    Item_Kind__RESERVED_101,
    Item_Kind__RESERVED_102,
    Item_Kind__RESERVED_103,
    Item_Kind__RESERVED_104,
    Item_Kind__RESERVED_105,
    Item_Kind__RESERVED_106,
    Item_Kind__RESERVED_107,
    Item_Kind__RESERVED_108,
    Item_Kind__RESERVED_109,
    Item_Kind__RESERVED_110,
    Item_Kind__RESERVED_111,
    Item_Kind__RESERVED_112,
    Item_Kind__RESERVED_113,
    Item_Kind__RESERVED_114,
    Item_Kind__RESERVED_115,
    Item_Kind__RESERVED_116,
    Item_Kind__RESERVED_117,
    Item_Kind__Door__Wood,
    Item_Kind__Door__Gold,
    Item_Kind__Door__Iron,
    Item_Kind__Door__Diamond,
    Item_Kind__Door__Amethyst,
    Item_Kind__RESERVED_118,
    Item_Kind__RESERVED_119,
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
    Item_Kind__RESERVED_139,
    Item_Kind__RESERVED_140,
    Item_Kind__RESERVED_141,
    Item_Kind__RESERVED_142,
    Item_Kind__RESERVED_143,
    Item_Kind__RESERVED_144,
    Item_Kind__RESERVED_145,
    Item_Kind__Table,
    Item_Kind__Chest,
    Item_Kind__Unknown = BIT(9)
} Item_Kind;

typedef enum Tool_Mode {
    Tool_Mode__None = 0,
    Tool_Mode__Labor,
    Tool_Mode__Labor_Secondary,
    Tool_Mode__Combat,
    Tool_Mode__Combat_Lockon,
    Tool_Mode__Unknown
} Tool_Mode;

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
typedef struct Serialization_Request_t Serialization_Request;
typedef struct Serializer_t Serializer;

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

typedef enum UI_Window_Kind {
    UI_Window_Kind__None = 0,
    UI_Window_Kind__Idle,
    UI_Window_Kind__Equip,
    UI_Window_Kind__Trade,
    UI_Window_Kind__Labor,
    UI_Window_Kind__Typer,

    UI_Window_Kind__Main_Menu,
    UI_Window_Kind__Singleplayer,
    UI_Window_Kind__Multiplayer,
    UI_Window_Kind__Settings,

    UI_Window_Kind__In_Game_Settings,
    UI_Window_Kind__Loading,
    UI_Window_Kind__Station,

    UI_Window_Kind__Unknown
} UI_Window_Kind;

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
typedef enum Tile_Kind {
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
    Tile_Kind__Unknown = MASK(10)
} Tile_Kind;

// TODO: change this to reflect new tileset
typedef enum Tile_Cover_Kind {
    Tile_Cover_Kind__None,
    Tile_Cover_Kind__Fern,
    Tile_Cover_Kind__Fern__Frame_2,
    Tile_Cover_Kind__Fern__Frame_3,
    Tile_Cover_Kind__RESERVED_0,
    Tile_Cover_Kind__Cactus,
    Tile_Cover_Kind__Sapling__Oak,
    Tile_Cover_Kind__Sapling__Pine,
    Tile_Cover_Kind__Sign,
    Tile_Cover_Kind__Grate,
    Tile_Cover_Kind__Ore__Small__Stone_1,
    Tile_Cover_Kind__Ore__Small__Stone_2,
    Tile_Cover_Kind__Ore__Small__Stone_3,
    Tile_Cover_Kind__Ore__Large__Stone_1__Top_Left,
    Tile_Cover_Kind__Ore__Large__Stone_1__Top_Right,
    Tile_Cover_Kind__Ore__Large__Stone_2__Top_Left,
    Tile_Cover_Kind__Ore__Large__Stone_2__Top_Right,
    Tile_Cover_Kind__RESERVED_1,
    Tile_Cover_Kind__RESERVED_2,
    Tile_Cover_Kind__RESERVED_3,
    Tile_Cover_Kind__RESERVED_4,
    Tile_Cover_Kind__RESERVED_5,
    Tile_Cover_Kind__RESERVED_6,
    Tile_Cover_Kind__RESERVED_7,
    Tile_Cover_Kind__RESERVED_8,
    Tile_Cover_Kind__RESERVED_9,
    Tile_Cover_Kind__RESERVED_10,
    Tile_Cover_Kind__RESERVED_11,
    Tile_Cover_Kind__RESERVED_12,
    Tile_Cover_Kind__RESERVED_13,
    Tile_Cover_Kind__RESERVED_14,
    Tile_Cover_Kind__RESERVED_15,
    Tile_Cover_Kind__RESERVED_16,
    Tile_Cover_Kind__Grass__A,
    Tile_Cover_Kind__Grass__A__Frame_2,
    Tile_Cover_Kind__Grass__A__Frame_3,
    Tile_Cover_Kind__Tree__Trunk,
    Tile_Cover_Kind__Tree__Oak__Top,
    Tile_Cover_Kind__Tree__Pine__Top,
    Tile_Cover_Kind__Cactus__Tall__Top,
    Tile_Cover_Kind__RESERVED_17,
    Tile_Cover_Kind__RESERVED_18,
    Tile_Cover_Kind__Ore__Small__Coal_1,
    Tile_Cover_Kind__Ore__Small__Coal_2,
    Tile_Cover_Kind__Ore__Small__Coal_3,
    Tile_Cover_Kind__Ore__Large__Stone_1__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Stone_1__Bottom_Right,
    Tile_Cover_Kind__Ore__Large__Stone_2__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Stone_2__Bottom_Right,
    Tile_Cover_Kind__RESERVED_19,
    Tile_Cover_Kind__RESERVED_20,
    Tile_Cover_Kind__RESERVED_21,
    Tile_Cover_Kind__RESERVED_22,
    Tile_Cover_Kind__RESERVED_23,
    Tile_Cover_Kind__RESERVED_24,
    Tile_Cover_Kind__RESERVED_25,
    Tile_Cover_Kind__RESERVED_26,
    Tile_Cover_Kind__RESERVED_27,
    Tile_Cover_Kind__RESERVED_28,
    Tile_Cover_Kind__RESERVED_29,
    Tile_Cover_Kind__RESERVED_30,
    Tile_Cover_Kind__RESERVED_31,
    Tile_Cover_Kind__RESERVED_32,
    Tile_Cover_Kind__RESERVED_33,
    Tile_Cover_Kind__RESERVED_34,
    Tile_Cover_Kind__Grass__B,
    Tile_Cover_Kind__Grass__B__Frame_2,
    Tile_Cover_Kind__Grass__B__Frame_3,
    Tile_Cover_Kind__Stump,
    Tile_Cover_Kind__Tree__Oak__Middle,
    Tile_Cover_Kind__Tree__Pine__Middle,
    Tile_Cover_Kind__Cactus__Tall__Bottom,
    Tile_Cover_Kind__RESERVED_35,
    Tile_Cover_Kind__RESERVED_36,
    Tile_Cover_Kind__Ore__Small__Gold_1,
    Tile_Cover_Kind__Ore__Small__Gold_2,
    Tile_Cover_Kind__Ore__Small__Gold_3,
    Tile_Cover_Kind__Ore__Large__Coal_1__Top_Left,
    Tile_Cover_Kind__Ore__Large__Coal_1__Top_Right,
    Tile_Cover_Kind__Ore__Large__Coal_2__Top_Left,
    Tile_Cover_Kind__Ore__Large__Coal_2__Top_Right,
    Tile_Cover_Kind__RESERVED_37,
    Tile_Cover_Kind__RESERVED_38,
    Tile_Cover_Kind__RESERVED_39,
    Tile_Cover_Kind__RESERVED_40,
    Tile_Cover_Kind__RESERVED_41,
    Tile_Cover_Kind__RESERVED_42,
    Tile_Cover_Kind__RESERVED_43,
    Tile_Cover_Kind__RESERVED_44,
    Tile_Cover_Kind__RESERVED_45,
    Tile_Cover_Kind__RESERVED_46,
    Tile_Cover_Kind__RESERVED_47,
    Tile_Cover_Kind__RESERVED_48,
    Tile_Cover_Kind__RESERVED_49,
    Tile_Cover_Kind__RESERVED_50,
    Tile_Cover_Kind__RESERVED_51,
    Tile_Cover_Kind__RESERVED_52,
    Tile_Cover_Kind__Flower_Yellow,
    Tile_Cover_Kind__Flower_Yellow__Frame_2,
    Tile_Cover_Kind__Flower_Yellow__Frame_3,
    Tile_Cover_Kind__Crop__A,
    Tile_Cover_Kind__Crop__B,
    Tile_Cover_Kind__Crop__C,
    Tile_Cover_Kind__Crop__D,
    Tile_Cover_Kind__Crop__E,
    Tile_Cover_Kind__RESERVED_53,
    Tile_Cover_Kind__Ore__Small__Iron_1,
    Tile_Cover_Kind__Ore__Small__Iron_2,
    Tile_Cover_Kind__Ore__Small__Iron_3,
    Tile_Cover_Kind__Ore__Large__Coal_1__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Coal_1__Bottom_Right,
    Tile_Cover_Kind__Ore__Large__Coal_2__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Coal_2__Bottom_Right,
    Tile_Cover_Kind__RESERVED_54,
    Tile_Cover_Kind__RESERVED_55,
    Tile_Cover_Kind__RESERVED_56,
    Tile_Cover_Kind__RESERVED_57,
    Tile_Cover_Kind__RESERVED_58,
    Tile_Cover_Kind__RESERVED_59,
    Tile_Cover_Kind__RESERVED_60,
    Tile_Cover_Kind__RESERVED_61,
    Tile_Cover_Kind__RESERVED_62,
    Tile_Cover_Kind__RESERVED_63,
    Tile_Cover_Kind__RESERVED_64,
    Tile_Cover_Kind__RESERVED_65,
    Tile_Cover_Kind__RESERVED_66,
    Tile_Cover_Kind__RESERVED_67,
    Tile_Cover_Kind__RESERVED_68,
    Tile_Cover_Kind__RESERVED_69,
    Tile_Cover_Kind__Flower_Blue,
    Tile_Cover_Kind__Flower_Blue__Frame_2,
    Tile_Cover_Kind__Flower_Blue__Frame_3,
    Tile_Cover_Kind__Crop__F,
    Tile_Cover_Kind__Crop__G,
    Tile_Cover_Kind__Crop__H,
    Tile_Cover_Kind__Crop__I,
    Tile_Cover_Kind__Crop__J,
    Tile_Cover_Kind__RESERVED_70,
    Tile_Cover_Kind__Ore__Small__Diamond_1,
    Tile_Cover_Kind__Ore__Small__Diamond_2,
    Tile_Cover_Kind__Ore__Small__Diamond_3,
    Tile_Cover_Kind__Ore__Large__Gold_1__Top_Left,
    Tile_Cover_Kind__Ore__Large__Gold_1__Top_Right,
    Tile_Cover_Kind__Ore__Large__Gold_2__Top_Left,
    Tile_Cover_Kind__Ore__Large__Gold_2__Top_Right,
    Tile_Cover_Kind__RESERVED_71,
    Tile_Cover_Kind__RESERVED_72,
    Tile_Cover_Kind__RESERVED_73,
    Tile_Cover_Kind__RESERVED_74,
    Tile_Cover_Kind__RESERVED_75,
    Tile_Cover_Kind__RESERVED_76,
    Tile_Cover_Kind__RESERVED_77,
    Tile_Cover_Kind__RESERVED_78,
    Tile_Cover_Kind__RESERVED_79,
    Tile_Cover_Kind__RESERVED_80,
    Tile_Cover_Kind__RESERVED_81,
    Tile_Cover_Kind__RESERVED_82,
    Tile_Cover_Kind__RESERVED_83,
    Tile_Cover_Kind__RESERVED_84,
    Tile_Cover_Kind__RESERVED_85,
    Tile_Cover_Kind__RESERVED_86,
    Tile_Cover_Kind__Flower_Red,
    Tile_Cover_Kind__Flower_Red__Frame_2,
    Tile_Cover_Kind__Flower_Red__Frame_3,
    Tile_Cover_Kind__Crop__K,
    Tile_Cover_Kind__Crop__L,
    Tile_Cover_Kind__Crop__M,
    Tile_Cover_Kind__Crop__N,
    Tile_Cover_Kind__Crop__O,
    Tile_Cover_Kind__RESERVED_87,
    Tile_Cover_Kind__Ore__Small__Amethyst_1,
    Tile_Cover_Kind__Ore__Small__Amethyst_2,
    Tile_Cover_Kind__Ore__Small__Amethyst_3,
    Tile_Cover_Kind__Ore__Large__Gold_1__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Gold_1__Bottom_Right,
    Tile_Cover_Kind__Ore__Large__Gold_2__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Gold_2__Bottom_Right,
    Tile_Cover_Kind__RESERVED_88,
    Tile_Cover_Kind__RESERVED_89,
    Tile_Cover_Kind__RESERVED_90,
    Tile_Cover_Kind__RESERVED_91,
    Tile_Cover_Kind__RESERVED_92,
    Tile_Cover_Kind__RESERVED_93,
    Tile_Cover_Kind__RESERVED_94,
    Tile_Cover_Kind__RESERVED_95,
    Tile_Cover_Kind__RESERVED_96,
    Tile_Cover_Kind__RESERVED_97,
    Tile_Cover_Kind__RESERVED_98,
    Tile_Cover_Kind__RESERVED_99,
    Tile_Cover_Kind__RESERVED_100,
    Tile_Cover_Kind__RESERVED_101,
    Tile_Cover_Kind__RESERVED_102,
    Tile_Cover_Kind__RESERVED_103,
    // < THRONES>
    Tile_Cover_Kind__RESERVED_104,
    Tile_Cover_Kind__RESERVED_105,
    Tile_Cover_Kind__RESERVED_106,
    Tile_Cover_Kind__RESERVED_107,
    Tile_Cover_Kind__RESERVED_108,
    Tile_Cover_Kind__RESERVED_109,
    // </THRONES>
    Tile_Cover_Kind__RESERVED_110,
    Tile_Cover_Kind__RESERVED_111,
    Tile_Cover_Kind__RESERVED_112,
    Tile_Cover_Kind__RESERVED_113,
    Tile_Cover_Kind__RESERVED_114,
    Tile_Cover_Kind__RESERVED_115,
    Tile_Cover_Kind__Ore__Large__Iron_1__Top_Left,
    Tile_Cover_Kind__Ore__Large__Iron_1__Top_Right,
    Tile_Cover_Kind__Ore__Large__Iron_2__Top_Left,
    Tile_Cover_Kind__Ore__Large__Iron_2__Top_Right,
    Tile_Cover_Kind__RESERVED_116,
    Tile_Cover_Kind__RESERVED_117,
    Tile_Cover_Kind__RESERVED_118,
    Tile_Cover_Kind__RESERVED_119,
    Tile_Cover_Kind__RESERVED_120,
    Tile_Cover_Kind__RESERVED_121,
    Tile_Cover_Kind__RESERVED_122,
    Tile_Cover_Kind__RESERVED_123,
    Tile_Cover_Kind__RESERVED_124,
    Tile_Cover_Kind__RESERVED_125,
    Tile_Cover_Kind__RESERVED_126,
    Tile_Cover_Kind__RESERVED_127,
    Tile_Cover_Kind__RESERVED_128,
    Tile_Cover_Kind__RESERVED_129,
    Tile_Cover_Kind__RESERVED_130,
    Tile_Cover_Kind__RESERVED_131,
    // < THRONES>
    Tile_Cover_Kind__RESERVED_132,
    Tile_Cover_Kind__RESERVED_133,
    Tile_Cover_Kind__RESERVED_134,
    Tile_Cover_Kind__RESERVED_135,
    Tile_Cover_Kind__RESERVED_136,
    Tile_Cover_Kind__RESERVED_137,
    // </THRONES>
    Tile_Cover_Kind__RESERVED_138,
    Tile_Cover_Kind__RESERVED_139,
    Tile_Cover_Kind__RESERVED_140,
    Tile_Cover_Kind__RESERVED_141,
    Tile_Cover_Kind__RESERVED_142,
    Tile_Cover_Kind__RESERVED_143,
    Tile_Cover_Kind__Ore__Large__Iron_1__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Iron_1__Bottom_Right,
    Tile_Cover_Kind__Ore__Large__Iron_2__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Iron_2__Bottom_Right,
    Tile_Cover_Kind__RESERVED_144,
    Tile_Cover_Kind__RESERVED_145,
    Tile_Cover_Kind__RESERVED_146,
    Tile_Cover_Kind__RESERVED_147,
    Tile_Cover_Kind__RESERVED_148,
    Tile_Cover_Kind__RESERVED_149,
    Tile_Cover_Kind__RESERVED_150,
    Tile_Cover_Kind__RESERVED_151,
    Tile_Cover_Kind__RESERVED_152,
    Tile_Cover_Kind__RESERVED_153,
    Tile_Cover_Kind__RESERVED_154,
    Tile_Cover_Kind__RESERVED_155,
    Tile_Cover_Kind__RESERVED_156,
    Tile_Cover_Kind__RESERVED_157,
    Tile_Cover_Kind__RESERVED_158,
    Tile_Cover_Kind__RESERVED_159,
    // < THRONES>
    Tile_Cover_Kind__RESERVED_160,
    Tile_Cover_Kind__RESERVED_161,
    Tile_Cover_Kind__RESERVED_162,
    Tile_Cover_Kind__RESERVED_163,
    Tile_Cover_Kind__RESERVED_164,
    Tile_Cover_Kind__RESERVED_165,
    // </THRONES>
    Tile_Cover_Kind__RESERVED_166,
    Tile_Cover_Kind__RESERVED_167,
    Tile_Cover_Kind__RESERVED_168,
    Tile_Cover_Kind__RESERVED_169,
    Tile_Cover_Kind__RESERVED_170,
    Tile_Cover_Kind__RESERVED_171,
    Tile_Cover_Kind__Ore__Large__Diamond_1__Top_Left,
    Tile_Cover_Kind__Ore__Large__Diamond_1__Top_Right,
    Tile_Cover_Kind__Ore__Large__Diamond_2__Top_Left,
    Tile_Cover_Kind__Ore__Large__Diamond_2__Top_Right,
    Tile_Cover_Kind__RESERVED_172,
    Tile_Cover_Kind__RESERVED_173,
    Tile_Cover_Kind__RESERVED_174,
    Tile_Cover_Kind__RESERVED_175,
    Tile_Cover_Kind__RESERVED_176,
    Tile_Cover_Kind__RESERVED_177,
    Tile_Cover_Kind__RESERVED_178,
    Tile_Cover_Kind__RESERVED_179,
    Tile_Cover_Kind__RESERVED_180,
    Tile_Cover_Kind__RESERVED_181,
    Tile_Cover_Kind__RESERVED_182,
    Tile_Cover_Kind__RESERVED_183,
    Tile_Cover_Kind__RESERVED_184,
    Tile_Cover_Kind__RESERVED_185,
    Tile_Cover_Kind__RESERVED_186,
    Tile_Cover_Kind__RESERVED_187,
    // < THRONES>
    Tile_Cover_Kind__RESERVED_188,
    Tile_Cover_Kind__RESERVED_189,
    Tile_Cover_Kind__RESERVED_190,
    Tile_Cover_Kind__RESERVED_191,
    Tile_Cover_Kind__RESERVED_192,
    Tile_Cover_Kind__RESERVED_193,
    // </THRONES>
    Tile_Cover_Kind__RESERVED_194,
    Tile_Cover_Kind__RESERVED_195,
    Tile_Cover_Kind__RESERVED_196,
    Tile_Cover_Kind__RESERVED_197,
    Tile_Cover_Kind__RESERVED_198,
    Tile_Cover_Kind__RESERVED_199,
    Tile_Cover_Kind__Ore__Large__Diamond_1__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Diamond_1__Bottom_Right,
    Tile_Cover_Kind__Ore__Large__Diamond_2__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Diamond_2__Bottom_Right,
    Tile_Cover_Kind__RESERVED_200,
    Tile_Cover_Kind__RESERVED_201,
    Tile_Cover_Kind__RESERVED_202,
    Tile_Cover_Kind__RESERVED_203,
    Tile_Cover_Kind__RESERVED_204,
    Tile_Cover_Kind__RESERVED_205,
    Tile_Cover_Kind__RESERVED_206,
    Tile_Cover_Kind__RESERVED_207,
    Tile_Cover_Kind__RESERVED_208,
    Tile_Cover_Kind__RESERVED_209,
    Tile_Cover_Kind__RESERVED_210,
    Tile_Cover_Kind__RESERVED_211,
    Tile_Cover_Kind__RESERVED_212,
    Tile_Cover_Kind__RESERVED_213,
    Tile_Cover_Kind__RESERVED_214,
    Tile_Cover_Kind__RESERVED_215,
    // < THRONES>
    Tile_Cover_Kind__RESERVED_216,
    Tile_Cover_Kind__RESERVED_217,
    Tile_Cover_Kind__RESERVED_218,
    Tile_Cover_Kind__RESERVED_219,
    Tile_Cover_Kind__RESERVED_220,
    Tile_Cover_Kind__RESERVED_221,
    // </THRONES>
    Tile_Cover_Kind__RESERVED_222,
    Tile_Cover_Kind__RESERVED_223,
    Tile_Cover_Kind__RESERVED_224,
    Tile_Cover_Kind__RESERVED_225,
    Tile_Cover_Kind__RESERVED_226,
    Tile_Cover_Kind__RESERVED_227,
    Tile_Cover_Kind__Ore__Large__Amethyst_1__Top_Left,
    Tile_Cover_Kind__Ore__Large__Amethyst_1__Top_Right,
    Tile_Cover_Kind__Ore__Large__Amethyst_2__Top_Left,
    Tile_Cover_Kind__Ore__Large__Amethyst_2__Top_Right,
    Tile_Cover_Kind__RESERVED_228,
    Tile_Cover_Kind__RESERVED_229,
    Tile_Cover_Kind__RESERVED_230,
    Tile_Cover_Kind__RESERVED_231,
    Tile_Cover_Kind__RESERVED_232,
    Tile_Cover_Kind__RESERVED_233,
    Tile_Cover_Kind__RESERVED_234,
    Tile_Cover_Kind__RESERVED_235,
    Tile_Cover_Kind__RESERVED_236,
    Tile_Cover_Kind__RESERVED_237,
    Tile_Cover_Kind__RESERVED_238,
    Tile_Cover_Kind__RESERVED_239,
    Tile_Cover_Kind__RESERVED_240,
    Tile_Cover_Kind__RESERVED_241,
    Tile_Cover_Kind__RESERVED_242,
    Tile_Cover_Kind__RESERVED_243,
    // < THRONES>
    Tile_Cover_Kind__RESERVED_244,
    Tile_Cover_Kind__RESERVED_245,
    Tile_Cover_Kind__RESERVED_246,
    Tile_Cover_Kind__RESERVED_247,
    Tile_Cover_Kind__RESERVED_248,
    Tile_Cover_Kind__RESERVED_249,
    // </THRONES>
    Tile_Cover_Kind__RESERVED_250,
    Tile_Cover_Kind__RESERVED_251,
    Tile_Cover_Kind__RESERVED_252,
    Tile_Cover_Kind__RESERVED_253,
    Tile_Cover_Kind__RESERVED_254,
    Tile_Cover_Kind__RESERVED_255,
    Tile_Cover_Kind__Ore__Large__Amethyst_1__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Amethyst_1__Bottom_Right,
    Tile_Cover_Kind__Ore__Large__Amethyst_2__Bottom_Left,
    Tile_Cover_Kind__Ore__Large__Amethyst_2__Bottom_Right,
    Tile_Cover_Kind__RESERVED_256,
    Tile_Cover_Kind__RESERVED_257,
    Tile_Cover_Kind__RESERVED_258,
    Tile_Cover_Kind__RESERVED_259,
    Tile_Cover_Kind__RESERVED_260,
    Tile_Cover_Kind__RESERVED_261,
    Tile_Cover_Kind__RESERVED_262,
    Tile_Cover_Kind__RESERVED_263,
    Tile_Cover_Kind__RESERVED_264,
    Tile_Cover_Kind__RESERVED_265,
    Tile_Cover_Kind__RESERVED_266,
    Tile_Cover_Kind__RESERVED_267,
    Tile_Cover_Kind__RESERVED_268,
    Tile_Cover_Kind__RESERVED_269,
    Tile_Cover_Kind__RESERVED_270,
    Tile_Cover_Kind__RESERVED_271,

    Tile_Cover_Kind__Chest__Left__Locked,
    Tile_Cover_Kind__Chest__Right__Locked,
    Tile_Cover_Kind__Chest__Single__Locked,
    Tile_Cover_Kind__Chest__Left,
    Tile_Cover_Kind__Chest__Right,
    Tile_Cover_Kind__Barrel,
    Tile_Cover_Kind__Chest__Single,
    Tile_Cover_Kind__RESERVED_272,
    Tile_Cover_Kind__RESERVED_273,
    Tile_Cover_Kind__RESERVED_274,
    Tile_Cover_Kind__RESERVED_275,
    Tile_Cover_Kind__RESERVED_276,
    Tile_Cover_Kind__RESERVED_277,
    Tile_Cover_Kind__RESERVED_278,
    Tile_Cover_Kind__RESERVED_279,
    Tile_Cover_Kind__RESERVED_280,
    // chair skip
    Tile_Cover_Kind__RESERVED_281,
    Tile_Cover_Kind__RESERVED_282,
    Tile_Cover_Kind__RESERVED_283,
    Tile_Cover_Kind__RESERVED_284,
    Tile_Cover_Kind__RESERVED_285,
    Tile_Cover_Kind__RESERVED_286,
    Tile_Cover_Kind__RESERVED_287,
    Tile_Cover_Kind__RESERVED_288,
    Tile_Cover_Kind__RESERVED_289,
    Tile_Cover_Kind__RESERVED_290,
    Tile_Cover_Kind__RESERVED_291,
    Tile_Cover_Kind__RESERVED_292,
    Tile_Cover_Kind__RESERVED_293,
    Tile_Cover_Kind__RESERVED_294,
    Tile_Cover_Kind__RESERVED_295,
    Tile_Cover_Kind__RESERVED_296,
    // row skip
    Tile_Cover_Kind__RESERVED_297,
    Tile_Cover_Kind__RESERVED_298,
    Tile_Cover_Kind__RESERVED_299,
    Tile_Cover_Kind__RESERVED_300,
    Tile_Cover_Kind__RESERVED_301,
    Tile_Cover_Kind__RESERVED_302,
    Tile_Cover_Kind__RESERVED_303,
    Tile_Cover_Kind__RESERVED_Anvil__Stone__Left,
    Tile_Cover_Kind__RESERVED_Anvil__Stone__Right,
    Tile_Cover_Kind__RESERVED_306,
    Tile_Cover_Kind__RESERVED_307,
    Tile_Cover_Kind__RESERVED_308,
    Tile_Cover_Kind__RESERVED_309,
    Tile_Cover_Kind__RESERVED_310,
    Tile_Cover_Kind__RESERVED_311,
    Tile_Cover_Kind__RESERVED_312,
    Tile_Cover_Kind__RESERVED_313,
    Tile_Cover_Kind__RESERVED_314,
    Tile_Cover_Kind__RESERVED_315,
    Tile_Cover_Kind__RESERVED_316,
    Tile_Cover_Kind__RESERVED_317,
    Tile_Cover_Kind__RESERVED_318,
    Tile_Cover_Kind__RESERVED_319,
    Tile_Cover_Kind__RESERVED_320,
    Tile_Cover_Kind__RESERVED_321,
    Tile_Cover_Kind__RESERVED_322,
    Tile_Cover_Kind__RESERVED_323,
    Tile_Cover_Kind__RESERVED_324,
    Tile_Cover_Kind__RESERVED_325,
    Tile_Cover_Kind__RESERVED_326,
    Tile_Cover_Kind__RESERVED_327,
    Tile_Cover_Kind__RESERVED_328,
    // row skip
    Tile_Cover_Kind__RESERVED_329,
    Tile_Cover_Kind__RESERVED_330,
    Tile_Cover_Kind__RESERVED_331,
    Tile_Cover_Kind__RESERVED_332,
    Tile_Cover_Kind__RESERVED_333,
    Tile_Cover_Kind__RESERVED_334,
    Tile_Cover_Kind__RESERVED_335,
    Tile_Cover_Kind__RESERVED_Anvil__Steel__Left,
    Tile_Cover_Kind__RESERVED_Anvil__Steel__Right,
    Tile_Cover_Kind__RESERVED_Table__Top__Left,
    Tile_Cover_Kind__RESERVED_Table__Top__Middle,
    Tile_Cover_Kind__RESERVED_Table__Top__Right,
    Tile_Cover_Kind__RESERVED_341,
    Tile_Cover_Kind__RESERVED_342,
    Tile_Cover_Kind__RESERVED_343,
    Tile_Cover_Kind__RESERVED_344,
    Tile_Cover_Kind__RESERVED_345,
    Tile_Cover_Kind__RESERVED_346,
    Tile_Cover_Kind__RESERVED_347,
    Tile_Cover_Kind__RESERVED_348,
    Tile_Cover_Kind__RESERVED_349,
    Tile_Cover_Kind__RESERVED_350,
    Tile_Cover_Kind__RESERVED_351,
    Tile_Cover_Kind__RESERVED_352,
    Tile_Cover_Kind__RESERVED_353,
    Tile_Cover_Kind__RESERVED_354,
    Tile_Cover_Kind__RESERVED_355,
    Tile_Cover_Kind__RESERVED_356,
    Tile_Cover_Kind__RESERVED_357,
    Tile_Cover_Kind__RESERVED_358,
    Tile_Cover_Kind__RESERVED_359,
    Tile_Cover_Kind__RESERVED_360,
    // row skip
    Tile_Cover_Kind__RESERVED_361,
    Tile_Cover_Kind__RESERVED_362,
    Tile_Cover_Kind__RESERVED_363,
    Tile_Cover_Kind__RESERVED_364,
    Tile_Cover_Kind__RESERVED_365,
    Tile_Cover_Kind__RESERVED_366,
    Tile_Cover_Kind__RESERVED_367,
    Tile_Cover_Kind__RESERVED_Anvil__Iron__Left,
    Tile_Cover_Kind__RESERVED_Anvil__Iron__Right,
    Tile_Cover_Kind__RESERVED_Table__Bottom__Left,
    Tile_Cover_Kind__RESERVED_Table__Bottom__Middle,
    Tile_Cover_Kind__RESERVED_Table__Bottom__Right,
    Tile_Cover_Kind__RESERVED_Bed__Horizontal__Left,
    Tile_Cover_Kind__RESERVED_Bed__Horizontal__Right,
    Tile_Cover_Kind__RESERVED_375,
    Tile_Cover_Kind__RESERVED_376,
    Tile_Cover_Kind__RESERVED_377,
    Tile_Cover_Kind__RESERVED_378,
    Tile_Cover_Kind__RESERVED_379,
    Tile_Cover_Kind__RESERVED_380,
    Tile_Cover_Kind__RESERVED_381,
    Tile_Cover_Kind__RESERVED_382,
    Tile_Cover_Kind__RESERVED_383,
    Tile_Cover_Kind__RESERVED_384,
    Tile_Cover_Kind__RESERVED_385,
    Tile_Cover_Kind__RESERVED_386,
    Tile_Cover_Kind__RESERVED_387,
    Tile_Cover_Kind__RESERVED_388,
    Tile_Cover_Kind__RESERVED_389,
    Tile_Cover_Kind__RESERVED_390,
    Tile_Cover_Kind__RESERVED_391,
    Tile_Cover_Kind__RESERVED_392,

    Tile_Cover_Kind__WALL               = 0b1000000001,
    Tile_Cover_Kind__Wall__Oak_Wood,
    Tile_Cover_Kind__Wall__Stone_Brick,
    Tile_Cover_Kind__Wall__Gold,
    Tile_Cover_Kind__Wall__Iron,
    Tile_Cover_Kind__Wall__Diamond,
    Tile_Cover_Kind__Wall__Amethyst,
    Tile_Cover_Kind__Wall__Sandstone,
    Tile_Cover_Kind__Wall__Stone,
    Tile_Cover_Kind__Wall__Dirt,
    Tile_Cover_Kind__Wall__Sand,
    Tile_Cover_Kind__Wall__Grass,
    Tile_Cover_Kind__Wall__Steel,
    Tile_Cover_Kind__RESERVED_WALL_0,
    Tile_Cover_Kind__RESERVED_WALL_1,
    Tile_Cover_Kind__RESERVED_WALL_2,

    Tile_Cover_Kind__RESERVED_WALL_SKIP_0 = 
        Tile_Cover_Kind__WALL
        + (1*32 + 16),
    Tile_Cover_Kind__Door__Horizontal__Wood,
    Tile_Cover_Kind__Door__Horizontal__Stone_Brick,
    Tile_Cover_Kind__Door__Horizontal__Gold,
    Tile_Cover_Kind__Door__Horizontal__Iron,
    Tile_Cover_Kind__Door__Horizontal__Diamond,
    Tile_Cover_Kind__Door__Horizontal__Amethyst,
    Tile_Cover_Kind__Door__Horizontal__Sandstone,
    Tile_Cover_Kind__Door__Horizontal__Stone,
    Tile_Cover_Kind__Door__Horizontal__Dirt,
    Tile_Cover_Kind__Door__Horizontal__Sand,
    Tile_Cover_Kind__Door__Horizontal__Grass,
    Tile_Cover_Kind__Door__Horizontal__Steel,

    Tile_Cover_Kind__RESERVED_WALL_SKIP_1 = 
        Tile_Cover_Kind__WALL
        + (4*32 + 16),
    Tile_Cover_Kind__Door__Horizontal__Open__Wood,
    Tile_Cover_Kind__Door__Horizontal__Open__Stone_Brick,
    Tile_Cover_Kind__Door__Horizontal__Open__Gold,
    Tile_Cover_Kind__Door__Horizontal__Open__Iron,
    Tile_Cover_Kind__Door__Horizontal__Open__Diamond,
    Tile_Cover_Kind__Door__Horizontal__Open__Amethyst,
    Tile_Cover_Kind__Door__Horizontal__Open__Sandstone,
    Tile_Cover_Kind__Door__Horizontal__Open__Stone,
    Tile_Cover_Kind__Door__Horizontal__Open__Dirt,
    Tile_Cover_Kind__Door__Horizontal__Open__Sand,
    Tile_Cover_Kind__Door__Horizontal__Open__Grass,
    Tile_Cover_Kind__Door__Horizontal__Open__Steel,

    Tile_Cover_Kind__RESERVED_WALL_SKIP_2 = 
        Tile_Cover_Kind__WALL
        + (5*32 + 16),
    Tile_Cover_Kind__Door__Vertical__Wood,
    Tile_Cover_Kind__Door__Vertical__Stone_Brick,
    Tile_Cover_Kind__Door__Vertical__Gold,
    Tile_Cover_Kind__Door__Vertical__Iron,
    Tile_Cover_Kind__Door__Vertical__Diamond,
    Tile_Cover_Kind__Door__Vertical__Amethyst,
    Tile_Cover_Kind__Door__Vertical__Sandstone,
    Tile_Cover_Kind__Door__Vertical__Stone,
    Tile_Cover_Kind__Door__Vertical__Dirt,
    Tile_Cover_Kind__Door__Vertical__Sand,
    Tile_Cover_Kind__Door__Vertical__Grass,
    Tile_Cover_Kind__Door__Vertical__Steel,

    Tile_Cover_Kind__RESERVED_WALL_SKIP_3 = 
        Tile_Cover_Kind__WALL
        + (6*32 + 16),
    Tile_Cover_Kind__Door__Vertical__Open__Wood,
    Tile_Cover_Kind__Door__Vertical__Open__Stone_Brick,
    Tile_Cover_Kind__Door__Vertical__Open__Gold,
    Tile_Cover_Kind__Door__Vertical__Open__Iron,
    Tile_Cover_Kind__Door__Vertical__Open__Diamond,
    Tile_Cover_Kind__Door__Vertical__Open__Amethyst,
    Tile_Cover_Kind__Door__Vertical__Open__Sandstone,
    Tile_Cover_Kind__Door__Vertical__Open__Stone,
    Tile_Cover_Kind__Door__Vertical__Open__Dirt,
    Tile_Cover_Kind__Door__Vertical__Open__Sand,
    Tile_Cover_Kind__Door__Vertical__Open__Grass,
    Tile_Cover_Kind__Door__Vertical__Open__Steel,

    Tile_Cover_Kind__RESERVED_WALL_SKIP_4 = 
        Tile_Cover_Kind__WALL
        + (9*32 + 16),
    Tile_Cover_Kind__Window__Vertical__Wood,
    Tile_Cover_Kind__Window__Vertical__Stone_Brick,
    Tile_Cover_Kind__Window__Vertical__Gold,
    Tile_Cover_Kind__Window__Vertical__Iron,
    Tile_Cover_Kind__Window__Vertical__Diamond,
    Tile_Cover_Kind__Window__Vertical__Amethyst,
    Tile_Cover_Kind__Window__Vertical__Sandstone,
    Tile_Cover_Kind__Window__Vertical__Stone,
    Tile_Cover_Kind__Window__Vertical__Dirt,
    Tile_Cover_Kind__Window__Vertical__Sand,
    Tile_Cover_Kind__Window__Vertical__Grass,
    Tile_Cover_Kind__Window__Vertical__Steel,

    // LOGICAL  These Tile_Cover_Kinds don't correspond to a unique tile.
    //          They all overlap with another LOGICIAL tile cover.
    Tile_Cover_Kind__LOGICAL            = 0b1100000000,
    Tile_Cover_Kind__Crop_Wheat_A       = 0b1100000000,
    Tile_Cover_Kind__Crop_Wheat_B,
    Tile_Cover_Kind__Crop_Wheat_C,
    Tile_Cover_Kind__Crop_Corn_A,
    Tile_Cover_Kind__Crop_Corn_B,
    Tile_Cover_Kind__Crop_Corn_C,
    Tile_Cover_Kind__Crop_Pumpkin_A,
    Tile_Cover_Kind__Crop_Pumpkin_B,
    Tile_Cover_Kind__Crop_Pumpkin_C,
    Tile_Cover_Kind__Crop_Watermelon_A,
    Tile_Cover_Kind__Crop_Watermelon_B,
    Tile_Cover_Kind__Crop_Watermelon_C,
    Tile_Cover_Kind__Crop_Onion_A,
    Tile_Cover_Kind__Crop_Onion_B,
    Tile_Cover_Kind__Crop_Onion_C,
    Tile_Cover_Kind__Crop_Tomato_A,
    Tile_Cover_Kind__Crop_Tomato_B,
    Tile_Cover_Kind__Crop_Tomato_C,

    Tile_Cover_Kind__Tree__Oak,
    Tile_Cover_Kind__Tree__Pine,

    Tile_Cover_Kind__Unknown            = BIT(10)-1
} Tile_Cover_Kind;

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
typedef struct Chunk_Manager__Chunk_Map_Node_t Chunk_Manager__Chunk_Map_Node;
typedef struct Tile_t Tile;

///
/// SECTION_core
///

typedef struct Game_t Game;
typedef struct Game_Action_t Game_Action;

///
/// SECTION_platform
///

typedef struct PLATFORM_File_System_Context_t PLATFORM_File_System_Context;
typedef struct PLATFORM_Audio_Context_t PLATFORM_Audio_Context;
typedef struct PLATFORM_Gfx_Context_t PLATFORM_Gfx_Context;
typedef struct PLATFORM_Texture_t PLATFORM_Texture;
typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;

#endif
