#include "serialization/serialization_request.h"
#include "defines.h"
#include "defines_weak.h"

void initialize_serialization_request(
        Serialization_Request *p_serialization_request,
        void *p_file_handler,
        Serializer *p_serializer,
        Quantity__u16 size_of__serialization,
        Serialization_Request_Flags serialization_request_flags) {
    p_serialization_request
        ->p_file_handler = p_file_handler;
    p_serialization_request
        ->p_serializer = p_serializer;
    p_serialization_request
        ->size_of__serialization = size_of__serialization;
    p_serialization_request
        ->serialization_request_flags = serialization_request_flags;
}

void initialize_serialization_request_as__uninitalized(
        Serialization_Request *p_serialization_request) {
    initialize_serialization_request(
            p_serialization_request, 
            0,
            0, 
            0,
            SERIALIZATION_REQUEST_FLAGS__NONE);
}
