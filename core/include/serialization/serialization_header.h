#ifndef SERIALIZATION_HEADER_H
#define SERIALIZATION_HEADER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_serialization_header(
        Serialization_Header *p_serialization_header,
        Identifier__u32 identifier_for__serialized_struct,
        Quantity__u32 size_of__struct);

void initialize_serialization_header__contiguous_array(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Quantity__u32 size_of__struct);

Serialization_Header *get_p_serialization_header_from__contigious_array(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Index__u32 index_of__serialized_header);

static inline
void initialize_serialization_header_for__deallocated_struct(
        Serialization_Header *p_serialization_header,
        Quantity__u32 size_of__struct) {
    initialize_serialization_header(
            p_serialization_header,
            IDENTIFIER__UNKNOWN__u32,
            size_of__struct);
}

///
/// For a contiguous array of structs with
/// _serialization_header as the first member
/// this function will find the first instance of
/// that contigous range which has a IDENTIFIER__UNKNOWN__u32.
///
/// NOTE: if a serialization header is found, it's identifier
/// will be randomly assigned.
///
/// Returns null if it fails to find such an instance.
///
Serialization_Header *get_next_available_p_serialization_header(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 quantity_of__serialization_headers);

static inline
bool is_identifier_u32_matching__serialization_header(
        Identifier__u32 identifier__u32,
        Serialization_Header *p_serialization_header) {
#ifndef NDEBUG
    if (!p_serialization_header) {
        debug_abort("is_identifier_u32__serialization_header, p_serialized_header is null.");
        return false;
    }
#endif
    return identifier__u32
        == p_serialization_header->uuid;
}

static inline
bool is_serialized_struct__deallocated(
        Serialization_Header *p_serialization_header) {
    return p_serialization_header->uuid
        == IDENTIFIER__UNKNOWN__u32;
}

#endif
