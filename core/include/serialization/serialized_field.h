#ifndef SERIALIZED_FIELD_H
#define SERIALIZED_FIELD_H

#include "defines_weak.h"
#include "serialization/serialization_header.h"
#include <defines.h>

void initialize_serialized_field(
        Serialized_Field *p_serialized_field,
        void *p_serialized_field__data,
        Identifier__u32 identifier_for__serialized_field);

///
/// Iterates through a contiguous array of
/// structs with _serialization_header as their
/// first member field. Linking the p_serialized_field
/// to the first instance which matches in ID.
///
/// Returns true if the link is made, false otherwise.
///
bool link_serialized_field_against__contiguous_array(
        Serialized_Field *p_serialized_field,
        Serialization_Header *p_serialization_structs,
        Quantity__u32 quantity_of__structs);

///
/// WARNING: This has undefined behavior for 
/// structs that do not put Serialization_Header
/// as their FIRST member field.
///
static inline
bool is_serialized_field_matching__serialization_header(
        Serialized_Field *p_serialization_field,
        Serialization_Header *p_serialization_header) {
#ifndef NDEBUG
    if (!p_serialization_field) {
        debug_abort("is_serialized_field_matching__serialization_header, p_serialized_field is null.");
        return false;
    }
    if (!p_serialization_header) {
        debug_abort("is_serialized_field_matching__serialization_header, p_serialized_header is null.");
        return false;
    }
#endif
    return is_identifier_u32_matching__serialization_header(
            p_serialization_field->identifier_for__serialized_field,
            p_serialization_header);
}

void point_serialized_field_to__this_serialized_struct(
        Serialized_Field *p_serialized_field,
        void *p_serialized_struct);

static inline
void initialize_serialized_field_as__unassigned(
        Serialized_Field *p_serialized_field) {
    initialize_serialized_field(
            p_serialized_field, 
            0, 
            IDENTIFIER__UNKNOWN__u32);
}

static inline
void initialize_serialized_field_as__unlinked(
        Serialized_Field *p_serialized_field,
        Identifier__u32 identifier_for__serialized_field) {
    initialize_serialized_field(
            p_serialized_field, 
            0, 
            identifier_for__serialized_field);
}

static inline
bool is_p_serialized_field__linked(
        Serialized_Field *p_serialized_field) {
    ///
    /// 1) serialized_field__data points to something
    /// 2) the serialization_header of that ptr has a uuid
    /// 3) the uuid's match
    ///
    bool is_pointed =
        p_serialized_field
        ->p_serialized_field__data
        ;
    if (!is_pointed)
        return false;

    bool is_with__uuid =
        p_serialized_field
        ->p_serialized_field__serialization_header
        ->uuid != IDENTIFIER__UNKNOWN__u32
        ;
    bool is_with__same_uuid =
        p_serialized_field
        ->identifier_for__serialized_field
        == p_serialized_field
            ->p_serialized_field__serialization_header
            ->uuid
        ;
    return is_pointed
        && is_with__uuid
        && is_with__same_uuid
        ;
}

static inline
Inventory *get_p_inventory_from__serialized_field(
        Serialized_Field *p_serialized_field) {
    return p_serialized_field->p_serialized_field__inventory;
}

static inline
Entity *get_p_entity_from__serialized_field(
        Serialized_Field *p_serialized_field) {
    return p_serialized_field->p_serialized_field__entity;
}

static inline
Chunk *get_p_chunk_from__serialized_field(
        Serialized_Field *p_serialized_field) {
    return p_serialized_field->p_serialized_field__chunk;
}

#endif
