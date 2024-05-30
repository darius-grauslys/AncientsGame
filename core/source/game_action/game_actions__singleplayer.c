#include "defines.h"
#include "vectors.h"
#include "world/chunk.h"
#include "world/chunk_manager.h"
#include <game_action/game_actions__singleplayer.h>
#include <game_action/game_action.h>
#include <entity/entity_manager.h>
#include <collisions/hitbox_aabb.h>
#include <entity/reserves.h>

void handle_game_action__entity__flags__set(
        Entity *p_entity,
        Entity_Flags__u8 entity_flags) {
    p_entity->entity_flags = entity_flags;
}

void handle_game_action__entity__hitbox__apply_velocity(
        Entity *p_entity,
        Vector__3i32F4 velocity) {
    apply_velocity_to__hitbox(
            &p_entity->hitbox, 
            velocity);
}

void handle_game_action__entity__hitbox__set_velocity(
        Entity *p_entity,
        Vector__3i32F4 velocity) {
    set_velocity_to__hitbox(
            &p_entity->hitbox, 
            velocity);
}

void handle_game_action__entity__health__apply_damage(
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Damaging_Specifier hearts_damaging_specifier) {
    apply_hearts_damaging_specifier_to__entity(
            p_entity_target, 
            hearts_damaging_specifier);
}

void handle_game_action__entity__health__apply_healing(
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Healing_Specifier hearts_healing_specifier) {
    apply_hearts_healing_specifier_to__entity(
            p_entity_target, 
            hearts_healing_specifier);
}

void handle_game_action__entity__health__set(
        Entity *p_entity_source,
        Entity *p_entity_target,
        Resource_Reserve *hearts) {
    set_hearts_of__entity(
            p_entity_target, 
            hearts);
}

void handle_game_action__entity__energy__apply_damage(
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Damaging_Specifier energy_damage_specifier) {
    apply_energy_damaging_specifier_to__entity(
            p_entity_target, 
            energy_damage_specifier);
}

void handle_game_action__entity__energy__apply_healing(
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Healing_Specifier energy_healing_specifier) {
    apply_energy_healing_specifier_to__entity(
            p_entity_target, 
            energy_healing_specifier);
}

void handle_game_action__entity__energy__set(
        Entity *p_entity_source,
        Entity *p_entity_target,
        Resource_Reserve *energy_orbs) {
    set_energy_orbs_of__entity(
            p_entity_target, 
            energy_orbs);
}

void handle_game_action__entity__place__tile(
        Game *p_game,
        Entity *p_entity_source,
        Tile *tile,
        Direction__u8 direction_to_place_the__tile) {
    Vector__3i32F4 position = {
        p_entity_source->hitbox.x__i32F4,
        p_entity_source->hitbox.y__i32F4,
        p_entity_source->hitbox.z__i32F4
        // p_entity_source->hitbox.position__3i32F4.x__i32F4,
        // p_entity_source->hitbox.position__3i32F4.y__i32F4,
        // p_entity_source->hitbox.position__3i32F4.z__i32F4
    };

    offset_vector_by__direction(
            &position, 
            direction_to_place_the__tile);

    Tile *p_tile =
        get_tile_ptr_from__chunk_manager_with__v__3i32F4(
                &p_game->world.chunk_manager, 
                position);

    *p_tile = *tile;
}

void handle_game_action__entity__item_stack__pick_up(
        Entity *p_entity_source,
        Item_Stack *p_item_stack) {

}

void handle_game_action__entity__item_stack__drop(
        Entity *p_entity_source,
        Item_Stack *p_item_stack) {

}

void handle_game_action__entity__item_stack__consume(
        Entity *p_entity_source,
        Item_Stack *p_item_stack) {

}

void handle_game_action__entity__item_stack__equip(
        Entity *p_entity_source,
        Item_Stack *p_item_stack) {

}

