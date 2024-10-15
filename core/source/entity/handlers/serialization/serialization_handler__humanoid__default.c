#include "defines.h"
#include "entity/handlers/serialization/serialization_handler__living__default.h"
#include "game.h"
#include "inventory/inventory_manager.h"
#include "serialization/serialized_field.h"
#include <entity/handlers/serialization/serialization_handler__humanoid__default.h>

struct __humanoid_field {
    Armor_Properties            humanoid__armor_properties;
    Identifier__u32             identifer__inventory_ptr;
    Sustenance__u8              humanoid__primary_sustenance__u8;
    Sustenance__u8              humanoid__secondary_sustenance__u8;
    enum Homeostasis_Update_Kind kind_of_homeostasis__update;
    Homeostasis__i8             humanoid__homeostasis__i8;
    Timer__u16                  humanoid__homeostasis__timer_u16;
};

void m_serialize_handler__humanoid__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {
    m_serialize_handler__living__default(
            p_game, 
            p_serialization_request, 
            p_this_serializer);

    Entity *p_humanoid = (Entity*)p_this_serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    struct __humanoid_field field;

    field.humanoid__armor_properties =
        p_humanoid->humanoid__armor_properties;
    field.identifer__inventory_ptr =
        p_humanoid->s_humanoid__inventory_ptr
        .identifier_for__serialized_field;
    field.humanoid__primary_sustenance__u8 =
        p_humanoid->humanoid__primary_sustenance__u8;
    field.humanoid__secondary_sustenance__u8 =
        p_humanoid->humanoid__secondary_sustenance__u8;
    field.kind_of_homeostasis__update =
        p_humanoid->kind_of_homeostasis__update;
    field.humanoid__homeostasis__timer_u16 =
        p_humanoid->humanoid__homeostasis__timer_u16;

    enum PLATFORM_Write_File_Error error = 
        PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&field, 
                sizeof(field),
                1, 
                p_file_handler);

    if (!resolve_s_inventory_ptr_to__inventory_manager(
                get_p_inventory_manager_from__game(p_game), 
                &p_humanoid->s_humanoid__inventory_ptr)) {
        return;
    }

    Inventory *p_inventory =
        p_humanoid->s_humanoid__inventory_ptr.p_serialized_field__inventory;

    p_inventory->_serializer.m_serialize_handler(
            p_game,
            p_serialization_request,
            &p_inventory->_serializer);
}

void m_deserialize_handler__humanoid__default(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {
    m_deserialize_handler__living__default(
            p_game, 
            p_serialization_request, 
            p_this_serializer);

    Entity *p_humanoid = (Entity*)p_this_serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    struct __humanoid_field field;

    Quantity__u32 length_of__read = sizeof(field);
    enum PLATFORM_Read_File_Error error = 
        PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&field, 
                &length_of__read,
                1, 
                p_file_handler);

    // TODO: verify read length.

    p_humanoid->humanoid__armor_properties =
        field.humanoid__armor_properties;
    initialize_serialized_field_as__unlinked(
            &p_humanoid->s_humanoid__inventory_ptr, 
            field.identifer__inventory_ptr);
    p_humanoid->humanoid__primary_sustenance__u8 =
        field.humanoid__primary_sustenance__u8;
    p_humanoid->humanoid__secondary_sustenance__u8 =
        field.humanoid__secondary_sustenance__u8;
    p_humanoid->kind_of_homeostasis__update =
        field.kind_of_homeostasis__update;
    p_humanoid->humanoid__homeostasis__timer_u16 =
        field.humanoid__homeostasis__timer_u16;

    Inventory *p_inventory =
        allocate_p_inventory_in__inventory_manager(
                get_p_inventory_manager_from__game(p_game));

    if (!p_inventory)
        return;

    initialize_serialized_field(
            &p_humanoid->s_humanoid__inventory_ptr, 
            p_inventory, 
            p_inventory->_serialization_header.uuid);

    p_inventory->_serializer.m_deserialize_handler(
            p_game,
            p_serialization_request,
            &p_inventory->_serializer);
}
