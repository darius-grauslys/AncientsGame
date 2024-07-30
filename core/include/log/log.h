#ifndef LOG_H
#define LOG_H

#include "defines_weak.h"
#include <defines.h>

void initialize_log(
        Log *p_log);

void flush_message_into__log(
        Log *p_log);

///
/// Will return nullptr if the index
/// is out of range.
///
Message *get_p_message_from__log(
        Log *p_log,
        Index__u8 index_of__message);

static inline
Message *get_next_p_message_in__log(
        Log *p_log) {
    return p_log->p_next_message;
}

static inline
void clear_log(Log *p_log) {
    initialize_log(p_log);
}

#endif
