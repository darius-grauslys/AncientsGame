#ifndef SERIALIZATION_HANDLER__ENTITY__DEFAULT_H
#define SERIALIZATION_HANDLER__ENTITY__DEFAULT_H

#include <defines.h>

void m_serialize_handler__entity__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);
void m_deserialize_handler__entity__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);

#endif
