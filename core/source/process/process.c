#include "defines.h"
#include "defines_weak.h"
#include "timer.h"
#include <process/process.h>

void initialize_process(
        Process *p_process,
        m_Process m_process_run__handler,
        m_Process m_process_removed__handler,
        void *p_process_data,
        Quantity__u32 quantity_of__steps_per_cycle) {
    initialize_timer_u32(
            get_p_timer_u32_from__process(p_process), 
            QUANTITY__UNKNOWN__u32);
    p_process->quantity_of__steps_per_cycle =
        quantity_of__steps_per_cycle;
    p_process->m_process_run__handler =
        m_process_run__handler;
    p_process->m_process_removed__handler =
        m_process_removed__handler;
    p_process->the_kind_of_priority__this_process_has =
        Process_Priority_Kind__None;
    p_process->the_kind_of_status__this_process_has =
        Process_Status_Kind__None;
    p_process->p_process_data =
        p_process_data;
}

void initialize_process_as__empty_process(
        Process *p_process) {
    initialize_process(
            p_process, 0, 0, 0, 0);
}
