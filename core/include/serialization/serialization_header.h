#ifndef SERIALIZATION_HEADER_H
#define SERIALIZATION_HEADER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_serialization_header(
        Serialization_Header *p_serialization_header,
        Identifier__u32 identifier_for__serialized_struct,
        Quantity__u32 size_of__struct,
        m_Serialize m_serialize_handler,
        m_Deserialize m_deserialize_handler
        );

static inline
void initialize_serialization_header_for__deallocated_struct(
        Serialization_Header *p_serialization_header) {
    initialize_serialization_header(
            p_serialization_header,
            IDENTIFIER__UNKNOWN__u32,
            0,
            0, 0);
}

#endif
