#include "inventory/implemented/weapon.h"
#include "collisions/collision_manager.h"
#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "degree.h"
#include "entity/entity.h"
#include "entity/humanoid.h"
#include "entity/reserves.h"
#include "game.h"
#include "game_action/game_action.h"
#include "inventory/item.h"
#include "platform.h"
#include "serialization/serialized_field.h"
#include "vectors.h"

void initialize_item_as__weapon(
        Item *p_item__weapon,
        enum Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Hearts_Damaging_Flags damage_type,
        Quantity__u8 quantity_of__damage) {
    initialize_item(
            p_item__weapon,
            the_kind_of__item,
            ITEM_FILTER_FLAG__INTERACTABLE,
            weight_of_each__item,
            m_item_use_handler__weapon,
            0, 0);
    p_item__weapon->weapon__damage_type =
        damage_type;
    p_item__weapon->weapon__quantity_of__damage_u8 =
        quantity_of__damage;
}

void f_trigger_box_collision_handler__weapon(
        Entity *p_entity_collision_source,
        Entity *p_entity_collided,
        Direction__u8 direction_of_collision,
        Game *p_game) {
    if (p_entity_collided
            == p_entity_collision_source->p_entity__owner) {
        return;
    }
    
    Game_Action duplicate_game_action =
        *p_entity_collision_source
        ->p_prepared_action;
    point_serialized_field_to__this_serialized_struct(
            &duplicate_game_action.s_entity__target,
            p_entity_collided);

    invoke_game_action(
            p_game, 
            &duplicate_game_action);
}

void m_item_use_handler__weapon(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game) {
    PLATFORM_play_audio__effect(
            get_p_PLATFORM_audio_context_from__game(p_game), 
            Audio_Effect_Kind__Weapon__Melee);

    Direction__u8 direct_of__attack =
        get_humanoid__direction(p_entity_user);
    Degree__u9 angle_of__attack =
        get_angle_from__direction(direct_of__attack);

    Vector__3i32F4 cone_origin =
        p_entity_user->hitbox.position__3i32F4;

    if (direct_of__attack & DIRECTION__NORTH) {
        cone_origin.y__i32F4 += 
            i32_to__i32F4(p_entity_user->hitbox.height__quantity_u32 >> 1);
    }
    if (direct_of__attack & DIRECTION__EAST) {
        cone_origin.y__i32F4 += 
            i32_to__i32F4(p_entity_user->hitbox.width__quantity_u32 >> 1);
    }
    if (direct_of__attack & DIRECTION__SOUTH) {
        cone_origin.y__i32F4 -= 
            i32_to__i32F4(p_entity_user->hitbox.height__quantity_u32 >> 1);
    }
    if (direct_of__attack & DIRECTION__WEST) {
        cone_origin.y__i32F4 -= 
            i32_to__i32F4(p_entity_user->hitbox.width__quantity_u32 >> 1);
    }

    Hearts_Damaging_Specifier damage_spec;
    damage_spec.hearts_damaging__flags =
        p_item_self->weapon__damage_type;
    damage_spec.quantity_of__damage =
        p_item_self->weapon__quantity_of__damage_u8;

    // TODO: the offset here is not perfect.
    Vector__3i32F4 ray_offset__3i32F4 =
        get_2i32F4_offset_from__angle(
                angle_of__attack);
    ray_offset__3i32F4.x__i32F4 <<= 2;
    ray_offset__3i32F4.y__i32F4 <<= 2;
    Vector__3i32F4 cone_point__3i32F4 =
        add_vectors__3i32F4(
                cone_origin, 
                ray_offset__3i32F4);

    Game_Action game_action__apply_heart_damage;
    initialize_game_action_as__apply_heart_damage_to__entity(
            &game_action__apply_heart_damage,
            p_entity_user, 
            0, 
            &damage_spec);

    Entity trigger_box;
    initialize_entity(
            &trigger_box, 
            Entity_Kind__Trigger_Box, 
            cone_point__3i32F4, 
            8, 8);
    apply_velocity_to__hitbox(
            &trigger_box.hitbox, 
            &ray_offset__3i32F4);
    trigger_box.p_entity__owner = p_entity_user;
    trigger_box.p_prepared_action = &game_action__apply_heart_damage;

    poll_collision_manager(
            get_p_collision_manager_from__game(p_game), 
            p_game,
            &trigger_box, 
            f_trigger_box_collision_handler__weapon);
}
