#ifndef DEFINES_H
#define DEFINES_H

typedef struct PLATFORM_Gfx_Context_t PLATFORM_Gfx_Context;
typedef struct PLATFORM_Texture_t PLATFORM_Texture_t;
typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;

/*
 *
 * The following comes from platform_defines.h:
 * - PLATFORM_Gfx_Context
 * - PLATFORM_Sprite
 *
 * */
#include <platform_defines.h>

#include <stdint.h>
#include <stdbool.h>

#ifndef PLATFORM__CHUNKS
#define GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS 4
#define GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS 3

#define CHUNK_WIDTH__IN_TILES 8
#define CHUNK_DEPTH__IN_TILES 1

#define CHUNK_QUANTITY_OF__TILES \
    (CHUNK_WIDTH__IN_TILES * CHUNK_WIDTH__IN_TILES)

#define CHUNK__WIDTH_BIT_SHIFT 3
#define CHUNK__HEIGHT_BIT_SHIFT 3
#define CHUNK__DEPTH_BIT_SHIFT (CHUNK__WIDTH_BIT_SHIFT + CHUNK__HEIGHT_BIT_SHIFT)

#define CHUNK__WIDTH (1 << CHUNK__WIDTH_BIT_SHIFT)
#define CHUNK__HEIGHT (1 << CHUNK__HEIGHT_BIT_SHIFT)
// depth is 1 until AFTER the adventure update.
#define CHUNK__DEPTH (1)

#define CHUNK__QUANTITY_OF_TILES (CHUNK__WIDTH * \
        CHUNK__HEIGHT * CHUNK__DEPTH)

///
/// Note, both  CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
/// and         CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS
///
/// must equal one another. These two only exist to remind
/// the programmer if we are moving along COLS or ROWS.
///
/// That also means YOU should use these appropriately.
///
#define CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 8
#define CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS 8
#define CHUNK_MANAGER__QUANTITY_OF_CHUNKS \
    (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS \
    * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
#endif

///
/// This is to only be called during
/// initalization, since layer_one
/// (x/y)__center_chunk is
/// CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2.
///
/// Most north west collision node is:
///     x__chunk == 0
///     y__chunk == 0
///
/// In otherwords, we don't need to do
/// any modulus to obtain a bounded index
/// of [0, CHUNK_MANAGER__QUANTITY_OF_CHUNKS - 1]
///
static uint32_t inline get_chunk_index_during__initialization(
    int32_t x__chunk, int32_t y__chunk) {
    x__chunk = x__chunk % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
    y__chunk = y__chunk % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
    if (x__chunk < 0) {
        x__chunk = (x__chunk + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
            % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
    }
    if (y__chunk < 0) {
        y__chunk = (y__chunk + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS)
            % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
    }
    return (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - y__chunk - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + x__chunk
        ;
}

#ifndef PLATFORM__ENTITIES
#define ENTITY_MAXIMUM_QUANTITY_OF 128
#define ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS 8
#define ENTITY_MAXIMUM_QUANTITY_OF__NPCS 48
#define ENTITY_MAXIMUM_QUANTITY_OF__PROJECTILES 72
#endif

#define ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE \
    (ENTITY_MAXIMUM_QUANTITY_OF__NPCS \
    + ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS)

#ifndef PLATFORM_DEFINES_H
#error Cannot build AncientsGame without a backend implementation.
#endif

typedef struct Console_t Console;
typedef struct Game_t Game;

typedef uint8_t Direction;

#define DIRECTION__NONE 0
#define DIRECTION__NORTH 1
#define DIRECTION__EAST (1 << 1)
#define DIRECTION__SOUTH (1 << 2)
#define DIRECTION__WEST (1 << 3)

#define DIRECTION__ANY ((1 << 4) - 1)
#define DIRECTION__NORTH_EAST (DIRECTION__NORTH \
        | DIRECTION__EAST)
#define DIRECTION__NORTH_WEST (DIRECTION__NORTH \
        | DIRECTION__WEST)
#define DIRECTION__SOUTH_EAST (DIRECTION__SOUTH \
        | DIRECTION__EAST)
