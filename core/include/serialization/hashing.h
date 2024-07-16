#ifndef HASHING_H
#define HASHING_H

#include "defines_weak.h"
#include <defines.h>

Serialization_Header *poll_for__uuid_collision(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 *r_identifier__u32);

///
/// Takes a return-oriented pointer r_identifier__u32
/// which might be modified prior to return, and
/// returns a Serialization_Header ptr to the element
/// within the contiguous array p_serialization_headers
/// that corresponds to the r_identifier__u32
///
/// if r_identifier__u32 is initially IDENTIFIER__UNKNOWN__u32
/// it will be given a random value. So if you want a
/// random value, be sure to initialize r_identifier__u32
/// as IDENTIFIER__UNKNOWN__u32 prior to invoking this
/// function.
///
Serialization_Header *get_unique__hashed_uuid_u32(
        Game *p_game,
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 *r_identifier__u32);

static inline
Serialization_Header *dehash_identitier_in__contigious_array(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 identifier__u32) {
    return poll_for__uuid_collision(
                p_serialization_headers, 
                length_of__p_serialization_headers,
                &identifier__u32);
}

///
/// Wrapper invocation for get_unique__hashed_uuid_u32.
/// Will always modify r_identifier__u32 to a random
/// value.
///
static inline
Serialization_Header *get_random_unique__hashed_uuid_u32(
        Game *p_game,
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 *r_identifier__u32) {
    *r_identifier__u32 = IDENTIFIER__UNKNOWN__u32;
    return get_unique__hashed_uuid_u32(
            p_game, 
            p_serialization_headers, 
            length_of__p_serialization_headers,
            r_identifier__u32);
}

static inline
Identifier__u32 bound_uuid_to__contiguous_array(
        Identifier__u32 identifier,
        Quantity__u32 quantity_of__elements) {
    return identifier % quantity_of__elements;
}

#endif
