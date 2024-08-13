#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "defines_weak.h"
#include <defines.h>

void intialize_serializer(
        Serializer *p_serializer,
        Quantity__u32 size_of__struct,
        Identifier__u32 uuid__u32,
        m_Serialize m_serialize_handler,
        m_Deserialize m_deserialize_handler);

void intialize_serializer_as__deallocated(
        Serializer *p_serializer,
        Quantity__u32 size_of__struct,
        m_Serialize m_serialize_handler,
        m_Deserialize m_deserialize_handler);

void m_serialize__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);

void m_deserialize__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);

#endif
