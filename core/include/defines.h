#ifndef DEFINES_H
#define DEFINES_H

#include <platform_defines.h>

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
    North,
    North_East,
    East,
    South_East,
    South,
    South_West,
    West,
    North_West
};

///
/// The following are platform specific.
/// As a result, anything defined in core will
/// treat them as opaque pointers.
///

typedef void* TextureAtlas;
typedef void* RenderTarget;

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
