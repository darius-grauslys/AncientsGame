#include "defines.h"
#include "defines_weak.h"
#include "serialization/identifiers.h"
#include "serialization/serialization_header.h"
#include "serialization/serialized_field.h"
#include "serialization/hashing.h"

Serialization_Header *poll_for__uuid_collision(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 *r_identifier__u32) {

    Identifier__u32 identifier__mod_size = 
        *r_identifier__u32 
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
                    current_identifier,
                    p_serialization_header)) {
            *r_identifier__u32 =
                *r_identifier__u32
                - identifier__mod_size
                + current_identifier
                ;
            return p_serialization_header;
        }
    } while ((current_identifier = (current_identifier + 1) 
                % length_of__p_serialization_headers)
            != identifier__mod_size);

    *r_identifier__u32 =
        IDENTIFIER__UNKNOWN__u32;
    return 0;
}

Serialization_Header *get_unique__hashed_uuid_u32(
        Game *p_game,
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 *r_identifier__u32) {
    *r_identifier__u32 = 
        (IDENTIFIER__UNKNOWN__u32 != *r_identifier__u32)
        ? *r_identifier__u32
        : get_random__uuid_u32(p_game)
        ;

    return poll_for__uuid_collision(
            p_serialization_headers, 
            length_of__p_serialization_headers, 
            r_identifier__u32);
}
