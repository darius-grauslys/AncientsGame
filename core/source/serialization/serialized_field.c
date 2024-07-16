#include "defines.h"
#include "defines_weak.h"
#include "serialization/hashing.h"
#include <serialization/serialized_field.h>
#include <serialization/serialization_header.h>

void initialize_serialized_field(
        Serialized_Field *p_serialized_field,
        void *p_serialized_field__data,
        Identifier__u32 identifier_for__serialized_field) {
    initialize_serialization_header(
            &p_serialized_field->_serialization_header, 
            identifier_for__serialized_field, 
            sizeof(Serialized_Field));
    p_serialized_field
        ->p_serialized_field__data =
        p_serialized_field__data;
}

bool link_serialized_field(
        Serialized_Field *p_serialized_field,
        Serialization_Header *p_serialization_structs,
        Quantity__u32 quantity_of__structs) {
#ifndef NDEBUG
    if (!p_serialization_structs) {
        debug_abort("link_serialized_field, p_serialized_structs is null.");
        return false;
    }
    if (!p_serialized_field) {
        debug_abort("link_serialized_field, p_serialized_field is null.");
        return false;
    }
#else
    if (!p_serialization_structs
            || !p_serialized_field)
        return false;
#endif

    Identifier__u32 bounded_uuid =
        bound_uuid_to__contiguous_array(
                p_serialized_field->identifier_for__serialized_field,
                quantity_of__structs);

    uint8_t *p_bytes = (uint8_t*)p_serialization_structs;
    Quantity__u32 size_of__struct = 
        p_serialization_structs->size_of__struct;

    Serialization_Header *p_serialization_header =
        (Serialization_Header*)(
                p_bytes + (size_of__struct * bounded_uuid));

    if (is_serialized_struct__deallocated(p_serialization_header)) {
        initialize_serialized_field_as__unlinked(
                p_serialized_field, 
                p_serialized_field->identifier_for__serialized_field);
        return false;
    }

    p_serialized_field
        ->p_serialized_field__serialization_header =
        p_serialization_header;
    
    return true;
}

void point_serialized_field_to__this_serialized_struct(
        Serialized_Field *p_serialized_field,
        void *p_serialized_struct) {
    if (!p_serialized_field) {
        p_serialized_field->p_serialized_field__data = 0;
        p_serialized_field->identifier_for__serialized_field =
            IDENTIFIER__UNKNOWN__u32;
        return;
    }
    if (!p_serialized_struct) {
        return;
    }
    p_serialized_field->p_serialized_field__data =
        p_serialized_struct;
    p_serialized_field->identifier_for__serialized_field =
        ((Serialization_Header*)p_serialized_struct)
        ->uuid;
}
