#ifndef NDS_DEFINES_H
#define NDS_DEFINES_H

#include <nds.h>
#include <maxmod9.h>
#include "defines.h"
#include "defines_weak.h"
#include "platform_defines.h"

enum NDS_Texture_Kind {
    NDS_Texture_Kind__None = 0,
    NDS_Texture_Kind__OAM,
    NDS_Texture_Kind__Background
};

typedef struct PLATFORM_Texture_t {
    OamState *oam;
    uint16_t *gfx;
    const uint16_t *gfx__readonly;
    uint32_t width, height;
    SpriteSize sprite_size;
    uint32_t oam_index;
    Texture_Flags flags;
    uint8_t dma_channel;
    enum NDS_Texture_Kind the_kind_of__texture;
} PLATFORM_Texture;

typedef struct NDS_Background_t {
    PLATFORM_Texture background_texture;
    PLATFORM_Texture background_texture__reserved;
    Vector__3i32 starting_position__3i32;
    Vector__3i32 spanning_scroll_lengths__3i32;
    uint16_t *gfx_map;
    uint16_t *gfx_tileset;
    // uint16_t *gfx_palette;
    Quantity__u32 background__scroll_x, background__scroll_y;
    Quantity__u32 quantity_of__tiles_allocated;
    Quantity__u32 quantity_of__tiles_allocated_in__reserve;
    Quantity__u32 quantity_of__map_entries_allocated;
    Quantity__u32 quantity_of__map_entries_allocated_in__reserve;
    Quantity__u32 quantity_of__pallete_colors_allocated;
    Quantity__u32 quantity_of__pallete_colors_allocated_in__reserve;
    Index__u32 priority;
    Index__u8 map_base, tile_base;
    Signed_Index__i8 background_index_from__initializer;
    Signed_Index__i8 background_index_from__hardware;
} NDS_Background;

typedef struct NDS_Gfx_Context__Chunk_Record_t {
    int32_t x, y;
} NDS_Gfx_Context__Chunk_Record;

#define NDS_SPRITE_PALLETE__8x8 0
#define NDS_SPRITE_PALLETE__16x16 1

typedef struct NDS_Sprite_Pallete_t {
    const uint16_t *p_pallete;
    Index__u8 pallete_slot;
    Quantity__u32 pallete_length;
} NDS_Sprite_Pallete;

#define NDS_PALLETE_SLOT__0 0
#define NDS_PALLETE_SLOT__1 1

#define NDS_SPRITE_PALLETE_QUANTITY_OF_FOR__DEFAULT 2

#define NDS_BACKGROUND_SLOT__GAME__GROUND 0
#define NDS_BACKGROUND_SLOT__GAME__WALL_UPPER 1
#define NDS_BACKGROUND_SLOT__GAME__WALL_LOWER 2

#define NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE 4

typedef struct OamState OamState;

#define NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_MAIN \
    TEXTURE_FLAG__RENDER_METHOD__0
#define NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_SUB \
    TEXTURE_FLAG__RENDER_METHOD__1
#define NDS_TEXTURE_FLAG__RENDER_METHOD__BACKGROUND_MAIN \
    TEXTURE_FLAG__RENDER_METHOD__2
#define NDS_TEXTURE_FLAG__RENDER_METHOD__BACKGROUND_SUB \
    TEXTURE_FLAG__RENDER_METHOD__3

typedef struct PLATFORM_Sprite_t {
    PLATFORM_Texture sprite_texture;
    const uint16_t *gfx_sprite_sheet;
    Sprite_Flags sprite_flags;
} PLATFORM_Sprite;

enum NDS_Background_Allocation_Kind {
    NDS_UI_Background_Allocation_Kind__None=0,
    NDS_UI_Background_Allocation_Kind__Base,
    NDS_UI_Background_Allocation_Kind__Sub_Base,
    NDS_UI_Background_Allocation_Kind__Log_Upper,
    NDS_UI_Background_Allocation_Kind__Log_Lower,
    NDS_UI_Background_Allocation_Kind__Scroll,
    NDS_UI_Background_Allocation_Kind__Scroll_Secondary,
    NDS_UI_Background_Allocation_Kind__Typer,
};

