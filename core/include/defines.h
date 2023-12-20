#ifndef DEFINES_H
#define DEFINES_H

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

typedef struct Sprite_t Sprite;
typedef struct Texture_t Texture;

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
