#ifndef CHUNK_VECTORS_H
#define CHUNK_VECTORS_H

#include <defines.h>
#include <vectors.h>

static Signed_Index__i32 inline get_chunk_x_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return get_x_i32_from__vector_3i32F4(vector__3i32F4) 
        >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE;
}

static Signed_Index__i32 inline get_chunk_y_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return get_y_i32_from__vector_3i32F4(vector__3i32F4) 
        >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE;
}

static Signed_Index__i32 inline get_chunk_z_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return get_z_i32_from__vector_3i32F4(vector__3i32F4) 
        >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE;
}

static Chunk_Vector__3i32 inline get_chunk_vector__3i32(
        Signed_Index__i32 x,
        Signed_Index__i32 y,
        Signed_Index__i32 z) {
    return (Vector__3i32) {
        x, 
        y, 
        z
    };
}

static Chunk_Vector__3i32 inline get_chunk_vector__3i32_with__i32F4(
        i32F4 x,
        i32F4 y,
        i32F4 z) {
    return (Vector__3i32) {
        x >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE, 
        y >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE, 
        z >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE
    };
}

static Chunk_Vector__3i32 inline vector_3i32F4_to__chunk_vector_3i32(
        Vector__3i32F4 vector) {
    return (Tile_Vector__3i32) {
        get_chunk_x_i32_from__vector_3i32F4(vector),
        get_chunk_y_i32_from__vector_3i32F4(vector),
        get_chunk_z_i32_from__vector_3i32F4(vector)
    };
}

static Chunk_Vector__3i32 inline vector_3i32_to__chunk_vector_3i32(
        Vector__3i32 vector) {
    return (Chunk_Vector__3i32) {
        vector.x__i32 
            >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE,
        vector.y__i32 
            >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE,
        vector.z__i32
            >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE
    };
}

#endif
