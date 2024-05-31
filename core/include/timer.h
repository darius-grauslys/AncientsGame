#ifndef TIMER_H
#define TIMER_H

#include "defines.h"
#include "defines_weak.h"

static void inline init_timer_u32_as__unused(Timer__u32 *timer__u32) {
    timer__u32->remaining__u32 =
        timer__u32->start__u32 = 0;
}

static void inline init_timer_u32(
        Timer__u32 *timer__u32,
        uint8_t start__u32) {
    timer__u32->remaining__u32 =
        timer__u32->start__u32 = start__u32;
}

static void inline reset_timer_u32(
        Timer__u32 *timer__u32) {
    timer__u32->remaining__u32 =
        timer__u32->start__u32;
}

static bool inline is_timer_u32__elapsed(Timer__u32 *timer__u32) {
    return timer__u32->remaining__u32 == 0;
}

static bool inline poll_timer_u32(Timer__u32 *timer__u32) {
#ifndef NDEBUG
    if (timer__u32->remaining__u32 > timer__u32->start__u32) {
        debug_error("poll_timer_u32, timer__u32->elapsed:%d exceeds limit:%d",
                timer__u32->remaining__u32,
                timer__u32->start__u32);
    }
#endif
    return (is_timer_u32__elapsed(timer__u32) 
            || timer__u32->remaining__u32-- == 0);
}

static void inline loop_timer_u32(Timer__u32 *timer__u32) {
    if (timer__u32->remaining__u32 == 0)
        timer__u32->remaining__u32 = 
            timer__u32->start__u32;
    timer__u32->remaining__u32--;
}

static Quantity__u32 inline get_time_elapsed_from__timer_u32(
        Timer__u32 *timer__u32) {
    return timer__u32->start__u32 - timer__u32->remaining__u32;
}

static void inline init_timer_u8_as__unused(Timer__u8 *timer__u8) {
    timer__u8->remaining__u8 =
        timer__u8->start__u8 = 0;
}

static void inline init_timer_u8(
        Timer__u8 *timer__u8,
        uint8_t start__u8) {
    timer__u8->remaining__u8 =
        timer__u8->start__u8 = start__u8;
}

static void inline reset_timer_u8(
        Timer__u8 *timer__u8) {
    timer__u8->remaining__u8 =
        timer__u8->start__u8;
}

static bool inline is_timer_u8__elapsed(Timer__u8 *timer__u8) {
    return timer__u8->remaining__u8 == 0;
}

static bool inline poll_timer_u8(Timer__u8 *timer__u8) {
#ifndef NDEBUG
    if (timer__u8->remaining__u8 > timer__u8->start__u8) {
        debug_error("poll_timer_u8, timer__u8->elapsed:%d exceeds limit:%d",
                timer__u8->remaining__u8,
                timer__u8->start__u8);
    }
#endif
    return (is_timer_u8__elapsed(timer__u8) 
            || timer__u8->remaining__u8-- == 0);
}

static void inline loop_timer_u8(Timer__u8 *timer__u8) {
    if (timer__u8->remaining__u8 == 0)
        timer__u8->remaining__u8 = 
            timer__u8->start__u8;
    timer__u8->remaining__u8--;
}

static Quantity__u8 inline get_time_elapsed_from__timer_u8(
        Timer__u8 *timer__u8) {
    return timer__u8->start__u8 - timer__u8->remaining__u8;
}

static void inline init_timer_u16_as__unused(Timer__u16 *timer__u16) {
    timer__u16->remaining__u16 =
        timer__u16->start__u16 = 0;
}

static void inline init_timer_u16(
        Timer__u16 *timer__u16,
        uint8_t start__u16) {
    timer__u16->remaining__u16 =
        timer__u16->start__u16 = start__u16;
}

static void inline reset_timer_u16(
        Timer__u16 *timer__u16) {
    timer__u16->remaining__u16 =
        timer__u16->start__u16;
}

static bool inline is_timer_u16__elapsed(Timer__u16 *timer__u16) {
    return timer__u16->remaining__u16 == 0;
}

static bool inline poll_timer_u16(Timer__u16 *timer__u16) {
#ifndef NDEBUG
    if (timer__u16->remaining__u16 > timer__u16->start__u16) {
        debug_error("poll_timer_u16, timer__u16->elapsed:%d exceeds limit:%d",
                timer__u16->remaining__u16,
                timer__u16->start__u16);
    }
#endif
    return (is_timer_u16__elapsed(timer__u16) 
            || timer__u16->remaining__u16-- == 0);
}

static void inline loop_timer_u16(Timer__u16 *timer__u16) {
    if (timer__u16->remaining__u16 == 0)
        timer__u16->remaining__u16 = 
            timer__u16->start__u16;
    timer__u16->remaining__u16--;
}

static Quantity__u16 inline get_time_elapsed_from__timer_u16(
        Timer__u16 *timer__u16) {
    return timer__u16->start__u16 - timer__u16->remaining__u16;
}

#endif
