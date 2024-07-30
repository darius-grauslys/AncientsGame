#include "log/log.h"
#include "defines.h"
#include "defines_weak.h"
#include "log/message.h"

void initialize_log(
        Log *p_log) {
    for (Index__u8 index_of__message = 0;
            index_of__message < MESSAGE_MAX_QUANTITY_OF;
            index_of__message++) {
        initialize_message(&p_log->messages[index_of__message]);
    }
    p_log->p_oldest_message = 0;
    p_log->p_next_message = 
        &p_log->messages[0];
}

void poll_message_pointer_for__wrapping(
        Log *p_log,
        Message **p_message_ptr) {
    (*p_message_ptr)++;
    Message *p_message = *p_message_ptr; 
    if (!p_log->p_oldest_message) {
        p_log->p_oldest_message =
            &p_log->messages[0];
        return;
    }
    if (p_message
            - p_log->messages
            >= MESSAGE_MAX_QUANTITY_OF) {
        *p_message_ptr =
            &p_log->messages[0];
    }
}

void flush_message_into__log(
        Log *p_log) {
    poll_message_pointer_for__wrapping(
            p_log,
            &p_log->p_next_message);
    initialize_message(p_log->p_next_message);
    if (p_log->p_oldest_message
            == p_log->p_next_message) {
        poll_message_pointer_for__wrapping(
                p_log,
                &p_log->p_oldest_message);
    }
}

///
/// Will return nullptr if the index
/// is out of range.
///
Message *get_p_message_from__log(
        Log *p_log,
        Index__u8 index_of__message) {
    Message *p_message_current =
        p_log->p_oldest_message;
    for (Index__u8 index_of__message_lookup = 0;
            index_of__message_lookup < index_of__message;
            index_of__message_lookup++) {
        if (p_message_current
                == p_log->p_next_message)
            return 0;
        poll_message_pointer_for__wrapping(
                p_log, 
                &p_message_current);
    }
    return p_message_current;
}
