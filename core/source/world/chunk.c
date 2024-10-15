#include "collisions/collision_manager.h"
#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "entity/entity_manager.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "platform.h"
#include "platform_defines.h"
#include "serialization/serialized_field.h"
#include "serialization/serializer.h"
#include "vectors.h"
#include "world/tile.h"
#include <world/chunk.h>

void initialize_chunk(Chunk *p_chunk) {
    intialize_serializer(
            &p_chunk->_serializer, 
            sizeof(Chunk), 
            get_uuid__chunk(p_chunk), 
            m_serialize__chunk, 
            m_deserialize__chunk);
}

void f_foreach_inventory_container__serialize_into__chunk(
        Game *p_game,
        Inventory *p_inventory,
        Inventory_Manager *p_inventory_manager,
        void *p_data) {
    Serialization_Request *p_serialization_request =
        (Serialization_Request*)p_data;
    p_serialization_request->quantity_of__sub_serializations++;
    void *p_file_handler =
        p_serialization_request->p_file_handler;

    Quantity__u32 length_of__write =
        sizeof(Serialization_Header);
    enum PLATFORM_Write_File_Error error = PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)&p_inventory->_serialization_header, 
                length_of__write, 
                1, 
                p_file_handler);
    if (error) {
        debug_error("f_foreach_inventory_container__serialize_into__chunk, error: %d", error);
        return;
    }

    p_inventory->_serializer.m_serialize_handler(
            p_game,
            p_serialization_request,
            (Serializer*)p_inventory);

    release_p_inventory_in__inventory_manager(
            p_inventory_manager, 
            p_inventory);
}

void f_foreach_entity__serialize_into__chunk(
        Entity *p_entity,
        Game *p_game,
        void *p_data) {
    Serialization_Request *p_serialization_request =
        (Serialization_Request*)p_data;
    p_serialization_request->quantity_of__sub_serializations++;

    p_entity->_serializer.m_serialize_handler(
            p_game,
            p_serialization_request,
            (Serializer*)p_entity);

    set_entity_as__unloaded(p_entity);
}

void m_serialize__chunk(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_chunk__serializer) {

    Chunk *p_chunk = (Chunk*)p_this_chunk__serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    enum PLATFORM_Write_File_Error error = 
        PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)p_chunk->tiles, 
                sizeof(p_chunk->tiles), 
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    Quantity__u8 quantity_of__serialized__containers = 0;

    Index__u32 position_of__container_quantity_in__file =
        PLATFORM_get_position_in__file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_file_handler);

    error = PLATFORM_write_file(
            get_p_PLATFORM_file_system_context_from__game(p_game),
            &quantity_of__serialized__containers,
            1,
            1,
            p_file_handler);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    p_serialization_request->quantity_of__sub_serializations = 0;
    foreach_p_inventory_container_in__chunk_vector(
            get_p_inventory_manager_from__game(p_game), 
            p_serialization_request->position_of__serialization_3i32, 
            f_foreach_inventory_container__serialize_into__chunk, 
            p_game, 
            p_serialization_request);
    quantity_of__serialized__containers =
        p_serialization_request->quantity_of__sub_serializations;

    Quantity__u8 quantity_of__serialized__entities = 0;

    Index__u32 position_of__entity_quantity_in__file =
        PLATFORM_get_position_in__file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_file_handler);

    error = PLATFORM_write_file(
            get_p_PLATFORM_file_system_context_from__game(p_game),
            &quantity_of__serialized__entities,
            1,
            1,
            p_file_handler);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    // center hitbox to the center of the chunk.
    Vector__3i32F4 position_of__hitbox_3i32F4 =
        get_vector__3i32F4_using__i32(
                (p_serialization_request
                    ->position_of__serialization_3i32.x__i32
                    * CHUNK_WIDTH__IN_TILES * TILE_WIDTH__IN_PIXELS)
                + (CHUNK_WIDTH__IN_TILES * TILE_WIDTH__IN_PIXELS >> 1),
                (p_serialization_request
                    ->position_of__serialization_3i32.y__i32
                    * CHUNK_WIDTH__IN_TILES * TILE_WIDTH__IN_PIXELS)
                + (CHUNK_WIDTH__IN_TILES * TILE_WIDTH__IN_PIXELS >> 1),
                (p_serialization_request
                    ->position_of__serialization_3i32.z__i32
                    * CHUNK_DEPTH__IN_TILES * TILE_WIDTH__IN_PIXELS)
                + (CHUNK_WIDTH__IN_TILES * TILE_WIDTH__IN_PIXELS >> 1)
                );

    Hitbox_AABB serialization_hitbox;
    initialize_hitbox(
            &serialization_hitbox, 
            TILE_WIDTH__IN_PIXELS
            * CHUNK_WIDTH__IN_TILES, 
            TILE_WIDTH__IN_PIXELS
            * CHUNK_WIDTH__IN_TILES, 
            position_of__hitbox_3i32F4);

    p_serialization_request->quantity_of__sub_serializations = 0;
    // foreach_p_entity_within__hitbox(
    //         get_p_collision_manager_from__game(p_game), 
    //         &serialization_hitbox, 
    //         f_foreach_entity__serialize_into__chunk, 
    //         p_game, 
    //         p_serialization_request);

    Index__u32 position_at__end_of__file =
        PLATFORM_get_position_in__file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_file_handler);


    PLATFORM_set_position_in__file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            position_of__container_quantity_in__file, 
            p_file_handler);
    error = PLATFORM_write_file(
            get_p_PLATFORM_file_system_context_from__game(p_game),
            &quantity_of__serialized__containers,
            1,
            1,
            p_file_handler);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    PLATFORM_set_position_in__file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            position_of__entity_quantity_in__file, 
            p_file_handler);
    error = PLATFORM_write_file(
            get_p_PLATFORM_file_system_context_from__game(p_game),
            &quantity_of__serialized__entities,
            1,
            1,
            p_file_handler);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    PLATFORM_set_position_in__file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            position_at__end_of__file, 
            p_file_handler);

    clear_chunk_flags(p_chunk);
}

