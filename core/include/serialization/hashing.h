#ifndef HASHING_H
#define HASHING_H

#include "defines_weak.h"
#include "numerics.h"
#include "serialization/identifiers.h"
#include "serialization/serialization_header.h"
#include <defines.h>

///
/// Returns an index to a contiguous array
/// that points to a matching uuid.
/// In particular, this handles uuid collisions.
///
/// A collision is when the UUID mod (%) length_of__p_serialization_headers
/// happens to be congruent (same number after mod) with
/// another UUID also mod'd by length_of__p_serialization_headers.
///
/// Returns INDEX__UNKNOWN__u32 if the UUID is not found.
///
Index__u32 poll_for__uuid_collision(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 identifier__u32);

Identifier__u32 get_next_available__uuid_in__contiguous_array(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 uuid);

static inline
Identifier__u32 get_next_available__random_uuid_in__contiguous_array(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Repeatable_Psuedo_Random *p_randomizer) {
    Identifier__u32 uuid=
        get_random__uuid_u32(p_randomizer);
    return get_next_available__uuid_in__contiguous_array(
            p_serialization_headers, 
            length_of__p_serialization_headers, 
            uuid);
}

static inline
bool has_uuid_in__contiguous_array(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 identifier__u32) {
    return poll_for__uuid_collision(
            p_serialization_headers, 
            length_of__p_serialization_headers, 
            identifier__u32)
        != INDEX__UNKNOWN__u32;
}

static inline
Serialization_Header *dehash_identitier_u32_in__contigious_array(
        Serialization_Header *p_serialization_headers,
        Quantity__u32 length_of__p_serialization_headers,
        Identifier__u32 identifier__u32) {
    Index__u32 index__u32 = 
        poll_for__uuid_collision(
                p_serialization_headers, 
                length_of__p_serialization_headers,
                identifier__u32);
    if (is_index_u32__out_of_bounds(index__u32))
        return 0;
    return get_p_serialization_header_from__contigious_array(
            p_serialization_headers, 
            length_of__p_serialization_headers, 
            index__u32);
}

static inline
Identifier__u32 bound_uuid_to__contiguous_array(
        Identifier__u32 identifier,
        Quantity__u32 quantity_of__elements) {
    return identifier % quantity_of__elements;
}

#endif
