#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include <entity/handlers/serialization/serialization_handler__entity__default.h>

void m_serialize_handler__entity__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {
    Entity *p_entity=
        (Entity*)p_this_serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    enum PLATFORM_Write_File_Error error = 
        PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&p_this_serializer->_serialization_header, 
                sizeof(Serialization_Header), 
                1, 
                p_file_handler);

    struct {
        Entity_Flags__u8 entity_flags;
        Identifier__u16 identifier;
        enum Entity_Kind the_kind_of_entity;
    } field;
    
    field.entity_flags = p_entity->entity_flags;
    field.identifier = p_entity->identifier;
    field.the_kind_of_entity = p_entity->the_kind_of_entity__this_entity_is;

    error = 
        PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&field, 
                sizeof(field), 
                1, 
                p_file_handler);
}

void m_deserialize_handler__entity__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {
    Entity *p_entity=
        (Entity*)p_this_serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    Quantity__u32 length_of__read =
        sizeof(Serialization_Header);
    enum PLATFORM_Read_File_Error error = 
        PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&p_this_serializer->_serialization_header, 
                &length_of__read,
                1, 
                p_file_handler);

    struct {
        Entity_Flags__u8 entity_flags;
        Identifier__u16 identifier;
        enum Entity_Kind the_kind_of_entity;
    } field;

    length_of__read =
        sizeof(field);
    error = 
        PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&field, 
                &length_of__read, 
                1, 
                p_file_handler);

    p_entity->entity_flags =
        field.entity_flags;
    p_entity->identifier =
        field.identifier;
    p_entity->the_kind_of_entity__this_entity_is =
        field.entity_flags;
}
