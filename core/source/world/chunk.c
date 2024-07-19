#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory_manager.h"
#include "platform_defines.h"
#include "serialization/serialized_field.h"
#include "serialization/serializer.h"
#include "vectors.h"
#include "world/container.h"
#include "world/tile.h"
#include <world/chunk.h>

void initialize_chunk(
        Chunk *p_chunk, 
        Chunk_Vector__3i32 chunk_vector__3i32) {
    p_chunk->x__signed_index_i32 = chunk_vector__3i32.x__i32;
    p_chunk->y__signed_index_i32 = chunk_vector__3i32.y__i32;

    intialize_serializer(
            &p_chunk->_serializer, 
            sizeof(Chunk), 
            get_uuid__chunk(p_chunk), 
            m_serialize__chunk, 
            m_deserialize__chunk);
}

void m_serialize__chunk(
        Game *p_game,
        Serialized_Field *p_serialized_field__chunk) {
    if (!is_p_serialized_field__linked(
                p_serialized_field__chunk)) {
        return;
    }
    Chunk *p_chunk =
        p_serialized_field__chunk
        ->p_serialized_field__chunk
        ;
    for (u8 y=0;y<CHUNK_WIDTH__IN_TILES;y++) {
        for (u8 x=0;x<CHUNK_WIDTH__IN_TILES;x++) {
            Tile *p_tile =
                &p_chunk->tiles[x + y * 8];
            if (!is_tile__container(p_tile))
                continue;

            Vector__3i32 vector__3i32 =
                get_vector__3i32(
                        x + (p_chunk->x__signed_index_i32 << 3), 
                        y + (p_chunk->y__signed_index_i32 << 3),
                        0);

            Serialized_Field s_inventory;
            initialize_serialized_field_as__unlinked(
                    &s_inventory,
                    get_container__uuid(
                        vector__3i32));

            if (!resolve_s_inventory_ptr_to__inventory_manager(
                        get_p_inventory_manager_from__game(p_game),
                        &s_inventory)) {
                continue;
            }

            release_p_inventory_in__inventory_manager(
                    get_p_inventory_manager_from__game(p_game), 
                    s_inventory.p_serialized_field__inventory);
        }
    }
}

void m_deserialize__chunk(
        Game *p_game,
        Serialized_Field *p_chunk) {
    
}

Identifier__u32 get_uuid__chunk(
        Chunk *p_chunk) {
    return 1337;
    // TODO: impl
}
