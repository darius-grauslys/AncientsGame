#include "defines.h"
#include "defines_weak.h"
#include "random.h"
#include "serialization/hashing.h"
#include "serialization/identifiers.h"
#include "serialization/serialization_header.h"
#include "test_util.h"
#include <serialization/test_suite_serialization_serialization_header.h>

#include <serialization/serialization_header.c>

void initialize_test_serialization_header(
        Test_Serialization_Header
            *p_test_serialization_header,
        Identifier__u32 identifier) {
    for (Index__u32 index_of__byte = 0;
            index_of__byte
            < TEST_SERIALIZATION_HEADER_BYTES_QUANTITY_OF;
            index_of__byte++) {
        p_test_serialization_header
            ->bytes[index_of__byte] = index_of__byte;
    }
    initialize_serialization_header(
            &p_test_serialization_header
            ->_serialization_header, 
            identifier, 
            sizeof(Test_Serialization_Header));
}

void initialize_test_serialization_header__contiguous_array(
        Test_Serialization_Header *p_test_headers,
        Quantity__u32 length_of__p_test_headers) {
    Repeatable_Psuedo_Random randomizer;
    initialize_repeatable_psuedo_random(
            &randomizer, 
            (u32)(uint64_t)p_test_headers);
    initialize_serialization_header__contiguous_array(
            (Serialization_Header*)p_test_headers,
            length_of__p_test_headers,
            sizeof(Test_Serialization_Header));
    for (Index__u32 index_of__test_header = 0;
            index_of__test_header
            < length_of__p_test_headers;
            index_of__test_header++) {
        Identifier__u32 uuid = 
            get_random__uuid_u32(&randomizer);
        Index__u32 index__collision_resolved =
            poll_for__uuid_collision(
                    (Serialization_Header*)p_test_headers, 
                    length_of__p_test_headers, 
                    uuid);
        initialize_test_serialization_header(
                &p_test_headers[index__collision_resolved], 
                uuid);
    }
}

MunitResult assert_test_serialization_header_bytes_are__unaffected(
        Test_Serialization_Header
            *p_test_serialization_header) {
    for (Index__u32 index_of__byte = 0;
            index_of__byte
            < TEST_SERIALIZATION_HEADER_BYTES_QUANTITY_OF;
            index_of__byte++) {
        munit_assert_uchar(
                p_test_serialization_header->bytes[index_of__byte], 
                ==, 
                index_of__byte);
    }

    return MUNIT_OK;
}

TEST_FUNCTION(initialize_serialization_header) {
    Test_Serialization_Header 
        test_serialization_header;

    Identifier__u32 uuid =
        munit_rand_uint32();

    initialize_test_serialization_header(
            &test_serialization_header, 
            uuid);
    
    munit_assert_int(
            test_serialization_header
            ._serialization_header.uuid,
            ==,
            uuid);
    munit_assert_int(
            test_serialization_header
                ._serialization_header
                .size_of__struct,
            ==,
            sizeof(Test_Serialization_Header));
    return MUNIT_OK;
}

TEST_FUNCTION(get_p_serialization_header_from__contigious_array) {
    Test_Serialization_Header headers[256];
    initialize_test_serialization_header__contiguous_array(
            headers, 
            256);
    
    for (Quantity__u32 step = 0;
            step < 512;
            step++ ){
        Index__u32 index = 
            munit_rand_uint32() % 256;
        Serialization_Header
            *p_serialization_header =
            get_p_serialization_header_from__contigious_array(
                    (Serialization_Header*)headers, 
                    256, 
                    index);

        munit_assert_ptr(
                &headers[index]._serialization_header, 
                ==, 
                p_serialization_header);
        assert_test_serialization_header_bytes_are__unaffected(
                &headers[index]);
    }

    return MUNIT_OK;
}

TEST_FUNCTION(get_next_available_p_serialization_header) {
    Test_Serialization_Header headers[256];
    initialize_test_serialization_header__contiguous_array(
            headers, 
            256);

    Index__u32 index = 
        munit_rand_uint32() % 256;

    initialize_serialization_header_for__deallocated_struct(
            &headers[index]._serialization_header, 
            sizeof(Test_Serialization_Header));

    Serialization_Header *p_serialization_header =
        get_next_available_p_serialization_header(
                (Serialization_Header*)headers, 
                256);

    munit_assert_ptr(
            p_serialization_header,
            ==,
            &headers[index]);

    return MUNIT_OK;
}

DEFINE_SUITE(serialization_header,
        INCLUDE_TEST__STATELESS
            (initialize_serialization_header),
        INCLUDE_TEST__STATELESS
            (get_p_serialization_header_from__contigious_array),
        INCLUDE_TEST__STATELESS
            (get_next_available_p_serialization_header),
        END_TESTS)