void handle_game_action__entity(
        Game *p_game,
        Game_Action *p_game_action) {
    Entity *p_entity_source = 0;
    Entity *p_entity_target = 0;
    if (is_game_action_using__id_or_ptr(p_game_action->game_action_flags)) {
        p_entity_source =
            get_entity_ptr_from__entity_manager(
                    &p_game->world.entity_manager,
                    p_game_action->identifier__entity_source);
        p_entity_target =
            get_entity_ptr_from__entity_manager(
                    &p_game->world.entity_manager,
                    p_game_action->identifier__entity_target);
    } else {
        p_entity_source =
            p_game_action->p_entity_source;
        p_entity_target =
            p_game_action->p_entity_target;
    }
    enum Game_Action_Kind the_kind_of_game_action__this_action_is =
        p_game_action->the_kind_of_game_action__this_action_is;
    switch (the_kind_of_game_action__this_action_is) {
        default:
            debug_error("handle_game_action__entity, p_game_action is not an entity action.");
            return;
        case Game_Action_Kind__Entity__Flags__Set:
        case Game_Action_Kind__Entity__Hitbox__Apply_Velocity:
        case Game_Action_Kind__Entity__Hitbox__Set_Velocity:
        case Game_Action_Kind__Entity__Health__Apply_Damage:
        case Game_Action_Kind__Entity__Health__Apply_Healing:
        case Game_Action_Kind__Entity__Health__Set:
        case Game_Action_Kind__Entity__Energy__Apply_Damage:
        case Game_Action_Kind__Entity__Energy__Apply_Healing:
        case Game_Action_Kind__Entity__Energy__Set:
            if (!p_entity_target) {
                debug_error("Game_Action_Kind__Entity:%d, p_entity_target==0.",
                        the_kind_of_game_action__this_action_is);
                return;
            }
            switch (the_kind_of_game_action__this_action_is) {
                default:
                    break;
                case Game_Action_Kind__Entity__Flags__Set:
                    handle_game_action__entity__flags__set(
                            p_entity_target, 
                            p_game_action->entity_flags);
                    break;
                case Game_Action_Kind__Entity__Hitbox__Apply_Velocity:
                    handle_game_action__entity__hitbox__apply_velocity(
                            p_entity_target,
                            p_game_action->velocity_vector__apply);
                    break;
                case Game_Action_Kind__Entity__Hitbox__Set_Velocity:
                    handle_game_action__entity__hitbox__set_velocity(
                            p_entity_target,
                            p_game_action->velocity_vector__set);
                    break;
                case Game_Action_Kind__Entity__Health__Apply_Damage:
                    handle_game_action__entity__health__apply_damage(
                            p_entity_source,
                            p_entity_target,
                            p_game_action->hearts_damaging_specifier);
                    break;
                case Game_Action_Kind__Entity__Health__Apply_Healing:
                    handle_game_action__entity__health__apply_healing(
                            p_entity_source,
                            p_entity_target,
                            p_game_action->hearts_healing_specifier);
                    break;
                case Game_Action_Kind__Entity__Health__Set:
                    handle_game_action__entity__health__set(
                            p_entity_source,
                            p_entity_target,
                            &p_game_action->hearts);
                    break;
                case Game_Action_Kind__Entity__Energy__Apply_Damage:
                    handle_game_action__entity__energy__apply_damage(
                            p_entity_source,
                            p_entity_target,
                            p_game_action->energy_damage_specifier);
                    break;
                case Game_Action_Kind__Entity__Energy__Apply_Healing:
                    handle_game_action__entity__energy__apply_healing(
                            p_entity_source,
                            p_entity_target,
                            p_game_action->energy_healing_specifier);
                    break;
                case Game_Action_Kind__Entity__Energy__Set:
                    handle_game_action__entity__energy__set(
                            p_entity_source,
                            p_entity_target,
                            &p_game_action->energy_orbs);
                    break;
            }
            break;
        case Game_Action_Kind__Entity__Place_Tile:
        case Game_Action_Kind__Entity__Item_Stack__Pick_Up:
        case Game_Action_Kind__Entity__Item_Stack__Drop:
        case Game_Action_Kind__Entity__Item_Stack__Consume:
        case Game_Action_Kind__Entity__Item_Stack__Equip:
            if (!p_entity_source) {
                debug_error("Game_Action_Kind__Entity:%d, p_entity_source==0.",
                        the_kind_of_game_action__this_action_is);
                return;
            }
            switch (the_kind_of_game_action__this_action_is) {
                default:
                    break;
                case Game_Action_Kind__Entity__Place_Tile:
                case Game_Action_Kind__Entity__Item_Stack__Pick_Up:
                case Game_Action_Kind__Entity__Item_Stack__Drop:
                case Game_Action_Kind__Entity__Item_Stack__Consume:
                case Game_Action_Kind__Entity__Item_Stack__Equip:
                    break;
            }
            break;
    }
}

void m_game_action_handler_for__singleplayer(
        Game *p_this_game,
        Game_Action *p_game_action) {
    switch (p_game_action->the_kind_of_game_action__this_action_is) {
        default:
            debug_abort("m_game_action_handler_for__singleplayer, unhandled game action kind, %d.", p_game_action->the_kind_of_game_action__this_action_is);
            return;
        case Game_Action_Kind__Unknown:
            debug_error("m_game_action_handler, recieved unknown game action.");
        case Game_Action_Kind__None:
            return;
        case Game_Action_Kind__Entity__Flags__Set:
        case Game_Action_Kind__Entity__Hitbox__Apply_Velocity:
        case Game_Action_Kind__Entity__Health__Apply_Damage:
        case Game_Action_Kind__Entity__Health__Apply_Healing:
        case Game_Action_Kind__Entity__Health__Set:
        case Game_Action_Kind__Entity__Energy__Apply_Damage:
        case Game_Action_Kind__Entity__Energy__Apply_Healing:
        case Game_Action_Kind__Entity__Energy__Set:
        case Game_Action_Kind__Entity__Place_Tile:
        case Game_Action_Kind__Entity__Item_Stack__Pick_Up:
        case Game_Action_Kind__Entity__Item_Stack__Drop:
        case Game_Action_Kind__Entity__Item_Stack__Consume:
        case Game_Action_Kind__Entity__Item_Stack__Equip:
            handle_game_action__entity(
                    p_this_game, 
                    p_game_action);
            return;
    }
}