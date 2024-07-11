#include <degree.h>
#include <defines.h>
#include <vectors.h>

Vector__3i32F8 __DEGREE_TO_2i32F10__LOOKUP_TABLE[256] = {
    { 0b00000000,  0b11111111, 0 },
    { 0b00000110,  0b11111111, 0 },
    { 0b00001100,  0b11111111, 0 },
    { 0b00010010,  0b11111111, 0 },
    { 0b00011001,  0b11111110, 0 },
    { 0b00011111,  0b11111110, 0 },
    { 0b00100101,  0b11111101, 0 },
    { 0b00101011,  0b11111100, 0 },
    { 0b00110010,  0b11111011, 0 },
    { 0b00111000,  0b11111001, 0 },
    { 0b00111110,  0b11111000, 0 },
    { 0b01000100,  0b11110110, 0 },
    { 0b01001010,  0b11110100, 0 },
    { 0b01010000,  0b11110010, 0 },
    { 0b01010110,  0b11110000, 0 },
    { 0b01011100,  0b11101110, 0 },
    { 0b01100010,  0b11101100, 0 },
    { 0b01101000,  0b11101001, 0 },
    { 0b01101101,  0b11100111, 0 },
    { 0b01110011,  0b11100100, 0 },
    { 0b01111001,  0b11100001, 0 },
    { 0b01111110,  0b11011110, 0 },
    { 0b10000100,  0b11011011, 0 },
    { 0b10001001,  0b11011000, 0 },
    { 0b10001110,  0b11010100, 0 },
    { 0b10010011,  0b11010000, 0 },
    { 0b10011000,  0b11001101, 0 },
    { 0b10011101,  0b11001001, 0 },
    { 0b10100010,  0b11000101, 0 },
    { 0b10100111,  0b11000001, 0 },
    { 0b10101100,  0b10111101, 0 },
    { 0b10110000,  0b10111000, 0 },
    { 0b10110101,  0b10110100, 0 },
    { 0b10111001,  0b10110000, 0 },
    { 0b10111110,  0b10101011, 0 },
    { 0b11000010,  0b10100110, 0 },
    { 0b11000110,  0b10100001, 0 },
    { 0b11001010,  0b10011100, 0 },
    { 0b11001110,  0b10010111, 0 },
    { 0b11010001,  0b10010010, 0 },
    { 0b11010101,  0b10001101, 0 },
    { 0b11011000,  0b10001000, 0 },
    { 0b11011100,  0b10000010, 0 },
    { 0b11011111,  0b01111101, 0 },
    { 0b11100010,  0b01110111, 0 },
    { 0b11100101,  0b01110010, 0 },
    { 0b11100111,  0b01101100, 0 },
    { 0b11101010,  0b01100110, 0 },
    { 0b11101100,  0b01100001, 0 },
    { 0b11101111,  0b01011011, 0 },
    { 0b11110001,  0b01010101, 0 },
    { 0b11110011,  0b01001111, 0 },
    { 0b11110101,  0b01001001, 0 },
    { 0b11110111,  0b01000011, 0 },
    { 0b11111000,  0b00111101, 0 },
    { 0b11111010,  0b00110110, 0 },
    { 0b11111011,  0b00110000, 0 },
    { 0b11111100,  0b00101010, 0 },
    { 0b11111101,  0b00100100, 0 },
    { 0b11111110,  0b00011110, 0 },
    { 0b11111110,  0b00010111, 0 },
    { 0b11111111,  0b00010001, 0 },
    { 0b11111111,  0b00001011, 0 },
    { 0b11111111,  0b00000100, 0 },
    { 0b11111111,  0b00000010, 0 },
    { 0b11111111,  0b00000000, 0 }, // { 0b11111111, -0b00000001, 0 }, // old [64]
    { 0b11111111, -0b00000111, 0 },
    { 0b11111111, -0b00001101, 0 },
    { 0b11111111, -0b00010100, 0 },
    { 0b11111110, -0b00011010, 0 },
    { 0b11111101, -0b00100000, 0 },
    { 0b11111101, -0b00100111, 0 },
    { 0b11111011, -0b00101101, 0 },
    { 0b11111010, -0b00110011, 0 },
    { 0b11111001, -0b00111001, 0 },
    { 0b11110111, -0b00111111, 0 },
    { 0b11110110, -0b01000101, 0 },
    { 0b11110100, -0b01001011, 0 },
    { 0b11110010, -0b01010001, 0 },
    { 0b11110000, -0b01010111, 0 },
    { 0b11101110, -0b01011101, 0 },
    { 0b11101011, -0b01100011, 0 },
    { 0b11101001, -0b01101001, 0 },
    { 0b11100110, -0b01101111, 0 },
    { 0b11100011, -0b01110100, 0 },
    { 0b11100000, -0b01111010, 0 },
    { 0b11011101, -0b01111111, 0 },
    { 0b11011010, -0b10000101, 0 },
    { 0b11010111, -0b10001010, 0 },
    { 0b11010011, -0b10001111, 0 },
    { 0b11010000, -0b10010100, 0 },
    { 0b11001100, -0b10011010, 0 },
    { 0b11001000, -0b10011111, 0 },
    { 0b11000100, -0b10100011, 0 },
    { 0b11000000, -0b10101000, 0 },
    { 0b10111100, -0b10101101, 0 },
    { 0b10111000, -0b10110001, 0 },
    { 0b10110011, -0b10110110, 0 },
    { 0b10101111, -0b10111010, 0 },
    { 0b10101010, -0b10111111, 0 },
    { 0b10100101, -0b11000011, 0 },
    { 0b10100000, -0b11000111, 0 },
    { 0b10011011, -0b11001011, 0 },
    { 0b10010110, -0b11001110, 0 },
    { 0b10010001, -0b11010010, 0 },
    { 0b10001100, -0b11010110, 0 },
    { 0b10000111, -0b11011001, 0 },
    { 0b10000001, -0b11011100, 0 },
    { 0b01111100, -0b11011111, 0 },
    { 0b01110110, -0b11100010, 0 },
    { 0b01110001, -0b11100101, 0 },
    { 0b01101011, -0b11101000, 0 },
    { 0b01100101, -0b11101010, 0 },
    { 0b01011111, -0b11101101, 0 },
    { 0b01011001, -0b11101111, 0 },
    { 0b01010011, -0b11110001, 0 },
    { 0b01001101, -0b11110011, 0 },
    { 0b01000111, -0b11110101, 0 },
    { 0b01000001, -0b11110111, 0 },
    { 0b00111011, -0b11111000, 0 },
    { 0b00110101, -0b11111010, 0 },
    { 0b00101111, -0b11111011, 0 },
    { 0b00101001, -0b11111100, 0 },
    { 0b00100010, -0b11111101, 0 },
    { 0b00011100, -0b11111110, 0 },
    { 0b00010110, -0b11111111, 0 },
    { 0b00010000, -0b11111111, 0 },
    { 0b00001001, -0b11111111, 0 },
    { 0b00000010, -0b11111111, 0 },
    { 0b00000000, -0b11111111, 0 }, // { 0b00000011, -0b11111111, 0 }, // old [128]
    {-0b00000010, -0b11111111, 0 },
    {-0b00001001, -0b11111111, 0 },
    {-0b00001111, -0b11111111, 0 },
    {-0b00010101, -0b11111111, 0 },
    {-0b00011011, -0b11111110, 0 },
    {-0b00100010, -0b11111101, 0 },
    {-0b00101000, -0b11111100, 0 },
    {-0b00101110, -0b11111011, 0 },
    {-0b00110100, -0b11111010, 0 },
    {-0b00111010, -0b11111001, 0 },
    {-0b01000001, -0b11110111, 0 },
    {-0b01000111, -0b11110101, 0 },
    {-0b01001101, -0b11110100, 0 },
    {-0b01010011, -0b11110010, 0 },
    {-0b01011001, -0b11110000, 0 },
    {-0b01011110, -0b11101101, 0 },
    {-0b01100100, -0b11101011, 0 },
    {-0b01101010, -0b11101000, 0 },
    {-0b01110000, -0b11100110, 0 },
    {-0b01110101, -0b11100011, 0 },
    {-0b01111011, -0b11100000, 0 },
    {-0b10000000, -0b11011101, 0 },
    {-0b10000110, -0b11011001, 0 },
    {-0b10001011, -0b11010110, 0 },
    {-0b10010000, -0b11010011, 0 },
    {-0b10010110, -0b11001111, 0 },
    {-0b10011011, -0b11001011, 0 },
    {-0b10100000, -0b11000111, 0 },
    {-0b10100100, -0b11000011, 0 },
    {-0b10101001, -0b10111111, 0 },
    {-0b10101110, -0b10111011, 0 },
    {-0b10110010, -0b10110111, 0 },
    {-0b10110111, -0b10110010, 0 },
    {-0b10111011, -0b10101110, 0 },
    {-0b10111111, -0b10101001, 0 },
    {-0b11000100, -0b10100100, 0 },
    {-0b11001000, -0b10011111, 0 },
    {-0b11001011, -0b10011010, 0 },
    {-0b11001111, -0b10010101, 0 },
    {-0b11010011, -0b10010000, 0 },
    {-0b11010110, -0b10001011, 0 },
    {-0b11011010, -0b10000101, 0 },
    {-0b11011101, -0b10000000, 0 },
    {-0b11100000, -0b01111011, 0 },
    {-0b11100011, -0b01110101, 0 },
    {-0b11100110, -0b01101111, 0 },
    {-0b11101000, -0b01101010, 0 },
    {-0b11101011, -0b01100100, 0 },
    {-0b11101101, -0b01011110, 0 },
    {-0b11110000, -0b01011000, 0 },
    {-0b11110010, -0b01010010, 0 },
    {-0b11110100, -0b01001100, 0 },
    {-0b11110110, -0b01000110, 0 },
    {-0b11110111, -0b01000000, 0 },
    {-0b11111001, -0b00111010, 0 },
    {-0b11111010, -0b00110100, 0 },
    {-0b11111011, -0b00101110, 0 },
    {-0b11111100, -0b00100111, 0 },
    {-0b11111101, -0b00100001, 0 },
    {-0b11111110, -0b00011011, 0 },
    {-0b11111111, -0b00010101, 0 },
    {-0b11111111, -0b00001110, 0 },
    {-0b11111111, -0b00000100, 0 },
    {-0b11111111,  0b00000000, 0 }, //{-0b11111111, -0b00001000, 0 }, // old [192]
    {-0b11111111,  0b00001010, 0 },
    {-0b11111111,  0b00010000, 0 },
    {-0b11111110,  0b00010110, 0 },
    {-0b11111110,  0b00011101, 0 },
    {-0b11111101,  0b00100011, 0 },
    {-0b11111100,  0b00101001, 0 },
    {-0b11111011,  0b00101111, 0 },
    {-0b11111010,  0b00110110, 0 },
    {-0b11111000,  0b00111100, 0 },
    {-0b11110111,  0b01000010, 0 },
    {-0b11110101,  0b01001000, 0 },
    {-0b11110011,  0b01001110, 0 },
    {-0b11110001,  0b01010100, 0 },
    {-0b11101111,  0b01011010, 0 },
    {-0b11101101,  0b01100000, 0 },
    {-0b11101010,  0b01100110, 0 },
    {-0b11101000,  0b01101011, 0 },
    {-0b11100101,  0b01110001, 0 },
    {-0b11100010,  0b01110111, 0 },
    {-0b11011111,  0b01111100, 0 },
    {-0b11011100,  0b10000010, 0 },
    {-0b11011001,  0b10000111, 0 },
    {-0b11010101,  0b10001100, 0 },
    {-0b11010010,  0b10010010, 0 },
    {-0b11001110,  0b10010111, 0 },
    {-0b11001010,  0b10011100, 0 },
    {-0b11000110,  0b10100001, 0 },
    {-0b11000010,  0b10100101, 0 },
    {-0b10111110,  0b10101010, 0 },
    {-0b10111010,  0b10101111, 0 },
    {-0b10110110,  0b10110011, 0 },
    {-0b10110001,  0b10111000, 0 },
    {-0b10101101,  0b10111100, 0 },
    {-0b10101000,  0b11000000, 0 },
    {-0b10100011,  0b11000100, 0 },
    {-0b10011110,  0b11001000, 0 },
    {-0b10011001,  0b11001100, 0 },
    {-0b10010100,  0b11010000, 0 },
    {-0b10001111,  0b11010100, 0 },
    {-0b10001010,  0b11010111, 0 },
    {-0b10000100,  0b11011010, 0 },
    {-0b01111111,  0b11011110, 0 },
    {-0b01111001,  0b11100001, 0 },
    {-0b01110100,  0b11100100, 0 },
    {-0b01101110,  0b11100110, 0 },
    {-0b01101000,  0b11101001, 0 },
    {-0b01100011,  0b11101100, 0 },
    {-0b01011101,  0b11101110, 0 },
    {-0b01010111,  0b11110000, 0 },
    {-0b01010001,  0b11110010, 0 },
    {-0b01001011,  0b11110100, 0 },
    {-0b01000101,  0b11110110, 0 },
    {-0b00111111,  0b11111000, 0 },
    {-0b00111001,  0b11111001, 0 },
    {-0b00110010,  0b11111010, 0 },
    {-0b00101100,  0b11111100, 0 },
    {-0b00100110,  0b11111101, 0 },
    {-0b00100000,  0b11111101, 0 },
    {-0b00011010,  0b11111110, 0 },
    {-0b00010011,  0b11111111, 0 },
    {-0b00001101,  0b11111111, 0 },
    {-0b00000111,  0b11111111, 0 },
};

