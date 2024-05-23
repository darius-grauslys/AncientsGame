#ifndef DEFINES_H
#define DEFINES_H

#ifndef NDEBUG
#include <debug/debug.h>
#endif

///
/// This file has the definition of EVERY struct
/// macro, and typedef used in core!
///
/// Need help finding something? Everything is
/// organized by PRIMARY usage within the ./include
/// and ./source folders. So, for example, if you wanted
/// to find structs primarily used in the "world" folder
/// you should search for SECTION_World.
///
/// For base level files, search for SECTION_core.
///
/// NOTE:
/// SECTION_defines is for definitions which only
/// have PRIMARY usage in defines.h .
///
/// NOTE:
/// Every single struct, macro, and typedef has a forward
/// declaration in defines_weak.h . If you add a new
/// struct, macro, or typedef you SHOULD include a forward
/// definition of that type in defines_weak.h
///

#include <defines_weak.h>
#include <platform.h>

///
/// SECTION_defines
///

#define FRACTIONAL_PERCISION_4__BIT_SIZE 4
/// FIXED POINT fractional, with 4 bits of percision.
typedef int32_t     i32F4;

/// 
/// Vector__3i32F4 is a 3-tuple of 32 bit FIXED POINT
/// fractional integers with 4 bits of percision.
///
/// To get a whole number, use ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK
/// and shift the result to the right by ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE.
///
typedef struct Vector__3i32F4_t {
    i32F4 x__i32F4, y__i32F4, z__i32F4;
} Vector__3i32F4;

typedef int32_t Signed_Index__i32;

typedef uint32_t Psuedo_Random_Seed__u32;
typedef uint32_t Timer__u32;
typedef uint8_t Timer__u8;
typedef uint8_t Direction__u8;

typedef uint8_t Index_u8;
typedef uint16_t Index_u16;
typedef uint32_t Index_u32;

typedef int32_t Psuedo_Random__i32;
typedef uint32_t Psuedo_Random__u32;

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

///
/// SECTION_collisions
///

typedef struct Hitbox_AABB_t {
    Quantity__u32 width__quantity_32;
    Quantity__u32 height__quantity_u32;
    // We don't have a z-axis height.
    // Why? Because even thought the world
    // is 3D, everyone is made out of paper
    // in this video game.
    //
    // Entities can't co-exist in the same tile
    // but they can stand on top of one in an
    // above tile.
    Signed_Index__i32
        x__chunk__signed_index_i32, 
        y__chunk__signed_index_i32, 
        z__chunk__signed_index_i32;
    // TODO: replace with Vector_3i32
   i32F4 
        x__i32F4, 
        y__i32F4, 
        z__i32F4;
    // TODO: replace with Vector_3i32
   i32F4 
        x__velocity__i32F4, 
        y__velocity__i32F4, 
        z__velocity__i32F4;
} Hitbox_AABB;

/// When checking the distance between two collisions along each axis
/// anything equal to or less than this value is ignored when determining
/// displacement. This useful threshold is what allows a colliding player
/// to move up while an entity is moving into them from the right.
#define COLLISION_DELTA_THRESHOLD 20
#define COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET \
    (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4)
#define COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET \
    (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8)

///
/// This type is specific to Collision_Manager,
/// so there is no header files supporting it.
///
typedef struct Collision_Manager__Collision_Node_t {
    Entity *p_entity_ptrs[ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE];

    struct Collision_Manager__Collision_Node_t *p_north__collision_node;
    struct Collision_Manager__Collision_Node_t *p_east__collision_node;
    struct Collision_Manager__Collision_Node_t *p_south__collision_node;
    struct Collision_Manager__Collision_Node_t *p_west__collision_node;

    Direction__u8 legal_directions;
} Collision_Manager__Collision_Node;

///
/// 4 Collision Nodes per layer 3 node.
///
typedef struct Collision_Manager__Layer_Three_t {
    Collision_Manager__Collision_Node *p_top_left__collision_node;
    Collision_Manager__Collision_Node *p_top_right__collision_node;
    Collision_Manager__Collision_Node *p_bottom_left__collision_node;
    Collision_Manager__Collision_Node *p_bottom_right__collision_node;

    Signed_Index__i32 
        x__center_chunk__signed_index_i32, 
        y__center_chunk__signed_index_i32;
} Collision_Manager__Layer_Three;

