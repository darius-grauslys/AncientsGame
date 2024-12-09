#include "time/sdl_time.h"
#include "numerics.h"
#include "timer.h"

#ifdef _WIN32
///
/// NOTE: Timer value is considered to be i32F20 seconds
///
i32F20 PLATFORM_get_time_elapsed(
        Timer__u32 *p_timer__seconds__u32,
        Timer__u16 *p_timer__nanoseconds__u16) {
    
}
#else
#include <time.h>
///
/// NOTE: Timer value is considered to be i32F20 seconds
///
i32F20 PLATFORM_get_time_elapsed(
        Timer__u32 *p_timer__seconds__u32,
        Timer__u32 *p_timer__nanoseconds__u32) {
    struct timespec timespec__current;
    clock_gettime(
            CLOCK_MONOTONIC, 
            &timespec__current);

    u32 elapsed__seconds = 
        subtract_u32__no_overflow(
                timespec__current.tv_sec, 
                get_time_elapsed_from__timer_u32(
                    p_timer__seconds__u32));

    u32 elapsed__nanoseconds =
        subtract_u32__no_overflow(
                timespec__current.tv_nsec, 
                get_time_elapsed_from__timer_u32(
                    p_timer__nanoseconds__u32));
    if (!elapsed__nanoseconds) {
        elapsed__nanoseconds=
            timespec__current.tv_nsec
            + p_timer__nanoseconds__u32->remaining__u32
            ;
    }

    (void)progress_timer__u32(
                p_timer__seconds__u32, 
                elapsed__seconds);
    if (progress_timer__u32(
                p_timer__nanoseconds__u32, 
                elapsed__nanoseconds)) {
        elapsed__seconds--;
    }

    return 
        (elapsed__seconds << 20)
        + ((elapsed__nanoseconds
                & MASK(30))
                >> 10)
        ;
}
#endif
