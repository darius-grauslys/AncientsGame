#include "defines_weak.h"
#include <test_util.h>

#include <defines.h>

#define TEST_SERIALIZATION_HEADER_BYTES_QUANTITY_OF 256

typedef struct Test_Serialization_Header_t {
    Serialization_Header _serialization_header;
    u8 bytes[TEST_SERIALIZATION_HEADER_BYTES_QUANTITY_OF];
} Test_Serialization_Header;

void initialize_test_serialization_header(
        Test_Serialization_Header
            *p_test_serialization_header,
        Identifier__u32 identifier);

void initialize_test_serialization_header__contiguous_array(
        Test_Serialization_Header *p_test_headers,
        Quantity__u32 length_of__p_test_headers);

DECLARE_SUITE(serialization_header)