#define DIRECTION__SOUTH_WEST (DIRECTION__SOUTH \
        | DIRECTION__WEST)

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
    Direction direction;
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

typedef struct Entity_t Entity;

typedef struct Item_t Item;
typedef void (*m_item_use)    (Item* self, Entity* user, Game* game);
typedef void (*m_item_equip)  (Item *self, Entity* user, Game* game);
typedef void (*m_item_unequip)(Item *self, Entity* user, Game* game);

typedef struct Inventory_t Inventory;

typedef void (*m_dispose_entity)    (Entity *this_entity, Game *game);
typedef void (*m_entity_controller) (Entity *this_entity, Game *game);

///
/// callee_data is an opaque pointer to whatever
/// data the user of this function pointer needs
/// passed in addition to collided entities.
///
typedef void (*m_entity_collision)  (Entity *entity_collision_source,
        Entity *entity_collided,
        Direction direction_of_collision);

///
/// Here we define the entity super struct. It has everything we could need
/// for an entity, even if some of the things are not used.
///

#define ENTITY_FLAG__NONE 0
#define ENTITY_FLAG__IS_ENABLED (1)
#define ENTITY_FLAG__IS_NOT_UPDATING_POSITION \
    (ENTITY_FLAG__IS_ENABLED << 1)
#define ENTITY_FLAG__IS_NOT_UPDATING_GRAPHICS \
    (ENTITY_FLAG__IS_NOT_UPDATING_POSITION << 1)
#define ENTITY_FLAG__IS_COLLIDING \
    (ENTITY_FLAG__IS_NOT_UPDATING_GRAPHICS << 1)
#define ENTITY_FLAG__IS_UNLOADED \
    (ENTITY_FLAG__IS_COLLIDING << 1)
#define ENTITY_FLAG__IS_HIDDEN \
    (ENTITY_FLAG__IS_UNLOADED << 1)

typedef struct Hitbox_Point_t {
    int32_t x, y, z;
} Hitbox_Point;

typedef struct Hitbox_AABB_t {
    uint32_t width;
    uint32_t length;
    // We don't have a z-axis height.
    // Why? Because even thought the world
    // is 3D, everyone is made out of paper
    // in this video game.
    //
    // Entities can't co-exist in the same tile
    // but they can stand on top of one in an
    // above tile.
    int32_t x__chunk, y__chunk, z__chunk;
    int32_t x, y, z;
    int32_t x__velocity, y__velocity, z__velocity;
} Hitbox_AABB;

typedef struct Entity_t {
    Sprite_Wrapper          sprite_wrapper;

    // DO NOT INVOKE! Called automatically in release_entity(...)
    m_dispose_entity            dispose_handler;
    // DO NOT INVOKE! Called automatically
    m_entity_controller         controller_handler;
    // DO NOT INVOKE! Called automatically
    m_entity_collision          collision_handler;

    Hitbox_AABB hitbox;

    uint32_t                entity_flags;

    enum Entity_Kind        the_kind_of_entity__this_entity_is;
    union {
        Armor_Properties    armor_properties;
    };
} Entity;

#define ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE 6
#define ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE 4
#define ENTITY_CHUNK_FRACTIONAL__BIT_SIZE \
    (ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE \
     + ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE)

#define ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK ((1 << 6) -1)

// 1.5 pixels.
#define ENTITY_VELOCITY__PLAYER          0b1100
#define ENTITY_VELOCITY__PLAYER_DIAGONAL 0b1001

typedef struct Entity_Manager_t {
    Entity entities[ENTITY_MAXIMUM_QUANTITY_OF];
    Entity *local_player;
    uint32_t entity_count;
} Entity_Manager;

#define COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET \
    (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4)
#define COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET \
    (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8)

///
/// This type is specific to Collision_Manager,
/// so there is no header files supporting it.
///
typedef struct Collision_Manager__Collision_Node_t {
    Entity *entity_ptrs[ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE];

    struct Collision_Manager__Collision_Node_t *collision_node__north;
    struct Collision_Manager__Collision_Node_t *collision_node__east;
    struct Collision_Manager__Collision_Node_t *collision_node__south;
    struct Collision_Manager__Collision_Node_t *collision_node__west;

    Direction legal_directions;
} Collision_Manager__Collision_Node;

