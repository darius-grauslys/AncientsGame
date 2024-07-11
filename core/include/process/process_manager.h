#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <defines.h>

void initialize_process_manager(
        Process_Manager *p_process_manager);

///
/// Returns true if the process is successfully
/// registered.
///
/// Note you should only register complicated
/// processes. See process.h before using
/// process_manager.h .
///
bool register_process_in__process_manager(
        Process_Manager *p_process_manager,
        Process *p_process,
        enum Process_Priority_Kind the_priority_of_the_process);

///
/// Note you should only register complicated
/// processes. See process.h before using
/// process_manager.h .
///
static inline
void register_process_as__low_in__process_manager(
        Process_Manager *p_process_manager,
        Process *p_process) {
    register_process_in__process_manager(
            p_process_manager, 
            p_process, 
            Process_Priority_Kind__Low);
}

///
/// Note you should only register complicated
/// processes. See process.h before using
/// process_manager.h .
///
static inline
void register_process_as__medium_in__process_manager(
        Process_Manager *p_process_manager,
        Process *p_process) {
    register_process_in__process_manager(
            p_process_manager, 
            p_process, 
            Process_Priority_Kind__Medium);
}

///
/// Note you should only register complicated
/// processes. See process.h before using
/// process_manager.h .
///
static inline
void register_process_as__high_in__process_manager(
        Process_Manager *p_process_manager,
        Process *p_process) {
    register_process_in__process_manager(
            p_process_manager, 
            p_process, 
            Process_Priority_Kind__High);
}

///
/// Note you should only register complicated
/// processes. See process.h before using
/// process_manager.h .
///
void register_process_as__critical_in__process_manager(
        Process_Manager *p_process_manager,
        Game *p_game,
        Process *p_process);

void remove_process_from__process_manager(
        Process_Manager *p_process_manager,
        Game *p_game,
        Process *p_process);

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
        Process *p_process);

///
/// Gets the next available process.
/// Return nullptr if no process is available.
///
Process *allocate_process_in__process_manager(
        Process_Manager *p_process_manager);

///
/// Will remove a process if needed in order
/// to secure a process pointer. If all processes
/// are critical the game engine will panick
/// then this function will return nullptr.
///
Process *allocate_process_forcefully_in__process_manager(
        Process_Manager *p_process_manager,
        Game *p_game);

void poll_process_manager(
        Process_Manager *p_process_manager,
        Game *p_game);

#endif
