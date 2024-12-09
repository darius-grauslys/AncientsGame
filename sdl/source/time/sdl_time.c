#include "time/sdl_time.h"
#include "numerics.h"
#include "timer.h"
#include "sdl_numerics.h"

#ifdef _WIN32
///
/// NOTE: Timer value is considered to be i32F20 seconds
///
#include <windows.h>
#include <mmsystem.h>
i32F20 PLATFORM_get_time_elapsed(
        Timer__u32 *p_timer__seconds__u32,
        Timer__u32 *p_timer__nanoseconds__u32) {
    DWORD time__old = get_time_elapsed_from__timer_u32(
            p_timer__nanoseconds__u32);
    DWORD time__current = timeGetTime();

    if (time__old == time__current)
        return 0;

    u32 elapsed__miliseconds = 
        subtract_u32__no_overflow(
                time__current,
                time__old);
    if (!elapsed__miliseconds) {
        elapsed__miliseconds =
            time__current
            + (((uint32_t)-1)
                - time__old)
            ;
    }
    
    (void)progress_timer__u32(
                p_timer__nanoseconds__u32, 
                elapsed__miliseconds);

    return 
        ((elapsed__miliseconds
                & MASK(10))
                << 10)
        ;
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
    if (!elapsed__seconds) {
        elapsed__seconds=
            timespec__current.tv_sec
            + p_timer__seconds__u32->remaining__u32
            ;
    }

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