typedef struct NDS_Background_Allocation_Specification_t {
    Vector__3i32 starting_position__3i32;
    Vector__3i32 spanning_scroll_lengths__3i32;
    Texture_Flags background_texture_flags;
    const unsigned int *p_gfx_background;
    const uint16_t *p_map_background;
    const uint16_t *p_pal_background;
    Quantity__u32 length_of__p_gfx_background;
    Quantity__u32 length_of__p_map_background;
    Quantity__u16 length_of__p_pal_background;

    Quantity__u32 length_of__p_gfx_background__reservation;
    Quantity__u32 length_of__p_map_background__reservation;
    Quantity__u32 length_of__p_pal_background__reservation;

    enum NDS_Background_Allocation_Kind the_kind_of__background_allocation;
    Index__u8 background_slot;

    Index__u8 offset_for__tileset;
    Index__u8 offset_for__map;
    Index__u8 slot_for__extended_palette;

    Index__u8 priority_of__background;
} NDS_Background_Allocation_Specification;

typedef struct NDS_Background_Engine_Allocation_Context_t {
    NDS_Background_Allocation_Specification
        nds_background_allocation_specifications[
            NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE];
    //TODO: We will MOST likely need to make
    //extended background palletes a thing.
} NDS_Background_Engine_Allocation_Context;

///
/// For hud, and specifies an unused background
///
#define NDS_BACKGROUND_SLOT__UI__NONE 0
#define NDS_BACKGROUND_PRIORITY__UI__NONE 0

///
/// For hud, and UI that resides above ui_sprites
///
#define NDS_BACKGROUND_SLOT__UI__BASE 0
#define NDS_BACKGROUND_PRIORITY__UI__BASE 1

///
/// For UI that resides beneath ui_sprites, but doesn't scroll.
///
#define NDS_BACKGROUND_SLOT__UI__SUB_BASE 1
#define NDS_BACKGROUND_PRIORITY__UI__SUB_BASE 2

#define NDS_BACKGROUND_STARTING_X_I32__UI__EQUIPMENT 0
#define NDS_BACKGROUND_STARTING_Y_I32__UI__EQUIPMENT 0

///
/// For UI that involves constantly changing text.
///
#define NDS_BACKGROUND_SLOT__UI__LOG_UPPER 2
#define NDS_BACKGROUND_PRIORITY__UI__LOG_UPPER 3

#define NDS_BACKGROUND_STARTING_X_I32__UI__LOG_UPPER 0
#define NDS_BACKGROUND_STARTING_Y_I32__UI__LOG_UPPER 0

///
/// For UI that extends constantly changing text.
///
#define NDS_BACKGROUND_SLOT__UI__LOG_LOWER 3
#define NDS_BACKGROUND_PRIORITY__UI__LOG_LOWER 3

#define NDS_BACKGROUND_STARTING_X_I32__UI__LOG_LOWER 0
#define NDS_BACKGROUND_STARTING_Y_I32__UI__LOG_LOWER 256

///
/// For UI that requires scrolling.
///
#define NDS_BACKGROUND_SLOT__UI__SCROLL 2
#define NDS_BACKGROUND_PRIORITY__UI__SCROLL 3

#define NDS_BACKGROUND_SPAN_Y_I32__UI__INVENTORY 176
#define NDS_BACKGROUND_STARTING_X_I32__UI__INVENTORY_LEFT -44
#define NDS_BACKGROUND_STARTING_Y_I32__UI__INVENTORY_LEFT -88

///
/// For a separate UI background that also needs scrolling.
///
#define NDS_BACKGROUND_SLOT__UI__SCROLL_SECONDARY 3
#define NDS_BACKGROUND_PRIORITY__UI__SCROLL_SECONDARY 3

