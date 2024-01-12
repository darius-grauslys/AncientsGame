#ifndef DEFINES_H
#define DEFINES_H

/*
 *
 * The following comes from platform_defines.h:
 * - RenderTarget
 * - PLATFORM_Sprite
 *
 * */
#include <platform_defines.h>
#include <stdint.h>

#ifndef PLATFORM_DEFINES_H
#error Cannot build AncientsGame without a backend implementation.
#endif

typedef struct Console_t Console;

typedef struct World_t World;

typedef struct Entity_t Entity;
typedef void (*m_init_entity)(Entity* self, World* world);
typedef void (*m_update_entity)(Entity* self, World* world);
typedef void (*m_render_entity)(Entity* self, World* world);
typedef void (*m_dispose_entity)(Entity* self, World* world);

typedef struct Entity_Manager_t Entity_Manager;

typedef struct Item_t Item;
typedef void (*m_item_use)(Item* self, Entity* user, World* world);
typedef void (*m_item_equip)(Item *self, Entity* user, World* world);
typedef void (*m_item_unequip)(Item *self, Entity* user, World* world);

typedef struct Inventory_t Inventory;

typedef unsigned short USER_ID;

typedef struct Game_t Game;

typedef struct Scene_t Scene;
typedef void (*m_load_scene)(Game* game, Scene* this_scene);
typedef void (*m_update_scene)(Game* game, Scene* this_scene);
typedef void (*m_render_scene)(Game* game, Scene* this_scene);
typedef void (*m_unload_scene)(Game* game, Scene* this_scene);

#define TILE_PIXEL_HEIGHT 8
#define TILE_PIXEL_WIDTH 8

#define TILE_SHEET_PIXEL_WIDTH 256
#define TILE_SHEET_PIXEL_HEIGHT 256

#define QUANTITY_OF_TILES__IN_TILE_SHEET_ROW (TILE_SHEET_PIXEL_WIDTH / TILE_PIXEL_WIDTH)

#define TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR 3
#define TILE_FLAGS__BIT_SHIFT_IS_STAIR_UP_OR_DOWN 4
#define TILE_FLAGS__BIT_SHIFT_IS_STAIR 5
#define TILE_FLAGS__BIT_SHIFT_IS_SIGHT_BLOCKING 6
#define TILE_FLAGS__BIT_SHIFT_IS_PASSABLE 7

#define TILE_FLAGS__MASK_STAIR_VALUE ((1<<\
            TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR) - 1)
#define TILE_FLAGS__BIT_INVERTED_STAIR (1<<\
        TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR)
#define TILE_FLAGS__BIT_IS_STAIR_UP_OR_DOWN (1<<\
        TILE_FLAGS__BIT_SHIFT_IS_STAIR_UP_OR_DOWN)
#define TILE_FLAGS__BIT_IS_STAIR (1<<\
        TILE_FLAGS__BIT_SHIFT_IS_STAIR)
#define TILE_FLAGS__BIT_IS_SIGHT_BLOCKING (1<<\
        TILE_FLAGS__BIT_SHIFT_IS_SIGHT_BLOCKING)
#define TILE_FLAGS__BIT_IS_PASSABLE (1<<\
        TILE_FLAGS__BIT_SHIFT_IS_PASSABLE)

#define TILE_FLAGS__NONE 0

#define TILE_SHEET_INDEX__WOOD 0
#define TILE_SHEET_INDEX__STONE_BRICK 1
#define TILE_SHEET_INDEX__GOLD 2
#define TILE_SHEET_INDEX__IRON 3
#define TILE_SHEET_INDEX__DIAMOND 4
#define TILE_SHEET_INDEX__AMEYTHYST 5
#define TILE_SHEET_INDEX__SANDSTONE 6
#define TILE_SHEET_INDEX__STONE 7
#define TILE_SHEET_INDEX__DIRT 8
#define TILE_SHEET_INDEX__SAND 9
#define TILE_SHEET_INDEX__GRASS 10
#define TILE_SHEET_INDEX__LEAVES 11
#define TILE_SHEET_INDEX__SNOW 12

typedef struct Tile_t Tile;

enum Tile_Kind {
    Tile_Kind__Void,
    Tile_Kind__Grass,
    Tile_Kind__Dirt,
    Tile_Kind__Sand,
    Tile_Kind__Oak_Wood,
    Tile_Kind__Stone,
    Tile_Kind__Stone_Brick,
    Tile_Kind__Iron,
    Tile_Kind__Gold,
    Tile_Kind__Diamond,
    Tile_Kind__Amethyst,
    Tile_Kind__Sandstone,
};

