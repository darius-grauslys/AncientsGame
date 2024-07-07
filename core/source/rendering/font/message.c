#include "defines.h"
#include "defines_weak.h"
#include "numerics.h"
#include <rendering/font/message.h>

void initialize_message_fully(
        Message *p_message,
        unsigned char *p_c_string_name,
        Quantity__u32 max_length_of__c_string_name,
        unsigned char *p_c_string,
        Quantity__u32 max_length_of__c_string) {
    p_message->length_of__message_name = 
        clamp__u8(
                max_length_of__c_string_name, 
                0, 
                MESSAGE_NAME_MAX_LENGTH_OF);
    p_message->length_of__message =
        clamp__u8(
                max_length_of__c_string, 
                0, 
                MESSAGE_MAX_LENGTH_OF);

    //TODO: memcpy forward signature in platform.h
    memcpy(
            p_c_string_name,
            p_message->uchar_array_of__message_name,
            p_message->length_of__message_name);
    memcpy(
            p_c_string,
            p_message->uchar_array_of__message,
            p_message->length_of__message);
}

void initialize_message_as__empty(
        Message *p_message) {
    for (Index__u8 index_of__char_in__message_name = 0;
            index_of__char_in__message_name < MESSAGE_NAME_MAX_LENGTH_OF;
            index_of__char_in__message_name++) {
        p_message->uchar_array_of__message_name[
            index_of__char_in__message_name] = 0;
    }
    for (Index__u8 index_of__char_in__message = 0;
            index_of__char_in__message < MESSAGE_MAX_LENGTH_OF;
            index_of__char_in__message++) {
        p_message->uchar_array_of__message[
            index_of__char_in__message] = 0;
    }
    p_message->length_of__message_name = 0;
    p_message->length_of__message = 0;
}

void initialize_message_with__utf_16_string(
        Message *p_message,
        unsigned short *p_utf_16_string,
        Quantity__u32 max_length_of__utf_16_string) {
	debug_abort("not impl");
}

void put_c_string_into__message(
        Message *p_message,
        unsigned char *p_c_string,
        Quantity__u8 max_length_of__c_string) {
    max_length_of__c_string =
        clamp__u8(
                max_length_of__c_string, 
                0, 
                MESSAGE_MAX_LENGTH_OF);
    memcpy(
            p_c_string,
            p_message->uchar_array_of__message,
            p_message->length_of__message);
}
