#include "serialization/serializer.h"
#include "defines_weak.h"
#include "game.h"
#include "serialization/serialization_header.h"

void intialize_serializer(
        Serializer *p_serializer,
        Quantity__u32 size_of__struct,
        Identifier__u32 uuid__u32,
        m_Serialize m_serialize_handler,
        m_Deserialize m_deserialize_handler) {
    initialize_serialization_header(
            &p_serializer->_serialization_header, 
            uuid__u32, 
            size_of__struct);

    p_serializer->m_serialize_handler =
        m_serialize_handler;
    p_serializer->m_deserialize_handler =
        m_deserialize_handler;
}

void intialize_serializer_as__deallocated(
        Serializer *p_serializer,
        Quantity__u32 size_of__struct,
        m_Serialize m_serialize_handler,
        m_Deserialize m_deserialize_handler) {
    initialize_serialization_header_for__deallocated_struct(
            &p_serializer->_serialization_header, 
            size_of__struct);

    p_serializer->m_serialize_handler =
        m_serialize_handler;
    p_serializer->m_deserialize_handler =
        m_deserialize_handler;
}

void m_serialize__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    enum PLATFORM_Write_File_Error error = 
        PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&p_this_serializer->_serialization_header, 
                sizeof(Serialization_Header), 
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_serialize__default, error: %d", error);
        return;
    }

    Quantity__u32 length_of__write =
        p_this_serializer->_serialization_header.size_of__struct
        - sizeof(Serializer);
    error = PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                ((u8*)&p_this_serializer) + sizeof(Serializer), 
                length_of__write, 
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_serialize__default, error: %d", error);
        return;
    }
}

void m_deserialize__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    Quantity__u32 length_of__read =
        sizeof(Serialization_Header);

    enum PLATFORM_Read_File_Error error = 
        PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&p_this_serializer->_serialization_header, 
                &length_of__read, 
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_deserialize__default, failed error: %d", error);
        return;
    }

    if (length_of__read
            != sizeof(Serialization_Header)) {
        debug_error("m_deserialize__default, bad read length: %d/%d", 
                length_of__read,
                sizeof(Serialization_Header));
        return;
    }

    Quantity__u32 length_of__read__expected = 
        length_of__read =
            p_this_serializer->_serialization_header.size_of__struct
            - sizeof(Serializer);

    error = PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                ((u8*)p_this_serializer) + sizeof(Serializer), 
                &length_of__read, 
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_deserialize__default, failed error: %d", error);
        return;
    }

    if (length_of__read
            != length_of__read__expected) {
        debug_error("m_deserialize__default, bad read length: %d/%d", 
                length_of__read,
                length_of__read__expected);
        return;
    }
}