enum Tile_Cover_Kind {
    Tile_Cover_Kind__None,
    Tile_Cover_Kind__Flower,
    Tile_Cover_Kind__Cactus,
    Tile_Cover_Kind__Oak_Trunk,
    Tile_Cover_Kind__Oak_Root,
    Tile_Cover_Kind__Oak_Branch,
    Tile_Cover_Kind__Oak_Leaves,
    Tile_Cover_Kind__Leaf_Clutter,
};

enum Direction {
    Direction__North,
    Direction__North_East,
    Direction__East,
    Direction__South_East,
    Direction__South,
    Direction__South_West,
    Direction__West,
    Direction__North_West
};

enum Entity_Kind {
    Entity_Kind__Particle,
    Entity_Kind__Item,
    Entity_Kind__Player,
    Entity_Kind__Skeleton,
    Entity_Kind__Zombie
};

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

typedef struct Armor_Properties_t {
    enum Entity_Armor_Kind                  
        the_kind_of_armor__this_armor_is;
    enum Entity_Armor_Modification_Kind     
        the_kind_of_modification__this_armor_has;
} Armor_Properties;

enum Sprite_Animation_Kind {
    Sprite_Animation_Kind__Idle,
    Sprite_Animation_Kind__Humanoid__Walk,
    Sprite_Animation_Kind__Humanoid__Use,
    Sprite_Animation_Kind__Humanoid__Hurt,
    Sprite_Animation_Kind__Humanoid__Die,
    Sprite_Animation_Kind__Player__Sleep,
};

typedef struct Sprite_Wrapper_t {
    PLATFORM_Sprite sprite;
    enum Direction direction;
    enum Sprite_Animation_Kind the_kind_of_animation__this_sprite_has;
    uint32_t frame;
    uint32_t x, y;
} Sprite_Wrapper;

#define SPRITE_FRAME__16x16__OFFSET (16 * 16)

#define SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED 16
#define SPRITE_FRAME_HEIGHT__ENTITY_HUMANOID_ARMORED 16

#define SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_UNARMORED 6
#define SPRITE_FRAME_HEIGHT__ENTITY_HUMANOID_UNARMORED 4

#define SPRITE_FRAME_COL__ENTITY_HUMANOID__IDLE 0
#define SPRITE_FRAME_COL__ENTITY_HUMANOID__WALK 1
#define SPRITE_FRAME_COL__ENTITY_HUMANOID__USE 3
#define SPRITE_FRAME_COL__ENTITY_HUMANOID__HURT 0
#define SPRITE_FRAME_COL__ENTITY_HUMANOID__DIE 1
#define SPRITE_FRAME_COL__ENTITY_HUMANOID__SLEEP 3

#define SPRITE_FRAME_ROW__ENTITY_HUMANOID__SIDE_FACING 0
#define SPRITE_FRAME_ROW__ENTITY_HUMANOID__FORWARD_FACING 1
#define SPRITE_FRAME_ROW__ENTITY_HUMANOID__BACK_FACING 2
#define SPRITE_FRAME_ROW__ENTITY_HUMANOID__FALLING 3

#define SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID 6
#define SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID 4

#define SPRITE_FRAME_COL__ENTITY_HUMANOID__ARMORED__LAST_COL 15
#define SPRITE_FRAME_ROW__ENTITY_HUMANOID__ARMORED__LAST_ROW 15

#define SPRITE_FRAME_COL__ENTITY_HUMANOID__UNARMORED__LAST_COL 5
#define SPRITE_FRAME_ROW__ENTITY_HUMANOID__UNARMORED__LAST_ROW 3

#define SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH 0
#define SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH 1
#define SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON 0
#define SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON 2
#define SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD 0
#define SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD 3

#define SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_DIAMOND 1
#define SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_DIAMOND 0
#define SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_DIAMOND 1
#define SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_DIAMOND 1

#define SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_AMETHYST 1
#define SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_AMETHYST 2
#define SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_AMETHYST 1
#define SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_AMETHYST 3

///
/// The meaning of these flags is dependent on
/// platform_defines.h
///
typedef uint32_t Texture_Flags;

#define TEXTURE_FLAGS__NONE 0

///
/// The following are platform specific.
/// As a result, anything defined in core will
/// treat them as opaque pointers.
///

///
/// The reason Chunk is platform specific is for
/// memory constraints and performance of a given platform.
///
/// For Desktop_PC, we can see this being 8, 16, or even 32, etc.
/// However for the NDS we might want to keep this to 8.
/// Then, for more restricted platforms we may want to even drop down
/// to just 4!
///

typedef struct Chunk_t Chunk;
typedef struct Chunk_Manager_t Chunk_Manager;

#endif
