#include "defines.h"
#include "defines_weak.h"
#include <serialization/serialized_field.h>
#include <serialization/serialization_header.h>

void initialize_serialized_field(
        Serialized_Field *p_serialized_field,
        void *p_serialized_field__data,
        Identifier__u32 identifier_for__serialized_field) {
    p_serialized_field
        ->p_serialized_field__data =
        p_serialized_field__data;
    p_serialized_field
        ->identifier_for__serialized_field =
        identifier_for__serialized_field;
}

bool is_serialized_field_matching__serialization_header(
        Serialized_Field *p_serialization_field,
        void *p_serialized_struct) {
    if (!p_serialized_struct)
        return false;

    Serialization_Header *p_serialization_header =
        (Serialization_Header*)p_serialized_struct;

    return p_serialization_field->identifier_for__serialized_field
        == p_serialization_header->identifier_for__serialized_struct;
}

bool link_serialized_field(
        Serialized_Field *p_serialized_field,
        Serialization_Header *p_serialization_structs,
        Quantity__u32 quantity_of__structs) {
    if (!p_serialization_structs
            || !p_serialized_field)
        return false;
    uint8_t *p_bytes = (uint8_t*)p_serialization_structs;
    Quantity__u32 size_of__struct = 
        ((Serialization_Header*)p_serialization_structs)
        ->size_of__serialized_struct;

    for (Quantity__u32 step = 0;
            step < quantity_of__structs;
            step++) {
        if (is_serialized_field_matching__serialization_header(
                    p_serialized_field, p_bytes)) {
            p_serialized_field->p_serialized_field__data =
                p_bytes;
            return true;
        }
        p_bytes += size_of__struct;
    }
    return false;
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
        ->identifier_for__serialized_struct;
}
