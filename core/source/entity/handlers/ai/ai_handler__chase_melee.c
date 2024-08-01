#include "entity/handlers/ai/ai_handler__chase_melee.h"
#include "defines.h"
#include "defines_weak.h"
#include "degree.h"
#include "entity/entity.h"
#include "entity/handlers/ai/ai_handler__dummy.h"
#include "entity/humanoid.h"
#include "game.h"
#include "game_action/game_action.h"
#include "numerics.h"
#include "rendering/animate_humanoid.h"
#include "rendering/animate_sprite.h"
#include "serialization/serialized_field.h"
#include "vectors.h"

void m_entity_ai_handler__chase_melee(
        Entity *this_chasing_melee,
        Game *p_game) {
    Entity *p_player = get_p_local_player_from__game(p_game);
    if (!p_player) {
        // m_entity_ai_handler__dummy(
        //         this_chasing_melee, 
        //         p_game);
        return;
    }

    switch (get_animation_kind_from__sprite_wrapper(
                get_p_sprite_wrapper_from__entity(this_chasing_melee))) {
        default:
            break;
        case Sprite_Animation_Kind__Humanoid__Die:
        case Sprite_Animation_Kind__Humanoid__Hurt:
        case Sprite_Animation_Kind__Humanoid__Use:
            return;
    }

    if (is_p_serialized_field__linked(
                &this_chasing_melee->goal__s_entity_ptr)) {
        Entity *p_target = 
            this_chasing_melee
            ->goal__s_entity_ptr
            .p_serialized_field__entity;

        i32 distance_squared_from__target =
            get_distance_squared_of__vector_3i32F4(
                    subtract_vectors__3i32F4(
                        this_chasing_melee->hitbox.position__3i32F4, 
                        p_target->hitbox.position__3i32F4));

        if (distance_squared_from__target
                >= i32_to__i32F4(64 << 6)) {
            initialize_serialized_field_as__unassigned(
                    &this_chasing_melee->goal__s_entity_ptr);
            return;
        } else if (
                distance_squared_from__target
                < i32_to__i32F4(96)) {
            humanoid__use(
                    p_game,
                    this_chasing_melee);
            return;
        }

        Degree__u9 angle_to__target =
            get_angle_between__vectors_3i32(
                    vector_3i32F4_to__vector_3i32(
                        this_chasing_melee->hitbox.position__3i32F4), 
                    vector_3i32F4_to__vector_3i32(
                        p_target->hitbox.position__3i32F4));
        Vector__3i32F4 movement__3i32F4 =
            get_2i32F4_offset_from__angle(angle_to__target);
        movement__3i32F4.x__i32F4 >>= 1;
        movement__3i32F4.y__i32F4 >>= 1;

        set_humanoid__direction(
                this_chasing_melee, 
                get_direction_from__angle(angle_to__target));

        animate_humanoid__walk(this_chasing_melee);
        invoke_action__apply_velocity_to__entity(
                p_game, 
                this_chasing_melee, 
                movement__3i32F4);
        return;
    }

    i32 distance_squared_from__player =
        get_distance_squared_of__vector_3i32F4(
                subtract_vectors__3i32F4(
                    this_chasing_melee->hitbox.position__3i32F4, 
                    p_player->hitbox.position__3i32F4));

    if (distance_squared_from__player
            < i32_to__i32F4(64 << 6)) {
        point_serialized_field_to__this_serialized_struct(
                &this_chasing_melee->goal__s_entity_ptr, 
                p_player);
        if (this_chasing_melee->the_kind_of__audio_effect_for__alert
                != Audio_Effect_Kind__None) {
            PLATFORM_play_audio__effect(
                    get_p_PLATFORM_audio_context_from__game(p_game), 
                    this_chasing_melee->the_kind_of__audio_effect_for__alert);
        }
        return;
    }

    if (is_vectors_3i32F4__out_of_bounds(
                this_chasing_melee->goal__position__3i32F4)) {
        return;
    }

    if (8 << 6 > get_distance_squared_of__vector_3i32F4(
                subtract_vectors__3i32F4(
                    this_chasing_melee->hitbox.position__3i32F4, 
                    this_chasing_melee->goal__position__3i32F4))) {
        return;
    }

    Degree__u9 angle_to__goal =
        get_angle_between__vectors_3i32(
                vector_3i32F4_to__vector_3i32(
                    this_chasing_melee->hitbox.position__3i32F4),
                vector_3i32F4_to__vector_3i32(
                    this_chasing_melee->goal__position__3i32F4));

    Vector__3i32F4 movement__3i32F4 =
        get_2i32F4_offset_from__angle(angle_to__goal);
    movement__3i32F4.x__i32F4 >>= 1;
    movement__3i32F4.y__i32F4 >>= 1;

    set_humanoid__direction(
            this_chasing_melee, 
            get_direction_from__angle(angle_to__goal));

    animate_humanoid__walk(this_chasing_melee);
    invoke_action__apply_velocity_to__entity(
            p_game, 
            this_chasing_melee, 
            movement__3i32F4);
}
