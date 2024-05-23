#ifndef PLATFORM_H
#define PLATFORM_H

#include <defines_weak.h>

///
/// This file contains all function signatures
/// which are NOT implemented in core.
///
/// Their implementation is platform dependent
/// and will be implemented by a backend such
/// as OpenGL, or nds.
///
/// -- HOW TO MAKE YOUR OWN BACKEND IMPLEMENTATION --
/// Create a header file at the base directory of your
/// include folder named "platform_defines.h"
///
/// Here you will define all your PLATFORM_*** structs.
/// Define the PLATFORM_*** functions whenever you want
/// but try to be organized about it.

/// <Entity>
void PLATFORM_render_entity(
        Entity *entity,
        int32_t x__origin,
        int32_t y__origin,
        Game *game);
/// </Entity>


/// <GFX_context>
void PLATFORM_init_gfx_context(PLATFORM_Gfx_Context *gfx_context);

///
/// On NDS, this will init both main and sub.
///
void PLATFORM_init_rendering__menu(PLATFORM_Gfx_Context *gfx_context);
/// 
/// On NDS, this will init both main and sub.
///
void PLATFORM_init_rendering__game(PLATFORM_Gfx_Context *gfx_context);

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager);
/// </GFX_context>

/// <Chunk>
///
/// TODO: we will want to rethink
/// the render_chunk and render_tile.
///
/// NDS wants to just use a tiled background
/// and PC wants to use openGL rect with uv's.
///
/// not quite sure how to best manage this atm.
///

/// 
/// Render a chunk using a texture_atlas
/// onto a given RenderTarget.
///
/// RenderTarget is an opaque pointer, which is defined
/// via a backend implementation.
///

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *context,
        Chunk *chunk);
/// </Chunk>

/// <Texture>
void PLATFORM_init_texture(PLATFORM_Texture *texture, Texture_Flags flags);
void PLATFORM_free_texture(PLATFORM_Texture *texture);

///
/// This is currently no-op on NDS. Later, if we need to,
/// we can to nitroFS along with this.
///
void PLATFORM_init_texture__with_path(PLATFORM_Texture *texture,
        Texture_Flags flags,
        const char *path);

void PLATFORM_init_texture__with_size(PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height);

void PLATFORM_update_texture(PLATFORM_Texture *texture);

void PLATFORM_use_texture(PLATFORM_Texture *texture);

void PLATFORM_release_texture(PLATFORM_Texture *texture);

uint32_t *PLATFORM_get_texture_flags_ptr(PLATFORM_Texture *texture);
/// </Texture>

/// <Render_Tile>
void PLATFORM_render_tile(
        PLATFORM_Gfx_Context *context,
        Tile *tile);
/// </Render_Tile>

/// <Sprite>
typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;
void PLATFORM_init_sprite(PLATFORM_Sprite *sprite,
        Texture_Flags texture_flags_for__sprite,
        bool perform_update);
void PLATFORM_init_sprite_for__entity(Entity *entity);

void PLATFORM_release_sprite(PLATFORM_Sprite *sprite);
/// </Sprite>

/// <Render_Sprite>
///
/// On NDS, PLATFORM_render_sprite doesn't do anything, and will be
/// optimized out.
///

void PLATFORM_render_sprite(Sprite_Wrapper *sprite);

/// </Render_Sprite>

/// <Animate_Sprite>
///
/// Performs the necessary graphical changes needed
/// to reflect the entity's sprite_wrapper.frame value.
///
void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *sprite_wrapper);
/// </Animate_Sprite>

/// <Game>
void PLATFORM_pre_render(Game *game);
void PLATFORM_post_render(Game *game);
/// </Game>

/// <Input>
void PLATFORM_poll_input(Game *game);
/// </Input>

/// <Defines>
typedef struct PLATFORM_Gfx_Context_t PLATFORM_Gfx_Context;
typedef struct PLATFORM_Texture_t PLATFORM_Texture_t;
typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;

#include <platform_defines.h>

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

#ifndef PLATFORM__ENTITIES
#define ENTITY_MAXIMUM_QUANTITY_OF 128
#define ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS 8
#define ENTITY_MAXIMUM_QUANTITY_OF__NPCS 48
#define ENTITY_MAXIMUM_QUANTITY_OF__PROJECTILES 72
#endif

#define ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE \
    (ENTITY_MAXIMUM_QUANTITY_OF__NPCS \
    + ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS)

#include <stdint.h>
#include <stdbool.h>

#ifndef PLATFORM_DEFINES_H
#error Cannot build AncientsGame without a backend implementation.
#endif
/// </Defines>

#endif
