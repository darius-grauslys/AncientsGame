#include "serialization/serializer.h"
#include "defines_weak.h"
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