#define NDS_BACKGROUND_STARTING_X_I32__UI__INVENTORY_RIGHT 44
#define NDS_BACKGROUND_STARTING_Y_I32__UI__INVENTORY_RIGHT -88

///
/// The only background slot available for the typer background.
///
#define NDS_BACKGROUND_SLOT__UI__TYPER 1
#define NDS_BACKGROUND_PRIORITY__UI__SCROLL_TYPER 0

#define NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE 128

typedef struct NDS_Sprite_Array_t {
    PLATFORM_Sprite sprites[
        NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE];
    Quantity__u8 quantity_of__sprites_allocated;
} NDS_Sprite_Array;

typedef struct NDS_Sprite_Manager_t {
    NDS_Sprite_Array sprites_on__oam_main;
    NDS_Sprite_Array sprites_on__oam_sub;
} NDS_Sprite_Manager;

#define NDS_QUANTITY_OF__BACKGROUND_IN__2D_ENGINE    4

typedef NDS_Background NDS_Backgrounds[
    NDS_QUANTITY_OF__BACKGROUND_IN__2D_ENGINE];

typedef struct PLATFORM_Graphics_Window_t {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context;
    OamState *p_oam_state;
} PLATFORM_Graphics_Window;

typedef struct PLATFORM_Gfx_Context_t {
    NDS_Backgrounds backgrounds__main;
    NDS_Backgrounds backgrounds__sub;

    PLATFORM_Graphics_Window graphics_window__main;
    PLATFORM_Graphics_Window graphics_window__sub;

    Typer typers[TYPER_MAX_QUANTITY_OF];

    NDS_Sprite_Manager nds_sprite_manager;

    F_Sprite_Gfx_Allocator__Lookup_Table_For__Entities
        F_sprite_gfx_allocator__lookup_table_for__entities;
    F_Sprite_Gfx_Allocator__Lookup_Table_For__Particles
        F_sprite_gfx_allocator__lookup_table_for__particles;

    f_Sprite_Gfx_Allocator f_sprite_gfx_allocator__handler_for__items;
    f_Sprite_Gfx_Allocator f_sprite_gfx_allocator__handler_for__ui;
    // TODO:    this padding is needed for some reason
    //          because f_ui is getting mangled by something.
    //
    //          search for: "f_ui mangling occurs here"
    //          It's in nds_game.c
    enum UI_Window_Kind the_kind_of__active_ui_window;
    u8 :8;
} PLATFORM_Gfx_Context;

typedef struct PLATFORM_Audio_Context_t {
    /// 
    /// If true, then modmax is actively streaming audio.
    ///
    Repeatable_Psuedo_Random randomizer;
    bool is_audio_context__streaming;
    mm_stream maxmod__stream;
} PLATFORM_Audio_Context;

#define FILE_SYSTEM_CONTEXT__MAX_WRITE 50176
#define FILE_SYSTEM_CONTEXT__QUANTITY_OF__SERIALIZAITON_REQUESTS \
    FILE_SYSTEM_CONTEXT__MAX_WRITE / 256

#define FILE_SYSTEM_CONTEXT__AUDIO_STREAM__TIME_CYCLE 0x74
#define FILE_SYSTEM_CONTEXT__AUDIO_STREAM__TIME_WINDOW 0x50

typedef struct PLATFORM_File_System_Context_t {
    Serialization_Request serialization_requests[
        FILE_SYSTEM_CONTEXT__QUANTITY_OF__SERIALIZAITON_REQUESTS];
    Serialization_Request *ptr_array_of__serialization_requests[
        FILE_SYSTEM_CONTEXT__QUANTITY_OF__SERIALIZAITON_REQUESTS];
    void (*f_audio_stream__callback)();
    Process *p_serialization_process;
    Timer__u8 timer__audio_stream_u8;
} PLATFORM_File_System_Context;

#endif
