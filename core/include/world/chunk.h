#ifndef CHUNK_H
#define CHUNK_H

#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

#include "defines_weak.h"
#include "platform_defines.h"
#include "tile.h"
#include "vectors.h"

void initialize_chunk(Chunk *p_chunk);

void m_serialize__chunk(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);

void m_deserialize__chunk(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_chunk__serializer);

Identifier__u32 get_uuid__chunk(
        Chunk *p_chunk);

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
static inline 
void set_tile_of__chunk(
        Chunk* chunk, 
        Local_Tile_Vector__3u8 local_tile_vector,
        Tile* tile) {
    //TODO: we need debug stuffs.
    int32_t index = 
        (1 << (local_tile_vector.z__u8 * CHUNK__DEPTH_BIT_SHIFT))
        + (1 << (local_tile_vector.y__u8 * CHUNK__HEIGHT_BIT_SHIFT)) 
        + local_tile_vector.x__u8;

    chunk->tiles[index] = *tile;
}

static inline 
Tile* get_p_tile_from__chunk(
        Chunk *chunk, 
        Local_Tile_Vector__3u8 local_tile_vector) {
    // TODO: improve
    // int32_t index = (1 << (z * CHUNK__DEPTH_BIT_SHIFT)) +
    //     ((CHUNK_WIDTH__IN_TILES - y) << CHUNK__HEIGHT_BIT_SHIFT) + x;
    Index__u8 index__u8 = 
        local_tile_vector.x__u8
        + (7 - local_tile_vector.y__u8) 
        * 8;

    return &chunk->tiles[index__u8];
}

static inline 
Tile* get_p_tile_from__chunk_using__u8(
        Chunk *chunk, 
        Index__u8 x__local__u8,
        Index__u8 y__local__u8,
        Index__u8 z__local__u8) {
    // TODO: improve
    // int32_t index = (1 << (z * CHUNK__DEPTH_BIT_SHIFT)) +
    //     ((CHUNK_WIDTH__IN_TILES - y) << CHUNK__HEIGHT_BIT_SHIFT) + x;
    Index__u8 index__u8 = 
        x__local__u8
        + (7 - y__local__u8) 
        * 8;

    return &chunk->tiles[index__u8];
}

///
/// Becareful calling this, make sure
/// you're not carelessly dropping a
/// CHUNK_FLAG__IS_UPDATED.
///
static inline
void clear_chunk_flags(Chunk *p_chunk) {
    p_chunk->chunk_flags = CHUNK_FLAGS__NONE;
}

static inline
void set_chunk_as__awaiting_serialization(Chunk *p_chunk) {
    p_chunk->chunk_flags &= 
        ~(CHUNK_FLAG__IS_AWAITING_DESERIALIZATION
                | CHUNK_FLAG__IS_ACTIVE);
    p_chunk->chunk_flags |= 
        CHUNK_FLAG__IS_AWAITING_SERIALIZATION;
}

static inline
void set_chunk_as__awaiting_deserialization(Chunk *p_chunk) {
    p_chunk->chunk_flags &= 
        ~(CHUNK_FLAG__IS_AWAITING_SERIALIZATION
                | CHUNK_FLAG__IS_ACTIVE);
    p_chunk->chunk_flags |= 
        CHUNK_FLAG__IS_AWAITING_DESERIALIZATION;
}

static inline
void set_chunk_as__active(Chunk *p_chunk) {
    p_chunk->chunk_flags &= 
        ~(CHUNK_FLAG__IS_AWAITING_SERIALIZATION
                | CHUNK_FLAG__IS_AWAITING_DESERIALIZATION);
    p_chunk->chunk_flags |= CHUNK_FLAG__IS_ACTIVE;
}

static inline
void set_chunk_as__inactive(Chunk *p_chunk) {
    p_chunk->chunk_flags &= ~CHUNK_FLAG__IS_ACTIVE;
}

///
/// Once set as updated, it will not be set as
/// not updated!
///
/// Use this if a tile is CHANGED, but not animated.
///
/// This flag lets the chunk serializer know if
/// it needs to be serialized.
///
static inline
void set_chunk_as__updated(Chunk *p_chunk) {
    p_chunk->chunk_flags |= CHUNK_FLAG__IS_UPDATED;
}

///
/// Use this if a tile is animated, or changed.
/// If a tile is changed, be sure to call set_chunk_as__updated
/// as well.
///
static inline
void set_chunk_as__visually_updated(Chunk *p_chunk) {
    p_chunk->chunk_flags |= CHUNK_FLAG__IS_VISUALLY_UPDATED;
}

static inline
void set_chunk_as__visually_committed(Chunk *p_chunk) {
    p_chunk->chunk_flags &= ~CHUNK_FLAG__IS_VISUALLY_UPDATED;
}

static inline
bool is_chunk__awaiting_serialization(Chunk *p_chunk) {
    return p_chunk->chunk_flags & CHUNK_FLAG__IS_AWAITING_SERIALIZATION;
}

static inline
bool is_chunk__awaiting_deserialization(Chunk *p_chunk) {
    return p_chunk->chunk_flags & CHUNK_FLAG__IS_AWAITING_DESERIALIZATION;
}

static inline
bool is_chunk__active(Chunk *p_chunk) {
    return p_chunk->chunk_flags & CHUNK_FLAG__IS_ACTIVE;
}

static inline
bool is_chunk__updated(Chunk *p_chunk) {
    return p_chunk->chunk_flags & CHUNK_FLAG__IS_UPDATED;
}

static inline
bool is_chunk__visually_updated(Chunk *p_chunk) {
    return p_chunk->chunk_flags & CHUNK_FLAG__IS_UPDATED;
}

#endif