void m_deserialize__chunk(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_chunk__serializer) {

    Chunk *p_chunk =
        (Chunk*)p_this_chunk__serializer;
    void *p_file_handler =
        p_serialization_request->p_file_handler;

    Quantity__u32 length_of__read =
        sizeof(p_chunk->tiles);

    enum PLATFORM_Read_File_Error error = 
        PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                (u8*)p_chunk->tiles, 
                &length_of__read,
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    if (length_of__read
            != sizeof(p_chunk->tiles)) {
        // debug_error("m_serialize__chunk, bad read length: %d/%d", 
        //         length_of__read,
        //         sizeof(p_chunk->tiles));
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    length_of__read = 1;
    u8 quantity_of__serialized__containers = 0;
    error = PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                &quantity_of__serialized__containers, 
                &length_of__read,
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    for (Index__u8 index_of__serialized_container = 0;
            index_of__serialized_container < quantity_of__serialized__containers;
            index_of__serialized_container++) {
        Serialization_Header serialization_header;

        length_of__read = sizeof(Serialization_Header);
        error = PLATFORM_read_file(
                    get_p_PLATFORM_file_system_context_from__game(p_game), 
                    (u8*)&serialization_header, 
                    &length_of__read,
                    1, 
                    p_file_handler);
        if (error) {
            debug_error("m_serialize__chunk, failed error: %d", error);
            set_chunk_as__inactive(p_chunk);
            set_chunk_as__visually_updated(p_chunk);
            return;
        }

        Inventory *p_inventory =
            allocate_p_inventory_using__this_uuid_in__inventory_manager(
                    get_p_inventory_manager_from__game(p_game),
                    serialization_header.uuid);
        initialize_inventory(
                p_inventory, 
                serialization_header.uuid);
        if (!p_inventory) {
            debug_error("m_deserialize__chunk, p_inventory is null. IM full?");
            break;
        }

        p_inventory->_serializer.m_deserialize_handler(
                p_game,
                p_serialization_request,
                (Serializer*)p_inventory);
    }

    length_of__read = 1;
    u8 quantity_of__serialized__entities = 0;
    error = PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                &quantity_of__serialized__entities, 
                &length_of__read,
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_serialize__chunk, failed error: %d", error);
        set_chunk_as__inactive(p_chunk);
        set_chunk_as__visually_updated(p_chunk);
        return;
    }

    for (Index__u8 index_of__serialized_entity = 0;
            index_of__serialized_entity < quantity_of__serialized__entities;
            index_of__serialized_entity++) {
        // TODO: impl
        break;
        Entity *p_entity =
            allocate_entity_in__entity_manager(
                    p_game, 
                    get_p_entity_manager_from__game(p_game), 
                    Entity_Kind__None, 
                    VECTOR__3i32F4__OUT_OF_BOUNDS, 
                    get_p_world_from__game(p_game)
                    ->p_PLATFORM_graphics_window_for__world);
        if (!p_entity) {
            debug_error("m_deserialize__chunk, p_entity is null. EM full?");
            break;
        }

        initialize_entity(
                p_entity, 
                Entity_Kind__None, 
                VECTOR__3i32F4__OUT_OF_BOUNDS, 
                1, 
                1);
        p_entity->_serializer.m_deserialize_handler(
                p_game,
                p_serialization_request,
                (Serializer*)p_entity);
    }

    set_chunk_as__active(p_chunk);
}

Identifier__u32 get_uuid__chunk(
        Chunk *p_chunk) {
    return 1337;
    // TODO: impl
}
