#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "timer.h"
#include <process/process_manager.h>
#include <process/process.h>

void initialize_process_manager(
        Process_Manager *p_process_manager) {
#ifndef NDEBUG
    if (!p_process_manager) {
        debug_abort("initialize_process_manager, p_process_manager is null.");
        return;
    }
#endif
    for (Index__u32 index_of__process = 0;
            index_of__process < PROCESS_MAX_QUANTITY_OF;
            index_of__process++) {
        initialize_process_as__empty_process(
                &p_process_manager
                ->processes[index_of__process]);
    }

    p_process_manager->quantity_of__running_processes = 0;
}

bool register_process_in__process_manager(
        Process_Manager *p_process_manager,
        Process *p_process,
        enum Process_Priority_Kind the_priority_of_the_process) {
#ifndef NDEBUG
    if (!p_process_manager) {
        debug_abort("register_process_in__process_manager, p_process_manager is null.");
        return false;
    }
    if (!p_process) {
        debug_abort("register_process_in__process_manager, p_process is null.");
        return false;
    }
#endif
    Process *p_process__available =
        allocate_process_in__process_manager(
                p_process_manager);

    if (!p_process__available)
        return false;
    if (p_process__available != p_process) {
        *p_process__available = *p_process;
    }
    p_process_manager->quantity_of__running_processes++;
    reset_process(p_process__available);
    p_process__available->the_kind_of_priority__this_process_has =
        the_priority_of_the_process;

    return true;
}

void register_process_as__critical_in__process_manager(
        Process_Manager *p_process_manager,
        Game *p_game,
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process_manager) {
        debug_abort("register_process_as__critical_in__process_manager, p_process_manager is null.");
        return;
    }
    if (!p_process) {
        debug_abort("register_process_as__critical_in__process_manager, p_process is null.");
        return;
    }
#endif
    Process *p_process__available =
        allocate_process_forcefully_in__process_manager(
                p_process_manager,
                p_game);

    if (!p_process__available)
        return;

    if (p_process__available ==
            p_process) {
        goto reset_process;
    }

    *p_process__available =
        *p_process;

reset_process:
    if (!is_process__active(p_process__available)) {
        p_process_manager->quantity_of__running_processes++;
    } else {
        remove_process_from__process_manager(
                p_process_manager, 
                p_game, 
                p_process__available);
    }
    reset_process(p_process__available);
    p_process__available
        ->the_kind_of_priority__this_process_has =
        Process_Priority_Kind__Critical;
}

///
/// Promotes p_process to the next
/// priority level up to High.
///
/// A process cannot be promoted to critical,
/// instead re-register the process as
/// Critical. No need to remove the process
/// prior to re-registration.
///
void promote_process_in__process_manager(
        Process_Manager *p_process_manager,
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process_manager) {
        debug_abort("promote_process_in__process_manager, p_process_manager is null.");
        return;
    }
    if (!p_process) {
        debug_abort("promote_process_in__process_manager, p_process is null.");
        return;
    }
#endif
    switch (get_process_priority(p_process)) {
        default:
            debug_abort("promote_process_in__process_manager, unknown priority: %d",
                    get_process_status(p_process));
            return;
        case Process_Priority_Kind__None:
        case Process_Priority_Kind__Low:
        case Process_Priority_Kind__Medium:
            p_process->the_kind_of_priority__this_process_has++;
            return;
        case Process_Priority_Kind__High:
        case Process_Priority_Kind__Critical:
            debug_warning("promote_process_in__process_manager, p_process already at highest priority.");
            return;
    }
}

///
/// Gets the next available process.
/// Return nullptr if no process is available.
///
Process *allocate_process_in__process_manager(
        Process_Manager *p_process_manager) {
#ifndef NDEBUG
    if (!p_process_manager) {
        debug_abort("allocate_process_in__process_manager, p_process_manager is null.");
        return 0;
    }
#endif
    Process *p_process__available = 0;
    for (Index__u32 index_of__process=0;
            index_of__process < PROCESS_MAX_QUANTITY_OF;
            index_of__process++) {
        Process *p_process__current =
            &p_process_manager
                ->processes[index_of__process];
        if (!is_process__available(p_process__current))
            continue;
        p_process__available = 
            p_process__current;
    }

    return p_process__available;
}

