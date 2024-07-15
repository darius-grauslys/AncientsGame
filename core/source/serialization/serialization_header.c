#include <serialization/serialization_header.h>

void initialize_serialization_header(
        Serialization_Header *p_serialization_header,
        Identifier__u32 identifier_for__serialized_struct,
        Quantity__u32 size_of__struct,
        m_Serialize m_serialize_handler,
        m_Deserialize m_deserialize_handler) {
    p_serialization_header
        ->size_of__serialized_struct = 
        size_of__struct;

    p_serialization_header
        ->identifier_for__serialized_struct =
        identifier_for__serialized_struct;

    p_serialization_header
        ->m_serialize_handler =
        m_serialize_handler;

    p_serialization_header
        ->m_deserialize_handler =
        m_deserialize_handler;
}
