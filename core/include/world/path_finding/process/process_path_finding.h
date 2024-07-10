#ifndef PROCESS_PATH_FINDING_H
#define PROCESS_PATH_FINDING_H

#include "defines_weak.h"
#include <defines.h>

///
/// Does not take ownership of the p_path_list.
///
void initialize_process_for__path_finding(
        Process *p_process,
        Path_List *p_path_list,
        Quantity__u32 quantity_of__steps_per_cycle);

void m_process__path_find(
        Process *p_this_process,
        Game *p_game);

static inline
Path_List *get_p_path_list_from__process(
        Process *p_proces) {
    return (Path_List*)
        p_proces->p_process_data;
}

#endif