typedef struct Collision_Manager__Layer_Two_t {
    Collision_Manager__Layer_Three top_left__layer_three;
    Collision_Manager__Layer_Three top_right__layer_three;
    Collision_Manager__Layer_Three bottom_left__layer_three;
    Collision_Manager__Layer_Three bottom_right__layer_three;

    Signed_Index__i32 
        x__center_chunk__signed_index_i32, 
        y__center_chunk__signed_index_i32;
} Collision_Manager__Layer_Two;

typedef struct Collision_Manager__t {
    Collision_Manager__Collision_Node collision_nodes[
        CHUNK_MANAGER__QUANTITY_OF_CHUNKS];

    Collision_Manager__Layer_Two top_left__layer_two;
    Collision_Manager__Layer_Two top_right__layer_two;
    Collision_Manager__Layer_Two bottom_left__layer_two;
    Collision_Manager__Layer_Two bottom_right__layer_two;

    Collision_Manager__Collision_Node *p_most_north_western__collision_node;

    Signed_Index__i32 
        x__center_chunk__signed_index_i32, 
        y__center_chunk__signed_index_i32;
} Collision_Manager;

///
/// SECTION_debug
///

///
/// SECTION_rendering
///

enum Sprite_Animation_Kind {
    Sprite_Animation_Kind__None,
    Sprite_Animation_Kind__Idle,
    Sprite_Animation_Kind__Humanoid__Walk,
    Sprite_Animation_Kind__Humanoid__Use,
    Sprite_Animation_Kind__Humanoid__Hurt,
    Sprite_Animation_Kind__Humanoid__Die,
    Sprite_Animation_Kind__Player__Sleep,
};

typedef uint8_t Sprite_Frame_Index__u8;

typedef Sprite_Frame_Index__u8 (*f_Sprite_Frame_Lookup) (
        Entity *p_entity,
        enum Sprite_Animation_Kind animation_kind);

typedef Timer__u32 (*f_Animation_Speed_Lookup) (
        Entity *p_entity,
        enum Sprite_Animation_Kind animation_kind);
typedef Timer__u32 (*f_Animation_Duration_Lookup) (
        Entity *p_entity,
        enum Sprite_Animation_Kind animation_kind);

typedef struct Sprite_Wrapper_t {
    PLATFORM_Sprite sprite;
    Timer__u32 time_elapsed;
    Timer__u32 time_limit;
    Direction__u8 direction;
    Sprite_Frame_Index__u8 frame__initial;
    Sprite_Frame_Index__u8 frame;
    Sprite_Frame_Index__u8 frame__final;
    enum Sprite_Animation_Kind the_kind_of_animation__this_sprite_has;
    enum Sprite_Animation_Kind the_kind_of_animation__thats_upcomming;
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

#define SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__IDLE 0
#define SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__WALK 2
#define SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__USE 2
#define SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__HURT 1
#define SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__DIE 2
#define SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__SLEEP 0

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
/// TEXTURE_FLAGS:
/// Bit orderings, from most significant to least:
/// [32 <-> 11 bits,    PLATFORM specific flags]
/// [10th bit,          is hidden]
/// [9-7 bits,          render method] 
/// [6-4 bits,          width] 
/// [3-1 bits,          height]
///

// Just a width or height component of an image.
#define TEXTURE_FLAG__LENGTH__BIT_COUNT 3
#define TEXTURE_FLAG__LENGTH__MASK ((1<<\
            TEXTURE_FLAG__LENGTH__BIT_COUNT)-1)
// The width and height component of the image
#define TEXTURE_FLAG__SIZE__BIT_COUNT 6
#define TEXTURE_FLAG__SIZE__MASK ((1<<\
            TEXTURE_FLAG__SIZE__BIT_COUNT)-1)

// Texture length specifiers
#define TEXTURE_FLAG__LENGTH_x8       0b000
#define TEXTURE_FLAG__LENGTH_x16    (1+\
        TEXTURE_FLAG__LENGTH_x8)    //0b001
#define TEXTURE_FLAG__LENGTH_x32    (1+\
        TEXTURE_FLAG__LENGTH_x16)   //0b010
