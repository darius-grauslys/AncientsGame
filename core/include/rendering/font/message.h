#ifndef MESSAGE_H
#define MESSAGE_H

#include "defines_weak.h"
#include <defines.h>

void initialize_message(
        Message *p_message,
        unsigned char *p_c_string_name,
        Quantity__u32 max_length_of__c_string_name,
        unsigned char *p_c_string,
        Quantity__u32 max_length_of__c_string);

void initialize_message_as__empty(
        Message *p_message);

void initialize_message_with__utf_16_string(
        Message *p_message,
        unsigned short *p_utf_16_string,
        Quantity__u32 max_length_of__utf_16_string);

static inline
unsigned char get_char_from__message(
        Message *p_message,
        Index__u8 index_of__char_in__message) {
#ifndef NDEBUG
    if (index_of__char_in__message <
            MESSAGE_MAX_LENGTH_OF) {
        debug_abort("get_char_from__message, out of bounds: %d",
                index_of__char_in__message);
        return 0; 
    }
#endif
    return p_message->uchar_array_of__message[
        index_of__char_in__message];
}

void put_c_string_into__message(
        Message *p_message,
        unsigned char *p_c_string,
        Quantity__u8 max_length_of__c_string);

#endif