///
/// 4 Collision Nodes per layer 3 node.
///
typedef struct Collision_Manager__Layer_Three_t {
    Collision_Manager__Collision_Node *collision_node__top_left;
    Collision_Manager__Collision_Node *collision_node__top_right;
    Collision_Manager__Collision_Node *collision_node__bottom_left;
    Collision_Manager__Collision_Node *collision_node__bottom_right;

    int32_t x__center_chunk, y__center_chunk;
} Collision_Manager__Layer_Three;

typedef struct Collision_Manager__Layer_Two_t {
    Collision_Manager__Layer_Three layer_three__top_left;
    Collision_Manager__Layer_Three layer_three__top_right;
    Collision_Manager__Layer_Three layer_three__bottom_left;
    Collision_Manager__Layer_Three layer_three__bottom_right;

    int32_t x__center_chunk, y__center_chunk;
} Collision_Manager__Layer_Two;

typedef struct Collision_Manager__t {
    Collision_Manager__Collision_Node collision_nodes[
        CHUNK_MANAGER__QUANTITY_OF_CHUNKS];

    Collision_Manager__Layer_Two layer_two__top_left;
    Collision_Manager__Layer_Two layer_two__top_right;
    Collision_Manager__Layer_Two layer_two__bottom_left;
    Collision_Manager__Layer_Two layer_two__bottom_right;

    Collision_Manager__Collision_Node *most_north_western__node;

    int32_t x__center_chunk, y__center_chunk;
} Collision_Manager;

typedef struct Game_t Game;

typedef struct Scene_t Scene;
typedef void (*m_load_scene)  (Scene *this_scene, Game* game);
typedef void (*m_update_scene)(Scene *this_scene, Game* game);
typedef void (*m_render_scene)(Scene *this_scene, Game* game);
typedef void (*m_unload_scene)(Scene *this_scene, Game* game);

#define TILE_PIXEL_HEIGHT 8
#define TILE_PIXEL_WIDTH 8

#define TILE_PIXEL_WIDTH__BIT_SIZE 3

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
#define TILE_SHEET_INDEX__WATER 257

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
    Tile_Kind__Water,
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

enum Tile_Structure_Kind {
    Tile_Structure_Kind__None,
    Tile_Structure_Kind__Floor,
    Tile_Structure_Kind__Stair_Ascending,
    Tile_Structure_Kind__Stair_Descending,
    Tile_Structure_Kind__Wall,
    Tile_Structure_Kind__Window,
};

///
/// INPUT
///

#define INPUT_NONE 0
#define INPUT_FORWARD (1<<0)
#define INPUT_LEFT (INPUT_FORWARD<<1)
#define INPUT_RIGHT (INPUT_LEFT<<1)
#define INPUT_BACKWARDS (INPUT_RIGHT<<1)

#define INPUT_GAME_SETTINGS (INPUT_BACKWARDS<<1)
#define INPUT_INVENTORY (INPUT_GAME_SETTINGS<<1)
#define INPUT_USE (INPUT_INVENTORY<<1)

typedef struct Input_t {
    uint32_t input_flags;
} Input;

///
/// WORLD
///

typedef struct Tile_t {
    enum Tile_Kind                  the_kind_of_tile__this_tile_is;
    union {
        enum Tile_Cover_Kind        the_kind_of_tile_cover__this_tile_has;
        enum Tile_Structure_Kind    the_kind_of_tile_structure__this_tile_is;
        union {
            Direction               direction_of_structure;
        };
    };
    uint8_t flags;
    // bits 1 2 3, stair direction (values 0-7)
    // bit 4, is the stair inverted
    // bit 5, is the stair going up or down
    // bit 6, is this a stair
    // bit 7, is sight blocking
    // bit 8, is passable
} Tile;

typedef struct World_Parameters_t World_Parameters;
typedef struct Chunk_t Chunk;

