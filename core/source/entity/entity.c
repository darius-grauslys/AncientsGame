#include "audio/audio_effect.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/handlers/serialization/serialization_handler__entity__default.h"
#include "game.h"
#include "inventory/equipment.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "platform.h"
#include "serialization/serialized_field.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
#include "world/tile_logic_manager.h"
#include "world/world.h"
#include <entity/entity.h>
#include <entity/handlers/entity_handlers.h>
#include <debug/debug.h>
#include <rendering/sprite.h>
#include <rendering/animate_entity.h>
#include <collisions/hitbox_aabb.h>
#include <debug/debug.h>
#include <serialization/serialization_header.h>
#include <game_util.h>

bool can_entity_kind_have__armor(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    can_entity_kind_have__armor.");
            return false;
        case Entity_Kind__Zombie:
            return false;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

bool can_entity__move(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    can_entity__move.");
            return false;
        case Entity_Kind__Zombie:
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

bool is_entity__humanoid(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    is_entity__humanoid.");
            return false;
        case Entity_Kind__Zombie:
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

void initialize_entity(
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4,
        Quantity__u32 width,
        Quantity__u32 height) {
    initialize_serialization_header(
            &p_entity->_serialization_header,
            p_entity->_serialization_header.uuid,
            sizeof(Entity));
    p_entity->_serializer.m_serialize_handler =
        m_serialize_handler__entity__default;
    p_entity->_serializer.m_deserialize_handler =
        m_deserialize_handler__entity__default;

    p_entity->the_kind_of_entity__this_entity_is =
        kind_of_entity;

    p_entity->the_kind_of__audio_effect_for__alert =
        Audio_Effect_Kind__None;
    p_entity->the_kind_of__audio_effect_for__hurt =
        Audio_Effect_Kind__None;
    p_entity->the_kind_of__audio_effect_for__die =
        Audio_Effect_Kind__None;

    initialize_hitbox(
            &p_entity->hitbox, 
            width, 
            height, 
            position__3i32F4);

    p_entity->goal__position__3i32F4 =
        VECTOR__3i32F4__OUT_OF_BOUNDS;
    initialize_serialized_field_as__unassigned(
            &p_entity->goal__s_entity_ptr);

    initialize_timer_u8(
            &p_entity->footstep__timer_u8, 16);
    p_entity->m_entity_dispose_handler = 
        m_entity_dispose_handler__default;

    p_entity->entity_flags = ENTITY_FLAG__NONE;

    set_entity__enabled(p_entity);
    set_entity__is_updating_position(p_entity);
    set_entity__is_updating_graphics(p_entity);
}

void set_entity__armor(Entity *p_entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification) {
    p_entity->humanoid__armor_properties.the_kind_of_armor__this_armor_is =
        kind_of_armor;
    p_entity->humanoid__armor_properties.the_kind_of_modification__this_armor_has =
        kind_of_armor_modification;
}

void play_audio_of__entity_footstep(
        Game *p_game,
        Entity *p_entity) {
    Tile *p_tile =
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__game(p_game), 
                p_entity->hitbox.position__3i32F4);
    if (!p_tile)
        return;
    Quantity__u8 duration = 
        p_entity->footstep__timer_u8.start__u8;
    if (poll_timer_u8(&p_entity->footstep__timer_u8)) {
        reset_timer_u8(&p_entity->footstep__timer_u8);
        switch (p_tile->the_kind_of_tile__this_tile_is) {
            default:
                break;
            case Tile_Kind__Oak_Wood:
                play_audio_effect_and__forget(
                        get_p_PLATFORM_audio_context_from__game(p_game), 
                        Audio_Effect_Kind__Footstep__Wood, 
                        AUDIO_FLAGS__NONE, 
                        get_timer__u32(duration));
                break;
            case Tile_Kind__Stone_Brick:
            case Tile_Kind__Sandstone:
            case Tile_Kind__Stone:
                play_audio_effect_and__forget(
                        get_p_PLATFORM_audio_context_from__game(p_game), 
                        Audio_Effect_Kind__Footstep__Rock, 
                        AUDIO_FLAGS__NONE, 
                        get_timer__u32(duration));
                break;
            case Tile_Kind__Gold:
            case Tile_Kind__Iron:
                play_audio_effect_and__forget(
                        get_p_PLATFORM_audio_context_from__game(p_game), 
                        Audio_Effect_Kind__Footstep__Metal, 
                        AUDIO_FLAGS__NONE, 
                        get_timer__u32(duration));
                break;
            case Tile_Kind__Diamond:
            case Tile_Kind__Amethyst:
                play_audio_effect_and__forget(
                        get_p_PLATFORM_audio_context_from__game(p_game), 
                        Audio_Effect_Kind__Footstep__Rock, 
                        AUDIO_FLAGS__NONE, 
                        get_timer__u32(duration));
                break;
            case Tile_Kind__Dirt:
                play_audio_effect_and__forget(
                        get_p_PLATFORM_audio_context_from__game(p_game), 
                        Audio_Effect_Kind__Footstep__Dirt, 
                        AUDIO_FLAGS__NONE, 
                        get_timer__u32(duration));
                break;
            case Tile_Kind__Sand:
                play_audio_effect_and__forget(
                        get_p_PLATFORM_audio_context_from__game(p_game), 
                        Audio_Effect_Kind__Footstep__Sand, 
                        AUDIO_FLAGS__NONE, 
                        get_timer__u32(duration));
                break;
            case Tile_Kind__Grass:
                play_audio_effect_and__forget(
                        get_p_PLATFORM_audio_context_from__game(p_game), 
                        Audio_Effect_Kind__Footstep__Grass, 
                        AUDIO_FLAGS__NONE, 
                        get_timer__u32(duration));
                break;
        }
    }
}

void entity__interact(
        Game *p_game,
        Entity *p_entity) {
    // Entity takes precedence over tile.
    
    Vector__3i32F4 vector_3i32F4__front_of_entity =
        get_vector_3i32F4_thats__infront_of_this__entity(
                p_entity);

    Entity *p_entity_to__interact_with =
        get_p_entity_from__world_using__3i32F4(
                get_p_world_from__game(p_game), 
                vector_3i32F4__front_of_entity);
    
    if (p_entity_to__interact_with) {
        // TODO: interaction handler for NPCs, or PC to PC.
        return;
    }

    Tile_Vector__3i32 tile_vector__3i32 =
        get_tile_vector_thats__infront_of_this__entity(
                p_entity);

    (void)poll_tile_for__interaction(
            p_game, 
            p_entity, 
            tile_vector__3i32);
}

