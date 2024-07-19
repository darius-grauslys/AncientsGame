#include "defines.h"
#include "defines_weak.h"
#include "serialization/identifiers.h"
#include "serialization/serialization_header.h"
#include "serialization/serialized_field.h"
#include "serialization/hashing.h"

Index__u32 poll_for__uuid_collision(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 identifier__u32) {

    Identifier__u32 identifier__mod_size = 
        identifier__u32 
        % length_of__p_serialization_headers;
    Quantity__u32 size_of__struct =
        p_serialization_headers->size_of__struct;

    u8 *p_bytes = (u8*)p_serialization_headers;

    Identifier__u32 current_identifier = 
        identifier__mod_size;
    do {
        Serialization_Header *p_serialization_header =
            (Serialization_Header*)(
                    p_bytes
                    + current_identifier
                    * size_of__struct
                    );
        if (is_serialized_struct__deallocated(
                    p_serialization_header)
                || is_identifier_u32_matching__serialization_header(
                    identifier__u32,
                    p_serialization_header)) {
            return current_identifier;
        }
    } while ((current_identifier = (current_identifier + 1) 
                % length_of__p_serialization_headers)
            != identifier__mod_size);
    return INDEX__UNKNOWN__u32;
}

Identifier__u32 get_next_available__uuid_in__contiguous_array(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 uuid) {
    uuid -= (uuid % length_of__p_serialization_headers);
    Index__u32 index__u32 =
        poll_for__uuid_collision(
                p_serialization_headers, 
                length_of__p_serialization_headers, 
                uuid);
    uuid += index__u32;
    return uuid;
}