#define TEXTURE_FLAG__LENGTH_x64    (1+\
        TEXTURE_FLAG__LENGTH_x32)   //0b011
#define TEXTURE_FLAG__LENGTH_x128   (1+\
        TEXTURE_FLAG__LENGTH_x64)   //0b100
#define TEXTURE_FLAG__LENGTH_x256   (1+\
        TEXTURE_FLAG__LENGTH_x128)  //0b101

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
/// SECTION_entity
///

typedef struct Entity_t Entity;

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
typedef void (*m_Item_Use)(
        Item *p_item_self, 
        Entity *p_entity_user, 
        Game *p_game);
typedef void (*m_Item_Equip)(
        Item *p_item_self, 
        Entity *p_entity_user, 
        Game *p_game);
typedef void (*m_Item_Unequip)(
        Item *p_item_self, 
        Entity *p_entity_user, 
        Game *p_game);

typedef struct Inventory_t Inventory;

typedef void (*m_Dispose_Entity)(
        Entity *p_entity_self, 
        Game *p_game);
typedef void (*m_Entity_Controller)(
        Entity *p_entity_self, 
        Game *p_game);

///
/// callee_data is an opaque pointer to whatever
/// data the user of this function pointer needs
/// passed in addition to collided entities.
///
typedef void (*m_Entity_Collision)(
        Entity *p_entity_collision_source,
        Entity *p_entity_collided,
        Direction__u8 direction_of_collision);

typedef struct Tile_t Tile;

typedef void (*m_Entity_Tile_Collision)(
        Entity *p_entity_self,
        Tile *p_tile_collided);

typedef void (*m_Entity_Animation) 
    (Entity *p_entity_self, Timer__u32 timer);

///
/// Here we define the entity super struct. It has everything we could need
/// for an entity, even if some of the things are not used.
///

typedef uint8_t Entity_Flags__u8;

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

