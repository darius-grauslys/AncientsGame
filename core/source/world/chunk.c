#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "platform.h"
#include "platform_defines.h"
#include "serialization/serialized_field.h"
#include "serialization/serializer.h"
#include "vectors.h"
#include "world/tile.h"
#include <world/chunk.h>

void initialize_chunk(Chunk *p_chunk) {
    intialize_serializer(
            &p_chunk->_serializer, 
            sizeof(Chunk), 
            get_uuid__chunk(p_chunk), 
            m_serialize__chunk, 
            m_deserialize__chunk);
}


void m_serialize__chunk(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_chunk__serializer) {
    enum PLATFORM_Write_File_Error error = 
        PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)p_this_chunk__serializer, 
                p_this_chunk__serializer->_serialization_header.size_of__struct, 
                1, 
                p_serialization_request->p_file_handler);
    Chunk *p_chunk = (Chunk*)p_this_chunk__serializer;
    clear_chunk_flags(p_chunk);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }
}

void m_deserialize__chunk(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_chunk__serializer) {
    Quantity__u32 length_of__read =
        p_this_chunk__serializer
        ->_serialization_header.size_of__struct;
    Serializer _serializer = *p_this_chunk__serializer;
    Chunk *p_chunk = (Chunk*)p_this_chunk__serializer;
    enum PLATFORM_Read_File_Error error = 
        PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)p_this_chunk__serializer, 
                &length_of__read,
                1, 
                p_serialization_request->p_file_handler);
    initialize_chunk((Chunk*)p_this_chunk__serializer);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }
    if (length_of__read
            != p_this_chunk__serializer
            ->_serialization_header
            .size_of__struct) {
        debug_error("m_serialize__chunk, bad read length: %d/%d", 
                length_of__read,
                p_this_chunk__serializer
                ->_serialization_header
                .size_of__struct);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    set_chunk_as__active(p_chunk);
}

Identifier__u32 get_uuid__chunk(
        Chunk *p_chunk) {
    return 1337;
    // TODO: impl
}