///
/// Will remove a process if needed in order
/// to secure a process pointer. If all processes
/// are critical the game engine will panick
/// then this function will return nullptr.
///
Process *allocate_process_forcefully_in__process_manager(
        Process_Manager *p_process_manager,
        Game *p_game) {
#ifndef NDEBUG
    if (!p_process_manager) {
        debug_abort("allocate_process_forcefully_in__process_manager, p_process_manager is null.");
        return 0;
    }
    if (!p_game) {
        debug_abort("get_available_p_process_forcefully_in__process_manager, p_game is null.");
        return 0;
    }
#endif
    Process *p_process__available =
        &p_process_manager->processes[0];
    for (Index__u32 index_of__process=1;
            index_of__process < PROCESS_MAX_QUANTITY_OF;
            index_of__process++) {
        Process *p_process__current =
            &p_process_manager
                ->processes[index_of__process];
        enum Process_Priority_Kind priority_of__current =
            get_process_priority(p_process__current);
        enum Process_Priority_Kind priority_of__available =
            get_process_priority(p_process__available);

        if (priority_of__current > priority_of__available) {
            p_process__available = 
                p_process__current;
            continue;
        }

        if (priority_of__current == priority_of__available) {
            if (get_time_elapsed_from__process(
                        p_process__current) <
                    get_time_elapsed_from__process(
                        p_process__available)) {
                continue;
            }
        }

        p_process__available =
            p_process__current;
    }

    if (is_process_of__this_priority(
                p_process__available, Process_Priority_Kind__Critical)) {
        debug_abort("register_process_as__critical_in__process_manager, failed to get available process.");
        debug_warning("Too many critical processes?");
    }
    
    return p_process__available;
}

void remove_process_from__process_manager(
        Process_Manager *p_process_manager,
        Game *p_game,
        Process *p_process) {
#ifndef NDEBUG
    if (!p_process_manager) {
        debug_abort("remove_process_from__process_manager, p_process_manager is null.");
        return;
    }
    if (!p_game) {
        debug_abort("remove_process_from__process_manager, p_game is null.");
        return;
    }
#endif
    if (does_process_have__removed_handler(p_process)) {
        p_process->m_process_removed__handler(
                p_process,
                p_game);
    }
    
    p_process->the_kind_of_status__this_process_has =
        Process_Status_Kind__Removed;
}

void poll_process_manager(
        Process_Manager *p_process_manager,
        Game *p_game) {
#ifndef NDEBUG
    if (!p_process_manager) {
        debug_abort("poll_process_manager, p_process_manager is null.");
        return;
    }
    if (!p_game) {
        debug_abort("poll_process_manager, p_game is null.");
        return;
    }
#endif
    for (Index__u32 index_of__process = 0;
            index_of__process < PROCESS_MAX_QUANTITY_OF;
            index_of__process++) {
        Process *p_process =
            &p_process_manager->processes[index_of__process];
        u32 time_elapsed__low =
            get_time_elapsed__game(p_game)
            & MASK(8);
        u32 time_elapsed__medium =
            get_time_elapsed__game(p_game)
            & MASK(7);
        u32 time_elapsed__high =
            get_time_elapsed__game(p_game)
            & MASK(6);

        if (is_process__complete(p_process)) {
            remove_process_from__process_manager(
                    p_process_manager, 
                    p_game, 
                    p_process);
            continue;
        }

        switch (get_process_priority(p_process)) {
            case Process_Priority_Kind__None:
                break;
            default:
                debug_error("poll_process_manager, unknown process priority: %d",
                        get_process_priority(p_process));
                reset_process(p_process);
                p_process->the_kind_of_status__this_process_has =
                    Process_Status_Kind__Unknown;
                p_process->the_kind_of_priority__this_process_has =
                    Process_Priority_Kind__None;
                continue;
            case Process_Priority_Kind__Low:
                if (time_elapsed__low ^ (index_of__process * MASK(4)))
                    continue;
                break;
            case Process_Priority_Kind__Medium:
                if (time_elapsed__medium ^ (index_of__process * MASK(3)))
                    continue;
                break;
            case Process_Priority_Kind__High:
                if (time_elapsed__high ^ (index_of__process * MASK(2)))
                    continue;
                break;
            case Process_Priority_Kind__Critical:
                break;
        }
        switch (get_process_status(p_process)) {
            default:
            case Process_Status_Kind__Unknown:
                debug_error("poll_process_manager, unknown process status: %d",
                        get_process_status(p_process));
                initialize_process_as__empty_process(p_process);
            case Process_Status_Kind__None:
            case Process_Status_Kind__Stopped:
                break;
            case Process_Status_Kind__Busy:
            case Process_Status_Kind__Idle:
                p_process->the_kind_of_status__this_process_has =
                    Process_Status_Kind__Busy;
                p_process->m_process_run__handler(
                        p_process,
                        p_game);
                break;
            case Process_Status_Kind__Removed:
                initialize_process_as__empty_process(p_process);
                break;
            case Process_Status_Kind__Complete:
                break;
            case Process_Status_Kind__Fail:
                remove_process_from__process_manager(
                        p_process_manager,
                        p_game,
                        p_process);
                break;
        }
    }
}