typedef struct Entity_t {
    Sprite_Wrapper          sprite_wrapper;

    // DO NOT INVOKE! Called automatically in release_entity(...)
    m_Dispose_Entity            m_dispose_handler;
    // DO NOT INVOKE! Called automatically
    m_Entity_Controller         m_controller_handler;
    // DO NOT INVOKE! Called automatically
    m_Entity_Collision          m_collision_handler;
    m_Entity_Tile_Collision     m_tile_collision_handler;
    m_Entity_Animation          m_animation_handler;

    Hitbox_AABB hitbox;

    Entity_Flags__u8            entity_flags;

    enum Entity_Kind            the_kind_of_entity__this_entity_is;
    union {
        struct { // humanoid union
            Armor_Properties    armor_properties;
            Direction__u8       direction;
            Quantity__u8        max_health__quantity_u8;
            Quantity__u8        health__quantity_u8;
            Timer__u8           stun_timer__timer_u8;
        };
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
    Entity *p_local_player;
    Quantity__u32 entity_count__quantity_u32;
} Entity_Manager;

///
/// SECTION_input
///

typedef uint32_t Input_Flags__u32;

#define INPUT_NONE 0
#define INPUT_FORWARD (1<<0)
#define INPUT_LEFT (INPUT_FORWARD<<1)
#define INPUT_RIGHT (INPUT_LEFT<<1)
#define INPUT_BACKWARDS (INPUT_RIGHT<<1)

#define INPUT_GAME_SETTINGS (INPUT_BACKWARDS<<1)
#define INPUT_LOCKON (INPUT_GAME_SETTINGS<<1)
#define INPUT_USE (INPUT_LOCKON<<1)
#define INPUT_USE_SECONDARY (INPUT_USE<<1)
#define INPUT_EXAMINE (INPUT_USE_SECONDARY<<1)
//TODO: figure out what y does again lol
#define INPUT_Y_IS_WHAT_AGAIN (INPUT_EXAMINE<<1)

typedef struct Input_t {
    Input_Flags__u32 input_flags;
} Input;

///
/// SECTION_inventory
///

///
/// SECTION_multiplayer
///

///
/// SECTION_scene
///

typedef struct Scene_t {
    bool is_with__gamespace;
} Scene;

typedef void (*m_Load_Scene)  (Scene *p_this_scene, Game* p_game);
typedef void (*m_Update_Scene)(Scene *p_this_scene, Game* p_game);
typedef void (*m_Render_Scene)(Scene *p_this_scene, Game* p_game);
typedef void (*m_Unload_Scene)(Scene *p_this_scene, Game* p_game);

///
/// SECTION_ui
///

enum UI_Element_Kind {
    UI_Element_Kind__Button,
    UI_Element_Kind__Draggable,
    UI_Element_Kind__Slider,
};

typedef struct UI_Element_t UI_Element;

typedef void (*m_UI_Clicked)(UI_Element *p_this_ui_element);
typedef void (*m_UI_Dragged)(UI_Element *p_this_ui_element);
typedef void (*m_UI_Dropped)(UI_Element *p_this_ui_element);

typedef int16_t UI_Slider_Position__i16;
typedef uint8_t UI_Flags__u8;

#define UI_FLAGS__BIT_SHIFT_IS_ENABLED 0

#define UI_FLAGS__BIT_IS_ENABLED \
    (1 << UI_FLAGS__BIT_SHIFT_IS_ENABLED)

typedef struct UI_Element_t {
    enum UI_Element_Kind the_kind_of_ui_element__this_is;
    Hitbox_AABB ui_bounding_box__aabb;
    UI_Flags__u8 ui_flags;
    union {
        union {
            struct { // UI_Button
                m_UI_Clicked m_button_clicked_handler;
            };
            struct { // UI_Draggable
                m_UI_Dragged m_draggable_dragged_handler;
                m_UI_Dropped m_draggable_dropped_handler;
            };
            struct { // UI_Slider
                m_UI_Dragged m_ui_slider_dragged_handler;
                UI_Element *p_ui_slider_handle;
                UI_Slider_Position__i16 slider_position__ui_position_i16;
                UI_Slider_Position__i16 slider_position_min__ui_position_i16;
                UI_Slider_Position__i16 slider_position_max__ui_position_i16;
            };
        };
    };
} UI_Element;

#define UI_ELEMENT_MAXIMUM_QUANTITY_OF 128

typedef struct UI_Manager_t {
    Quantity__u8 quantity_of__ui_elements__quantity_u8;
    UI_Element ui_elements[];
} UI_Manager;

///
/// SECTION_world
///

typedef uint8_t Chunk_Tile_Index__u8;
///
/// The localized version of Vector_3i32.
/// It is local to a chunk.
///
typedef struct Local_Chunk_Vector_t {
    Chunk_Tile_Index__u8 
        x__chunk_index_u8, 
        y__chunk_index_u8, 
        z__chunk_index_u8;
} Local_Chunk_Vector;

#define TILE_PIXEL_HEIGHT 8
#define TILE_PIXEL_WIDTH 8

#define TILE_PIXEL_WIDTH__BIT_SIZE 3

#define TILE_SHEET_PIXEL_WIDTH 256
#define TILE_SHEET_PIXEL_HEIGHT 256

#define TILE_SHEET_TILE_WIDTH (TILE_SHEET_PIXEL_WIDTH / TILE_PIXEL_WIDTH)
#define TILE_SHEET_TILE_HEIGHT (TILE_SHEET_PIXEL_HEIGHT / TILE_PIXEL_HEIGHT)

#define QUANTITY_OF_TILES__IN_TILE_SHEET_ROW (TILE_SHEET_PIXEL_WIDTH / TILE_PIXEL_WIDTH)


#define TILE_STAIR_DIRECTION_NORTH      0
#define TILE_STAIR_DIRECTION_NORTH_EAST 1
#define TILE_STAIR_DIRECTION_EAST       2
#define TILE_STAIR_DIRECTION_SOUTH_EAST 3
#define TILE_STAIR_DIRECTION_SOUTH      4
#define TILE_STAIR_DIRECTION_SOUTH_WEST 5
#define TILE_STAIR_DIRECTION_WEST       6
#define TILE_STAIR_DIRECTION_NORTH_WEST 7
#define TILE_STAIR_DIRECTION_COUNT 8

#define TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR 3
#define TILE_FLAGS__BIT_SHIFT_IS_STAIR_UP_OR_DOWN \
    (TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR + 1)
#define TILE_FLAGS__BIT_SHIFT_IS_STAIR \
    (TILE_FLAGS__BIT_SHIFT_IS_STAIR_UP_OR_DOWN + 1)
#define TILE_FLAGS__BIT_SHIFT_IS_SIGHT_BLOCKING \
    (TILE_FLAGS__BIT_SHIFT_IS_STAIR + 1)
#define TILE_FLAGS__BIT_SHIFT_IS_UNPASSABLE \
    (TILE_FLAGS__BIT_SHIFT_IS_SIGHT_BLOCKING  +1)

#define TILE_FLAGS__MASK_STAIR_VALUE \
    ((1 << TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR) - 1)
#define TILE_FLAGS__BIT_INVERTED_STAIR \
    ( 1 << TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR)
#define TILE_FLAGS__BIT_IS_STAIR_UP_OR_DOWN \
    ( 1 << TILE_FLAGS__BIT_SHIFT_IS_STAIR_UP_OR_DOWN)
#define TILE_FLAGS__BIT_IS_STAIR \
    ( 1 << TILE_FLAGS__BIT_SHIFT_IS_STAIR)
#define TILE_FLAGS__BIT_IS_SIGHT_BLOCKING \
    ( 1 << TILE_FLAGS__BIT_SHIFT_IS_SIGHT_BLOCKING)
#define TILE_FLAGS__BIT_IS_UNPASSABLE \
    ( 1 << TILE_FLAGS__BIT_SHIFT_IS_UNPASSABLE)

#define TILE_FLAGS__NONE 0

#define TILE_SHEET_ELEMENT_WIDTH 32

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
};