Vector__3i32F4 get_2i32F4_offset_from__angle(
        Degree__u8 angle) {
    return vector_3i32F8_to__vector_3i32F4(
            __DEGREE_TO_2i32F10__LOOKUP_TABLE[angle]);
}

Vector__3i32F8 get_2i32F8_offset_from__angle(
        Degree__u8 angle) {
    return __DEGREE_TO_2i32F10__LOOKUP_TABLE[angle];
}

i32F8 get_middle_angle(
        i32F8 degree__one,
        i32F8 degree__two) {
    if (degree__one < degree__two)
        return (degree__one + degree__two) >> 1;
    return ((degree__one + degree__two + 256) >> 1);
}

Degree__u8 get_angle_between__vectors_3i32F4(
        Vector__3i32F4 source__3i32F4, 
        Vector__3i32F4 target__3i32F4) {
    i32F8 pivots[2];
    i32F8 *p_pivot__d_x, *p_pivot__d_y;

    // step 1) find cartesian quadrant

    i32 d_x = 
        target__3i32F4.x__i32F4
        - source__3i32F4.x__i32F4
        ;
    i32 d_y = 
        target__3i32F4.y__i32F4
        - source__3i32F4.y__i32F4
        ;

    // trivial cases
    if (!d_x && !d_y)
        return 0;
    if (!d_x)
        return 
            (d_y < 0)
            ? 128
            : 0
            ;
    if (!d_y)
        return
            (d_x < 0)
            ? 192
            : 64
            ;

    if (d_x > 0 && d_y > 0) {
        // quad 1 (x+, y+) 
        pivots[0] = i32_to__i32F8(0);
        pivots[1] = i32_to__i32F8(64);

        p_pivot__d_x = &pivots[1];
        p_pivot__d_y = &pivots[0];
    } else if (d_x > 0 && d_y < 0) {
        // quad 2 (x+, y-)
        pivots[0] = i32_to__i32F8(64);
        pivots[1] = i32_to__i32F8(128);

        p_pivot__d_x = &pivots[0];
        p_pivot__d_y = &pivots[1];
    } else if (d_x < 0 && d_y < 0) {
        // quad 3 (x-, y-)
        pivots[0] = i32_to__i32F8(128);
        pivots[1] = i32_to__i32F8(192);

        p_pivot__d_x = &pivots[1];
        p_pivot__d_y = &pivots[0];
    } else {
        // quad 4 (x+, y-)
        pivots[0] = i32_to__i32F8(192);
        pivots[1] = i32_to__i32F8(256);

        p_pivot__d_x = &pivots[0];
        p_pivot__d_y = &pivots[1];
    }

    d_x = abs(d_x);
    d_y = abs(d_y);

    i32F8 degree__between_pivots =
        get_middle_angle(
                pivots[0], 
                pivots[1]);

    if (d_x == d_y)
        return degree__between_pivots;

    i32F8 distance = 0;
    do {
        if (d_x < d_y) {
            d_y -= d_x;

            *p_pivot__d_x =
                degree__between_pivots;
        } else {
            d_x -= d_y;

            *p_pivot__d_y =
                degree__between_pivots;
        }
        degree__between_pivots =
            get_middle_angle(
                    pivots[0], 
                    pivots[1]);
        distance =
            pivots[0] - pivots[1];
    } while (
            !(distance < i32_to__i32F8(1) 
                && distance > i32_to__i32F8(-1))
            && d_x != d_y);

    Degree__u8 fractional =
        degree__between_pivots
        & MASK(8);

    Degree__u8 integer =
        (degree__between_pivots 
         >> FRACTIONAL_PERCISION_8__BIT_SIZE)
        & MASK(8);

    return integer
        + (bool)(fractional & BIT(7));
}
