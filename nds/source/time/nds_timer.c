#include "defines.h"
#include "timer.h"
#include <nds/timers.h>

void NDS_initialize_clock(void) {
    timerStart(0, ClockDivider_64, 0, 0);
}

i32F20 PLATFORM_get_time_elapsed(
        Timer__u32 *p_timer__seconds__u32,
        Timer__u32 *p_timer__nanoseconds__u32) {
    u16 ticks = timerElapsed(0);
    u32 nanoseconds = timerTicks2usec(ticks);

    if (progress_timer__u32(
                p_timer__nanoseconds__u32, 
                nanoseconds)) {
        loop_timer_u32(p_timer__seconds__u32);
    }

    u32 elapsed__seconds = 
        get_time_elapsed_from__timer_u32(
            p_timer__seconds__u32);

    u32 elapsed__nanoseconds =
        get_time_elapsed_from__timer_u32(
            p_timer__nanoseconds__u32);

    return 
        (elapsed__seconds << 20)
        + ((elapsed__nanoseconds
                & MASK(30))
                >> 10)
        ;
}