#define TILE_COVER_SHEET_INDEX__WALL (1 + TILE_SHEET_TILE_WIDTH * 14)

#define TILE_COVER_SHEET_INDEX__PLANT (25 + TILE_SHEET_TILE_WIDTH * 21)
#define TILE_COVER_SHEET_INDEX__FLOWER_RED (26 + TILE_SHEET_TILE_WIDTH * 21)
#define TILE_COVER_SHEET_INDEX__FLOWER_BLUE (27 + TILE_SHEET_TILE_WIDTH * 21)
#define TILE_COVER_SHEET_INDEX__FLOWER_YELLOW (28 + TILE_SHEET_TILE_WIDTH * 21)
#define TILE_COVER_SHEET_INDEX__CACTUS (29 + TILE_SHEET_TILE_WIDTH * 21)

#define TILE_COVER__BIT_SHIFT_IS_WALL 6
#define TILE_COVER__BIT_IS_WALL (1 <<\
        TILE_COVER__BIT_SHIFT_IS_WALL)

enum Tile_Cover_Kind {
    Tile_Cover_Kind__None               = 0b00000,
    Tile_Cover_Kind__Plant,
    Tile_Cover_Kind__Flower_Red,
    Tile_Cover_Kind__Flower_Blue,
    Tile_Cover_Kind__Flower_Yellow,
    Tile_Cover_Kind__Cactus,
    Tile_Cover_Kind__Oak_Trunk,
    Tile_Cover_Kind__Oak_Root,
    Tile_Cover_Kind__Oak_Branch,
    Tile_Cover_Kind__Oak_Leaves,
    Tile_Cover_Kind__Leaf_Clutter,
    Tile_Cover_Kind__Wall__Oak_Wood     = 0b1000001,
    Tile_Cover_Kind__Wall__Stone_Brick  = 0b1000010,
    Tile_Cover_Kind__Wall__Gold         = 0b1000011,
    Tile_Cover_Kind__Wall__Iron         = 0b1000100,
    Tile_Cover_Kind__Wall__Diamond      = 0b1000101,
    Tile_Cover_Kind__Wall__Amethyst     = 0b1000110,
    Tile_Cover_Kind__Wall__Sandstone    = 0b1000111,
    Tile_Cover_Kind__Wall__Stone        = 0b1001000,
    Tile_Cover_Kind__Wall__Dirt         = 0b1001001,
    Tile_Cover_Kind__Wall__Sand         = 0b1001010,
};

typedef uint8_t Tile_Flags__u8;

typedef struct Tile_t {
    enum Tile_Kind                  the_kind_of_tile__this_tile_is;
    enum Tile_Cover_Kind        the_kind_of_tile_cover__this_tile_has;
    //TODO: this structure is not padding friendly.
    // consider making flags 16 bit
    Tile_Flags__u8 tile_flags;
    // bits 1 2 3, stair direction (values 0-7)
    // bit 4, is the stair inverted
    // bit 5, is the stair going up or down
    // bit 6, is this a stair
    // bit 7, is sight blocking
    // bit 8, is passable
} Tile;

