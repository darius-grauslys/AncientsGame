#include "log/message.h"
#include "defines.h"
#include "defines_weak.h"
#include "serialization/serialization_header.h"

void initialize_message(
        Message *p_message) {
    for (Index__u8 index_of__char = 0;
            index_of__char<MESSAGE_NAME_MAX_LENGTH_OF;
            index_of__char++) {
        p_message->message__title[index_of__char] = 0;
    }
    for (Index__u8 index_of__char = 0;
            index_of__char<MESSAGE_MAX_LENGTH_OF;
            index_of__char++) {
        p_message->message__body[index_of__char] = 0;
    }
    initialize_serialization_header(
            &p_message->_serialization_header,
            IDENTIFIER__UNKNOWN__u32,
            sizeof(Message));
    p_message->length_of__message__title = 0;
    p_message->length_of__message__body = 0;
    p_message->index_of__body = 0;
}

///
/// Returns false if message body is full.
///
bool put_char_into__message(
        Message *p_message,
        char character) {
    if (p_message->index_of__body
            >= MESSAGE_MAX_LENGTH_OF)
        return true;
    p_message->message__body[
        p_message->index_of__body] = character;
    p_message->index_of__body++;
    p_message->length_of__message__body++;
    return false;
}

bool put_cstr_into__message(
        Message *p_message,
        char *cstr) {
#ifndef NDEBUG
    if (!p_message) {
        debug_abort("put_cstr_into__message, p_message is null.");
        return false;
    }
#endif
    char read_character = 0;
    for (Quantity__u8 size_of__message = 1;
            (read_character = cstr[size_of__message-1]) != 0;
            size_of__message++) {
        if (put_char_into__message(p_message, read_character)) {
            return true;
        }
    }
    return false;
}

///
/// Will return true if the title had to
/// be truncated.
///
bool set_title_of__message(
        Message *p_message,
        char *cstr) {
    char read_character = 0;
    for (Quantity__u8 size_of__message = 1;
            (read_character = cstr[size_of__message-1]) != 0;
            size_of__message++) {
        p_message->message__title[size_of__message-1] =
            read_character;
        p_message->length_of__message__title = 
            size_of__message;
        if (size_of__message + 1 > MESSAGE_NAME_MAX_LENGTH_OF) {
            return true;
        }
    }
    return false;
}
