#ifndef SERIALIZATION_REQUEST_H
#define SERIALIZATION_REQUEST_H

#include "defines_weak.h"
#include <defines.h>

void initialize_serialization_request(
        Serialization_Request *p_serialization_request,
        void *p_file_handler,
        Serializer *p_serializer,
        Quantity__u16 size_of__serialization,
        Serialization_Request_Flags serialization_request_flags);

void initialize_serialization_request_as__uninitalized(
        Serialization_Request *p_serialization_request);

static inline
void set_serialization_request_as__active(
        Serialization_Request *p_serialization_request) {
    p_serialization_request->serialization_request_flags |=
        SERIALZIATION_REQUEST_FLAG__IS_ACTIVE;
}

static inline
void set_serialization_request_as__inactive(
        Serialization_Request *p_serialization_request) {
    p_serialization_request->serialization_request_flags &=
        ~SERIALZIATION_REQUEST_FLAG__IS_ACTIVE;
}

static inline
void set_serialization_request_as__using_serializer(
        Serialization_Request *p_serialization_request) {
    p_serialization_request->serialization_request_flags |=
        SERIALZIATION_REQUEST_FLAG__USE_SERIALIZER_OR_BUFFER;
}

static inline
void set_serialization_request_as__using_buffer(
        Serialization_Request *p_serialization_request) {
    p_serialization_request->serialization_request_flags &=
        ~SERIALZIATION_REQUEST_FLAG__USE_SERIALIZER_OR_BUFFER;
}

static inline
void set_serialization_request_as__read(
        Serialization_Request *p_serialization_request) {
    p_serialization_request->serialization_request_flags |=
        SERIALIZATION_REQUEST_FLAG__READ_OR_WRITE;
}

static inline
void set_serialization_request_as__write(
        Serialization_Request *p_serialization_request) {
    p_serialization_request->serialization_request_flags &=
        ~SERIALIZATION_REQUEST_FLAG__READ_OR_WRITE;
}

static inline
void set_serialization_request_as__keep_alive(
        Serialization_Request *p_serialization_request) {
    p_serialization_request->serialization_request_flags |=
        SERIALIZATION_REQUEST_FLAG__KEEP_ALIVE;
}

static inline
void set_serialization_request_as__fire_and_forget(
        Serialization_Request *p_serialization_request) {
    p_serialization_request->serialization_request_flags &=
        ~SERIALIZATION_REQUEST_FLAG__KEEP_ALIVE;
}

static inline
bool is_serialization_request__active(
        Serialization_Request *p_serialization_request) {
    return p_serialization_request->serialization_request_flags
        & SERIALZIATION_REQUEST_FLAG__IS_ACTIVE;
}

static inline
bool is_serialization_request__using_serializer(
        Serialization_Request *p_serialization_request) {
    return p_serialization_request->serialization_request_flags
        & SERIALZIATION_REQUEST_FLAG__USE_SERIALIZER_OR_BUFFER;
}

static inline
bool is_serialization_request__using_buffer(
        Serialization_Request *p_serialization_request) {
    return !is_serialization_request__using_serializer(
            p_serialization_request);
}

static inline
bool is_serialization_request__reading(
        Serialization_Request *p_serialization_request) {
    return p_serialization_request->serialization_request_flags
        & SERIALIZATION_REQUEST_FLAG__READ_OR_WRITE;
}

static inline
bool is_serialization_request__writing(
        Serialization_Request *p_serialization_request) {
    return !is_serialization_request__reading(
            p_serialization_request);
}

static inline
bool is_serialization_request__keep_alive(
        Serialization_Request *p_serialization_request) {
    return p_serialization_request->serialization_request_flags
        & SERIALIZATION_REQUEST_FLAG__KEEP_ALIVE;
}

static inline
bool is_serialization_request__fire_and_forget(
        Serialization_Request *p_serialization_request) {
    return !is_serialization_request__keep_alive(
            p_serialization_request);
}

#endif
