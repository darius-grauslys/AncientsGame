#ifndef NUMERICS_H
#define NUMERICS_H

#include <defines_weak.h>

static const u8 MAX__U8     = ((u8)-1);
static const u16 MAX__U16   = ((u16)-1);
static const u32 MAX__U32   = ((u32)-1);

static inline
u8 add_u8__clamped(
        u8 first__u8,
        u8 second__u8,
        u8 clamp__u8) {
    if (MAX__U8 - first__u8 < second__u8) {
        return clamp__u8;
    }
    if (first__u8 + second__u8 > clamp__u8) {
        return clamp__u8;
    }
    return first__u8 + second__u8;
}

static inline
u16 add_u16__clamped(
        u16 first__u16,
        u16 second__u16,
        u16 clamp__u16) {
    if (MAX__U8 - first__u16 < second__u16) {
        return MAX__U8;
    }
    if (first__u16 + second__u16 > clamp__u16) {
        return clamp__u16;
    }
    return first__u16 + second__u16;
}

static inline
u32 add_u32__clamped(
        u32 first__u32,
        u32 second__u32,
        u32 clamp__u32) {
    if (MAX__U8 - first__u32 < second__u32) {
        return MAX__U8;
    }
    if (first__u32 + second__u32 > clamp__u32) {
        return clamp__u32;
    }
    return first__u32 + second__u32;
}

static inline
u8 subtract_u8__no_overflow(
        u8 first__u8,
        u8 second__u8) {
    if (first__u8 < second__u8)
        return 0;
    return first__u8 - second__u8;
}

static inline
u16 subtract_u16__no_overflow(
        u16 first__u16,
        u16 second__u16) {
    if (first__u16 < second__u16)
        return 0;
    return first__u16 - second__u16;
}

static inline
u32 subtract_u32__no_overflow(
        u32 first__u32,
        u32 second__u32) {
    if (first__u32 < second__u32)
        return 0;
    return first__u32 - second__u32;
}

static inline
u8 clamp__u8(
        u8 value__u8,
        u8 min__u8,
        u8 max__u8) {
    if (value__u8 < min__u8)
        return min__u8;
    if (value__u8 > max__u8)
        return max__u8;
    return value__u8;
}

static inline
void clamp__p_u8(
        u8 *p_value__u8,
        u8 min__u8,
        u8 max__u8) {
    u8 value__u8 = *p_value__u8;
    if (value__u8 < min__u8) {
        *p_value__u8 = min__u8;
        return;
    }
    if (value__u8 > max__u8) {
        *p_value__u8 = max__u8;
        return;
    }
}

static inline
i32 clamp__i32(
        i32 value__i32,
        i32 min__i32,
        i32 max__i32) {
    if (value__i32 < min__i32)
        return min__i32;
    if (value__i32 > max__i32)
        return max__i32;
    return value__i32;
}

static inline
void clamp__p_i32(
        i32 *p_value__i32,
        i32 min__i32,
        i32 max__i32) {
    i32 value__i32 = *p_value__i32;
    if (value__i32 < min__i32) {
        *p_value__i32 = min__i32;
        return;
    }
    if (value__i32 > max__i32) {
        *p_value__i32 = max__i32;
        return;
    }
}

#endif
