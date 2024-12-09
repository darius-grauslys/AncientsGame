#include "defines.h"
#include "defines_weak.h"
#include "serialization/hashing.h"
#include "serialization/serialization_header.h"
#include "test_util.h"
#include <serialization/test_suite_serialization_hashing.h>
#include <serialization/test_suite_serialization_serialization_header.h>

#include <serialization/hashing.c>

void initialize_test_serialization_header__contiguous_array_for__hashing_tests(
        Test_Serialization_Header *p_test_headers, 
        Quantity__u32 length_of__p_test_headers) {
    initialize_serialization_header__contiguous_array(
            (Serialization_Header*)p_test_headers,
            length_of__p_test_headers,
            sizeof(Test_Serialization_Header));
    for (Index__u32 index_of__test_header = 0;
            index_of__test_header
            < length_of__p_test_headers;
            index_of__test_header++) {
        Identifier__u32 uuid = 
            munit_rand_uint32();
        Identifier__u32 uuid__bounded =
            uuid % length_of__p_test_headers;
        uuid =
            uuid 
            - uuid__bounded
            + index_of__test_header
            ;
        initialize_test_serialization_header(
                &p_test_headers[index_of__test_header], 
                uuid);
    }
}

TEST_FUNCTION(poll_for__uuid_collision__no_collision) {
    const uint32_t length_of__headers = 256;
    Test_Serialization_Header headers[length_of__headers];
    initialize_test_serialization_header__contiguous_array_for__hashing_tests(
            headers, 
            length_of__headers);

    Index__u32 index =
        munit_rand_uint32() % length_of__headers;
    Index__u32 index__collision_resolved =
        poll_for__uuid_collision(
                (Serialization_Header*)headers, 
                length_of__headers, 
                headers[index]._serialization_header.uuid);
    munit_assert_uint(
            index, 
            ==, 
            index__collision_resolved);

    return MUNIT_OK;
}

TEST_FUNCTION(poll_for__uuid_collision__deliberate_collision) {
    const uint32_t length_of__headers = 256;
    Test_Serialization_Header headers[length_of__headers];
    initialize_test_serialization_header__contiguous_array_for__hashing_tests(
            headers, 
            length_of__headers);

    Index__u32 index =
        (munit_rand_uint32() % (length_of__headers >> 1));
    Index__u32 index__offset =
        index
        + (munit_rand_uint32() % (length_of__headers >> 2))
        ;
    Identifier__u32 uuid =
        headers[index]._serialization_header.uuid;
    headers[index]._serialization_header.uuid =
        headers[index__offset]._serialization_header.uuid;
    headers[index__offset]._serialization_header.uuid = uuid;
    Index__u32 index__collision_resolved =
        poll_for__uuid_collision(
                (Serialization_Header*)headers, 
                length_of__headers, 
                headers[index__offset]._serialization_header.uuid);
    munit_assert_uint(
            index__offset, 
            ==, 
            index__collision_resolved);

    return MUNIT_OK;
}

TEST_FUNCTION(has_uuid_in__contiguous_array) {
    const uint32_t length_of__headers = 256;
    Test_Serialization_Header headers[length_of__headers];
    initialize_test_serialization_header__contiguous_array_for__hashing_tests(
            headers, 
            length_of__headers);
    Index__u32 index =
        munit_rand_uint32() % length_of__headers;
    munit_assert_true(
            has_uuid_in__contiguous_array(
                (Serialization_Header*)headers, 
                length_of__headers, 
                headers[index]._serialization_header.uuid));
    munit_assert_false(
            has_uuid_in__contiguous_array(
                (Serialization_Header*)headers, 
                length_of__headers, 
                IDENTIFIER__UNKNOWN__u32));
    return MUNIT_OK;
}

DEFINE_SUITE(hashing,
        INCLUDE_TEST__STATELESS
            (poll_for__uuid_collision__no_collision),
        INCLUDE_TEST__STATELESS
            (poll_for__uuid_collision__deliberate_collision),
        INCLUDE_TEST__STATELESS
            (has_uuid_in__contiguous_array),
        END_TESTS)
