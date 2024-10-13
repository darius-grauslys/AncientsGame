#include "defines.h"
#include "defines_weak.h"
#include "entity/handlers/serialization/serialization_handler__entity__default.h"
#include "game.h"
#include "serialization/serialized_field.h"
#include <entity/handlers/serialization/serialization_handler__living__default.h>

struct __living_field {
    Direction__u8 direction;
    Resource_Reserve hearts;
    Resource_Reserve energy;
    Humanoid_Flags humanoid_flags;
    Timer__u8 stun_timer;
    Equipment equipment;
    Vector__3i32F4 goal__position__3i32F4;
    Identifier__u32 goal__entity_identifier;
    enum Audio_Effect_Kind the_kind_of__audio_effect_for__alert;
    enum Audio_Effect_Kind the_kind_of__audio_effect_for__hurt;
    enum Audio_Effect_Kind the_kind_of__audio_effect_for__die;
};

void m_serialize_handler__living__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {
    m_serialize_handler__entity__default(
            p_game, 
            p_serialization_request, 
            p_this_serializer);

    Entity *p_living = (Entity*)p_this_serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    struct __living_field field;

    field.direction = p_living->direction;
    field.hearts = p_living->hearts;
    field.energy = p_living->energy_orbs;
    field.humanoid_flags = p_living->humanoid_flags;
    field.stun_timer = p_living->stun__timer_u8;
    field.equipment = p_living->equipment;
    field.goal__position__3i32F4 = p_living->goal__position__3i32F4;
    field.goal__entity_identifier = 
        p_living->goal__s_entity_ptr.identifier_for__serialized_field;
    field.the_kind_of__audio_effect_for__alert =
        p_living->the_kind_of__audio_effect_for__alert;
    field.the_kind_of__audio_effect_for__hurt =
        p_living->the_kind_of__audio_effect_for__hurt;
    field.the_kind_of__audio_effect_for__die =
        p_living->the_kind_of__audio_effect_for__die;

    enum PLATFORM_Write_File_Error error = 
        PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&field, 
                sizeof(field),
                1, 
                p_file_handler);
}

void m_deserialize_handler__living__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {
    m_deserialize_handler__entity__default(
            p_game, 
            p_serialization_request, 
            p_this_serializer);

    Entity *p_living = (Entity*)p_this_serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    struct __living_field field;

    Quantity__u32 length_of__read = sizeof(field);
    enum PLATFORM_Read_File_Error error = 
        PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&field, 
                &length_of__read,
                1, 
                p_file_handler);

    p_living->direction =
        field.direction;
    p_living->hearts =
        field.hearts;
    p_living->energy_orbs =
        field.energy;
    p_living->humanoid_flags =
        field.humanoid_flags;
    p_living->stun__timer_u8 =
        field.stun_timer;
    p_living->equipment =
        field.equipment;
    p_living->goal__position__3i32F4 =
        field.goal__position__3i32F4;
    initialize_serialized_field_as__unlinked(
            &p_living->goal__s_entity_ptr, 
            field.goal__entity_identifier);
    p_living->the_kind_of__audio_effect_for__alert =
        field.the_kind_of__audio_effect_for__alert;
    p_living->the_kind_of__audio_effect_for__hurt =
        field.the_kind_of__audio_effect_for__hurt;
    p_living->the_kind_of__audio_effect_for__die =
        field.the_kind_of__audio_effect_for__die;

    // TODO: verify read length.
}
