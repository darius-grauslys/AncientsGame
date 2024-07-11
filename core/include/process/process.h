#ifndef PROCESS_H
#define PROCESS_H

#include "defines_weak.h"
#include "timer.h"
#include <defines.h>

void initialize_process(
        Process *p_process,
        m_Process m_process_run__handler,
        m_Process m_process_removed__handler,
        void *p_process_data,
        Quantity__u32 quantity_of__steps_per_cycle);

void initialize_process_as__empty_process(
        Process *p_process);

static inline
void complete_process(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("complete_process, p_process is null.");
        return;
    }
#endif
    p_process->the_kind_of_status__this_process_has =
        Process_Status_Kind__Complete;
    p_process->the_kind_of_priority__this_process_has =
        Process_Priority_Kind__None;
}

static inline
Timer__u32 *get_p_timer_u32_from__process(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("get_p_timer_u32_from__process, p_process is null.");
        return 0;
    }
#endif
    return &p_process->process_timer__u32;
}

static inline
enum Process_Status_Kind get_process_status(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("get_process_status, p_process is null.");
        return Process_Status_Kind__Unknown;
    }
#endif
    return p_process->the_kind_of_status__this_process_has;
}

static inline
enum Process_Priority_Kind get_process_priority(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("get_process_priority, p_process is null.");
        return Process_Priority_Kind__None;
    }
#endif
    return p_process->the_kind_of_priority__this_process_has;
}

static inline
bool is_process__active(Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("is_process__active, p_process is null.");
        return false;
    }
#endif
    switch (get_process_status(p_process)) {
        case Process_Status_Kind__Busy:
        case Process_Status_Kind__Idle:
            return true;
        default:
            return false;
    }
}

///
/// Reset's it's status as well
/// as it's lifetime counter.
///
static inline
void reset_process(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("reset_process, p_process is null.");
        return;
    }
#endif
    p_process->the_kind_of_status__this_process_has =
        Process_Status_Kind__Idle;
    reset_timer_u32(get_p_timer_u32_from__process(p_process));
}

static inline
void stop_process(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("stop_process, p_process is null.");
        return;
    }
#endif
    p_process->the_kind_of_status__this_process_has =
        Process_Status_Kind__Stopped;
}

static inline
bool is_process__complete(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("is_process__complete, p_process is null.");
        return false;
    }
#endif
    return p_process && p_process->the_kind_of_status__this_process_has
        == Process_Status_Kind__Complete;
}

static inline
bool is_process__available(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("is_process__available, p_process is null.");
        return false;
    }
#endif
    return p_process && p_process->the_kind_of_status__this_process_has
        == Process_Status_Kind__None;
}

static inline
Quantity__u32 get_time_elapsed_from__process(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("get_time_elapsed_from__process, p_process is null.");
        return false;
    }
#endif
    return get_time_elapsed_from__timer_u32(
            get_p_timer_u32_from__process(p_process));
}

static inline
bool is_process_of__this_priority(
        Process *p_process,
        enum Process_Priority_Kind the_kind_of__priority) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("is_process_of__this_priority, p_process is null.");
        return false;
    }
#endif
    return get_process_priority(p_process)
        == the_kind_of__priority;
}

static inline
bool does_process_have__run_handler(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("does_process_have__run_handler, p_process is null.");
        return false;
    }
#endif
    return p_process->m_process_run__handler;
}

static inline
bool does_process_have__removed_handler(
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process) {
        debug_abort("does_process_have__removed_handler, p_process is null.");
        return false;
    }
#endif
    return p_process->m_process_removed__handler;
}

#define LOOP_PROCESS(p_process) \
    for (Index__u32 index_of__process__loop = 0; index_of__process__loop \
            < p_process->quantity_of__steps_per_cycle;\
            index_of__process__loop++, \
            loop_timer_u32(get_p_timer_u32_from__process(p_process)))

#endif
