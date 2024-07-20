#include "inventory/implemented/weapon.h"
#include "collisions/collision_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "degree.h"
#include "entity/humanoid.h"
#include "entity/reserves.h"
#include "game.h"
#include "game_action/game_action.h"
#include "inventory/item.h"
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

void m_item_use_handler__weapon(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game) {
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

    Vector__3i32F4 ray_offset__3i32F4 =
        get_2i32F4_offset_from__angle(
                angle_of__attack);
    ray_offset__3i32F4.x__i32F4 <<= 3;
    ray_offset__3i32F4.y__i32F4 <<= 3;
    Vector__3i32F4 cone_point__3i32F4 =
        add_vectors__3i32F4(
                cone_origin, 
                ray_offset__3i32F4);
    Entity *p_entity =
        get_p_entity_from__collision_manager_with__3i32F4(
                get_p_collision_manager_from__game(p_game), 
                cone_point__3i32F4);
    if (p_entity && p_entity != p_entity_user) {
        invoke_action__apply_heart_damage_to__entity(
                p_game, 
                p_entity_user, 
                p_entity, 
                &damage_spec);
    }
}
