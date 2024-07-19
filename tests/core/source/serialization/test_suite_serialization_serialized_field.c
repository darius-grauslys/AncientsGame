#include "defines.h"
#include "defines_weak.h"
#include "serialization/serialized_field.h"
#include "test_util.h"
#include <serialization/test_suite_serialization_serialized_field.h>
#include <serialization/test_suite_serialization_serialization_header.h>

#include <serialization/serialized_field.c>

TEST_FUNCTION(initialize_serialized_field) {
    Serialized_Field s_field;
    Identifier__u32 uuid =
        munit_rand_uint32();
    initialize_serialized_field(
            &s_field, 
            &s_field, 
            uuid);

    munit_assert_uint(
            s_field.identifier_for__serialized_field,
            ==,
            uuid);
    munit_assert_uint(
            s_field._serialization_header.uuid,
            ==,
            uuid);
    munit_assert_uint(
            s_field._serialization_header.size_of__struct,
            ==,
            sizeof(Serialized_Field));

    munit_assert_ptr(
            s_field.p_serialized_field__data,
            ==,
            &s_field);
    munit_assert_ptr(
            s_field.p_serialized_field__data,
            ==,
            s_field.p_serialized_field__chunk);
    munit_assert_ptr(
            s_field.p_serialized_field__data,
            ==,
            s_field.p_serialized_field__entity);
    munit_assert_ptr(
            s_field.p_serialized_field__data,
            ==,
            s_field.p_serialized_field__inventory);
    munit_assert_ptr(
            s_field.p_serialized_field__data,
            ==,
            s_field.p_serialized_field__item_stack);
    munit_assert_ptr(
            s_field.p_serialized_field__data,
            ==,
            s_field.p_serialized_field__serialization_header);
    return MUNIT_OK;
}

TEST_FUNCTION(link_serialized_field) {
    Test_Serialization_Header headers[256];
    initialize_test_serialization_header__contiguous_array(
            headers, 256);

    Index__u32 index = 
        munit_rand_uint32() % 256;

    Serialized_Field s_field;

    initialize_serialized_field_as__unlinked(
            &s_field, 
            headers[index]._serialization_header.uuid);

    munit_assert_true(
            link_serialized_field_against__contiguous_array(
                &s_field, 
                (Serialization_Header*)headers, 
                256)
            );

    munit_assert_ptr(
            s_field.p_serialized_field__data,
            ==, 
            &headers[index]);

    return MUNIT_OK;
}

TEST_FUNCTION(point_serialized_field_to__this_serialized_struct) {
    Test_Serialization_Header header;
    Serialized_Field s_field;

    initialize_test_serialization_header(
            &header, 
            munit_rand_uint32());

    initialize_serialized_field_as__unassigned(
            &s_field);

    point_serialized_field_to__this_serialized_struct(
            &s_field, 
            &header);

    munit_assert_true(
            is_p_serialized_field__linked(&s_field)
            );

    return MUNIT_OK;
}

DEFINE_SUITE(serialized_field,
        INCLUDE_TEST__STATELESS
            (initialize_serialized_field),
        INCLUDE_TEST__STATELESS
            (link_serialized_field),
        INCLUDE_TEST__STATELESS
            (point_serialized_field_to__this_serialized_struct),
        END_TESTS)