typedef void (*Chunk_Generator_f)(
        World_Parameters *world_params,
        Chunk *chunk);

typedef struct World_Parameters_t {
    Chunk_Generator_f chunk_generator_f;
    uint32_t seed__initial;
    uint32_t seed__current_random;
} World_Parameters;

typedef struct Chunk_t {
    Tile tiles[CHUNK__WIDTH * CHUNK__HEIGHT * CHUNK__DEPTH];
    int32_t x, y;
    bool is_available;
} Chunk;

typedef struct Chunk_Manager__Chunk_Map_Node_t {
    Chunk *chunk__here;
    struct Chunk_Manager__Chunk_Map_Node_t *chunk_map_node__north;
    struct Chunk_Manager__Chunk_Map_Node_t *chunk_map_node__east;
    struct Chunk_Manager__Chunk_Map_Node_t *chunk_map_node__south;
    struct Chunk_Manager__Chunk_Map_Node_t *chunk_map_node__west;
} Chunk_Manager__Chunk_Map_Node;

typedef Chunk_Manager__Chunk_Map_Node
    Chunk_Manager__Chunk_Map[CHUNK_MANAGER__QUANTITY_OF_CHUNKS];

typedef struct Chunk_Manager_t {
    Chunk chunks[CHUNK_MANAGER__QUANTITY_OF_CHUNKS];
    Chunk_Manager__Chunk_Map chunk_map;
    
    Chunk_Manager__Chunk_Map_Node *chunk_map_node__that_the_player_is_on;
    Chunk_Manager__Chunk_Map_Node *chunk_map_node__most_north_western;
    Chunk_Manager__Chunk_Map_Node *chunk_map_node__most_south_eastern;
    Chunk_Manager__Chunk_Map_Node *chunk_map_node__most_north_eastern;
    Chunk_Manager__Chunk_Map_Node *chunk_map_node__most_south_western;

    int32_t x__center_chunk, y__center_chunk;
} Chunk_Manager;

///
/// The meaning of these flags is dependent on
/// platform_defines.h
///
typedef uint32_t Texture_Flags;

#define TEXTURE_FLAGS__NONE 0

///
/// TEXTURE_FLAGS:
/// Bit orderings, from most significant to least:
/// [31 <-> 10, PLATFORM specific flags]
/// [1 bit, is hidden]
/// [3 bits, render method] 
/// [3 bits, width] 
/// [3 bits, height]
///

// Just a width or height component of an image.
#define TEXTURE_FLAG__LENGTH__BIT_COUNT 3
#define TEXTURE_FLAG__LENGTH__MASK 0b111
// The width and height component of the image
#define TEXTURE_FLAG__SIZE__BIT_COUNT 6
#define TEXTURE_FLAG__SIZE__MASK 0b111111

// Texture length specifiers
#define TEXTURE_FLAG__LENGTH_x8   0b000
#define TEXTURE_FLAG__LENGTH_x16  0b001
#define TEXTURE_FLAG__LENGTH_x32  0b010
#define TEXTURE_FLAG__LENGTH_x64  0b011
#define TEXTURE_FLAG__LENGTH_x128 0b100
#define TEXTURE_FLAG__LENGTH_x256 0b101

