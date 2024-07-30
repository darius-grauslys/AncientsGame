#ifndef MESSAGE_H
#define MESSAGE_H

#include <defines.h>

void initialize_message(
        Message *p_message);

///
/// Returns true if message body is full.
///
bool put_char_into__message(
        Message *p_message,
        char character);

///
/// Returns true if message body is full.
///
bool put_cstr_into__message(
        Message *p_message,
        char *cstr);

///
/// Will return true if the title had to
/// be truncated.
///
bool set_title_of__message(
        Message *p_message,
        char *cstr);

static inline
void clear_message(
        Message *p_message) {
    initialize_message(p_message);
}

#endif