typedef uint16_t Tile_Render_Index__u16;
typedef uint16_t Tile_Wall_Adjacency_Code__u16;

typedef struct Tile_Render_Result_t {
    Tile_Render_Index__u16 tile_index__ground;
    Tile_Render_Index__u16 tile_index__cover;
    Tile_Render_Index__u16 tile_index__sprite_cover;
    Tile_Wall_Adjacency_Code__u16 wall_adjacency;
} Tile_Render_Result;

#define TILE_RENDER__WALL_ADJACENCY__BIT_SHIFT_VFLIP 5
#define TILE_RENDER__WALL_ADJACENCY__BIT_VFLIP (1<<\
        TILE_RENDER__WALL_ADJACENCY__BIT_SHIFT_VFLIP)

#define TILE_RENDER__WALL_ADJACENCY__EAST  0b00010001
#define TILE_RENDER__WALL_ADJACENCY__WEST  0b00110001
#define TILE_RENDER__WALL_ADJACENCY__NORTH 0b00000100
#define TILE_RENDER__WALL_ADJACENCY__SOUTH 0b00001000

#define TILE_RENDER__WALL_ADJACENCY__COVER_MASK 0b0011
#define TILE_RENDER__WALL_ADJACENCY__SPRITE_COVER_MASK 0b1111

typedef struct World_Parameters_t World_Parameters;
typedef struct Chunk_t Chunk;

typedef void (*f_Chunk_Generator)(
        World_Parameters *p_world_parameters,
        Chunk *p_chunk_to_generate);

typedef struct World_Parameters_t {
    f_Chunk_Generator f_chunk_generator;
    Psuedo_Random_Seed__u32 seed__initial;
    Psuedo_Random_Seed__u32 seed__current_random;
} World_Parameters;

/// Should only be made from calls to inlined helpers
/// from chunk_manager.h
typedef struct Position_Local_To_Chunk_2i8_t {
    Quantity__u8 x__local__quantity_u8;
    Quantity__u8 y__local__quantity_u8;
} Position_Local_To_Chunk_2i8;

typedef struct Chunk_t {
    Tile tiles[CHUNK__WIDTH * CHUNK__HEIGHT * CHUNK__DEPTH];
    Signed_Index__i32 x__signed_index_i32, y__signed_index_i32;
    bool is_available;
} Chunk;

typedef struct Chunk_Manager__Chunk_Map_Node_t {
    Chunk *p_chunk__here;
    struct Chunk_Manager__Chunk_Map_Node_t *p_north__chunk_map_node;
    struct Chunk_Manager__Chunk_Map_Node_t *p_east__chunk_map_node;
    struct Chunk_Manager__Chunk_Map_Node_t *p_south__chunk_map_node;
    struct Chunk_Manager__Chunk_Map_Node_t *p_west__chunk_map_node;
} Chunk_Manager__Chunk_Map_Node;

typedef Chunk_Manager__Chunk_Map_Node
    Chunk_Manager__Chunk_Map[CHUNK_MANAGER__QUANTITY_OF_CHUNKS];

typedef struct Chunk_Manager_t {
    Chunk chunks[CHUNK_MANAGER__QUANTITY_OF_CHUNKS];
    Chunk_Manager__Chunk_Map chunk_map;
    
    Chunk_Manager__Chunk_Map_Node *p_local_player_occupied__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *p_most_north_western__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *p_most_south_eastern__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *p_most_north_eastern__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *p_most_south_western__chunk_map_node;

    Signed_Index__i32 
        x__center_chunk__signed_index_i32, 
        y__center_chunk__signed_index_i32;
} Chunk_Manager;

typedef struct World_t {
    Entity_Manager entity_manager;
    Chunk_Manager chunk_manager;
    Collision_Manager collision_manager;
    World_Parameters world_parameters;
} World;

///
/// SECTION_core
///

typedef struct Game_t {
    Input input;
    PLATFORM_Gfx_Context gfx_context;
    World world;

    Timer__u32 tick__timer_u32;
} Game;

#endif