// Texture size specifiers
// Add these combinations in as needed:
#define TEXTURE_FLAG__SIZE_8x8 \
    TEXTURE_FLAG__LENGTH_x8 \
    | (TEXTURE_FLAG__LENGTH_x8 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_8x16 \
    TEXTURE_FLAG__LENGTH_x8 \
    | (TEXTURE_FLAG__LENGTH_x16 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_8x32 \
    TEXTURE_FLAG__LENGTH_x8 \
    | (TEXTURE_FLAG__LENGTH_x32 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_16x8 \
    TEXTURE_FLAG__LENGTH_x16 \
    | (TEXTURE_FLAG__LENGTH_x8 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_16x16 \
    TEXTURE_FLAG__LENGTH_x16 \
    | (TEXTURE_FLAG__LENGTH_x16 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_16x32 \
    TEXTURE_FLAG__LENGTH_x8 \
    | (TEXTURE_FLAG__LENGTH_x32 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_32x8 \
    TEXTURE_FLAG__LENGTH_x32 \
    | (TEXTURE_FLAG__LENGTH_x8 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_32x16 \
    TEXTURE_FLAG__LENGTH_x32 \
    | (TEXTURE_FLAG__LENGTH_x16 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_32x32 \
    TEXTURE_FLAG__LENGTH_x32 \
    | (TEXTURE_FLAG__LENGTH_x32 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_32x64 \
    TEXTURE_FLAG__LENGTH_x32 \
    | (TEXTURE_FLAG__LENGTH_x64 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_64x64 \
    TEXTURE_FLAG__LENGTH_x64 \
    | (TEXTURE_FLAG__LENGTH_x64 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_128x128 \
    TEXTURE_FLAG__LENGTH_x128 \
    | (TEXTURE_FLAG__LENGTH_x128 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)
#define TEXTURE_FLAG__SIZE_256x256 \
    TEXTURE_FLAG__LENGTH_x256 \
    | (TEXTURE_FLAG__LENGTH_x256 << \
            TEXTURE_FLAG__LENGTH__BIT_COUNT)

// We support up to 8 texture render methods 
// (on nds, this is oamMain, oamSub)
#define TEXTURE_FLAG__RENDER_METHOD__BIT_COUNT 3
#define TEXTURE_FLAG__RENDER_METHOD__MASK 0b111
#define TEXTURE_FLAG__RENDER_METHOD__0 0b000
#define TEXTURE_FLAG__RENDER_METHOD__1 0b001
#define TEXTURE_FLAG__RENDER_METHOD__2 0b010
#define TEXTURE_FLAG__RENDER_METHOD__3 0b011
#define TEXTURE_FLAG__RENDER_METHOD__4 0b100
#define TEXTURE_FLAG__RENDER_METHOD__5 0b101
#define TEXTURE_FLAG__RENDER_METHOD__6 0b110
#define TEXTURE_FLAG__RENDER_METHOD__7 0b111

// We support up to 8 texture formats 
// Replace 1-7 as needed.
#define TEXTURE_FLAG__FORMAT__BIT_COUNT 3
#define TEXTURE_FLAG__FORMAT__MASK 0b111
#define TEXTURE_FLAG__FORMAT__15_RGB 0b000
#define TEXTURE_FLAG__FORMAT__1 0b001
#define TEXTURE_FLAG__FORMAT__2 0b010
#define TEXTURE_FLAG__FORMAT__3 0b011
#define TEXTURE_FLAG__FORMAT__4 0b100
#define TEXTURE_FLAG__FORMAT__5 0b101
#define TEXTURE_FLAG__FORMAT__6 0b110
#define TEXTURE_FLAG__FORMAT__7 0b111

#define TEXTURE_FLAG__IS_HIDDEN \
    (1 << (TEXTURE_FLAG__RENDER_METHOD__BIT_COUNT \
           + TEXTURE_FLAG__SIZE__BIT_COUNT \
           + TEXTURE_FLAG__FORMAT__BIT_COUNT))

#define GET_TEXTURE_FLAG__LENGTH__WIDTH(flags) \
    ((flags & (TEXTURE_FLAG__LENGTH__MASK \
              << TEXTURE_FLAG__LENGTH__BIT_COUNT)) \
              >> TEXTURE_FLAG__LENGTH__BIT_COUNT)

#define GET_TEXTURE_FLAG__LENGTH__HEIGHT(flags) \
    (flags & TEXTURE_FLAG__LENGTH__MASK)

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

///
/// GAME
///

typedef struct World_t {
    Entity_Manager entity_manager;
    Chunk_Manager chunk_manager;
    Collision_Manager collision_manager;
    World_Parameters world_params;
} World;

typedef struct Game_t {
    Input input;
    PLATFORM_Gfx_Context gfx_context;
    World world;

    uint32_t tick;
} Game;

typedef struct Scene_t {
    bool is_with__gamespace;
} Scene;

#endif
