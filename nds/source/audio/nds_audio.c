#include "audio/nds_audio.h"
#include "audio/audio_effect.h"
#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "mm_types.h"
#include "nds_defines.h"
#include "random.h"
#include "soundbank_bin.h"
#include "soundbank.h"
#include "timer.h"

PLATFORM_Audio_Context _NDS_audio_context;

static inline
Audio_Effect *NDS_get_p_audio_effect_by__index_in__audio_context(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        Index__u8 index_of__audio_effect) {
    return &p_PLATFORM_audio_context->audio_effects[index_of__audio_effect];
}

static inline
void NDS_set_p_audio_effect__max_mod_handle(
        Audio_Effect *p_audio_effect,
        mm_word *p_max_mod_sound) {
    *((mm_sfxhand*)p_audio_effect->p_audio_instance_handle) = 
        mmEffect(*p_max_mod_sound);
}

static inline
void NDS_release_p_audio_effect(
        Audio_Effect *p_audio_effect) {
    mmEffectRelease(*((mm_sfxhand*)p_audio_effect->p_audio_instance_handle));
    set_audio_as__inactive(p_audio_effect);
}

void PLATFORM_initialize_audio(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {
    initialize_repeatable_psuedo_random(
            &p_PLATFORM_audio_context->randomizer, 
            (Psuedo_Random_Seed__u32)p_PLATFORM_audio_context);
    mmInitDefaultMem((mm_addr)soundbank_bin);

    for (Index__u8 index_of__effect = 0;
            index_of__effect < MSL_BANKSIZE;
            index_of__effect++) {
        mmLoadEffect(index_of__effect);
    }

    for (Index__u8 index_of__audio_effect = 0;
            index_of__audio_effect < NDS_MAX_QUANTITY_OF__AUDIO_EFFECTS;
            index_of__audio_effect++) {
        Audio_Effect *p_audio_effect =
            NDS_get_p_audio_effect_by__index_in__audio_context(
                    p_PLATFORM_audio_context, 
                    index_of__audio_effect);
        initialize_audio_effect(
                p_audio_effect, 
                &p_PLATFORM_audio_context->maxmod_sfx_handles[
                    index_of__audio_effect], 
                Audio_Effect_Kind__None, 
                AUDIO_FLAGS__NONE, 
                (Timer__u32){0, 0});
    }
}

Audio_Effect *PLATFORM_allocate_audio_effect(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {
    Audio_Effect *p_audio_effect = 0;
    for (Index__u8 index_of__audio_effect = 0;
            index_of__audio_effect < NDS_MAX_QUANTITY_OF__AUDIO_EFFECTS;
            index_of__audio_effect++) {
        Audio_Effect *p_audio_effect__candidate =
            NDS_get_p_audio_effect_by__index_in__audio_context(
                    p_PLATFORM_audio_context, 
                    index_of__audio_effect);
        if (is_audio__active(p_audio_effect__candidate))
            continue;
        p_audio_effect = p_audio_effect__candidate;
        break;
    }

    if (!p_audio_effect) {
#ifndef NDEBUG
        debug_warning("NDS::PLATFORM_allocate_audio_effect, failed to allocate audio_effect.");
#endif
        return 0;
    }

    set_audio_as__active(p_audio_effect);
    return p_audio_effect;
}

void PLATFORM_play_audio_effect(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        Audio_Effect *p_audio_effect) {

    Psuedo_Random__u32 random = 0;
    mm_word sound = 0;
    switch (p_audio_effect->the_kind_of__audio_effect) {
        default:
            debug_error("NDS::PLATFORM_play_audio__effect, unsupported audio effect kind: %d", p_audio_effect->the_kind_of__audio_effect);
            return;
        case Audio_Effect_Kind__Footstep__Wood:
            random = get_pseudo_random_i32__intrusively(
                    &p_PLATFORM_audio_context->randomizer)
                & MASK(3);
            random = (random + 1) >> 1;
            switch (random) {
                default:
                case 0:
                    sound = SFX_FOOTSTEP_WOOD_1;
                    break;
                case 1:
                    sound = SFX_FOOTSTEP_WOOD_2;
                    break;
                case 2:
                    sound = SFX_FOOTSTEP_WOOD_3;
                    break;
            }
            break;
        case Audio_Effect_Kind__Footstep__Rock:
            random = get_pseudo_random_i32__intrusively(
                    &p_PLATFORM_audio_context->randomizer)
                & MASK(3);
            random = (random + 1) >> 1;
            switch (random) {
                default:
                case 0:
                    sound = SFX_FOOTSTEP_STONE_1;
                    break;
                case 1:
                    sound = SFX_FOOTSTEP_STONE_2;
                    break;
                case 2:
                    sound = SFX_FOOTSTEP_STONE_3;
                    break;
            }
            break;
        case Audio_Effect_Kind__Footstep__Metal:
            random = get_pseudo_random_i32__intrusively(
                    &p_PLATFORM_audio_context->randomizer)
                & MASK(3);
            random = (random + 1) >> 1;
            switch (random) {
                default:
                case 0:
                    sound = SFX_FOOTSTEP_METAL_1;
                    break;
                case 1:
                    sound = SFX_FOOTSTEP_METAL_2;
                    break;
                case 2:
                    sound = SFX_FOOTSTEP_METAL_3;
                    break;
            }
            break;
        case Audio_Effect_Kind__Footstep__Dirt:
            random = get_pseudo_random_i32__intrusively(
                    &p_PLATFORM_audio_context->randomizer)
                & MASK(2);
            switch (random) {
                default:
                case 0:
                    sound = SFX_FOOTSTEP_SOIL_1;
                    break;
                case 1:
                    sound = SFX_FOOTSTEP_SOIL_2;
                    break;
            }
            break;
        case Audio_Effect_Kind__Footstep__Grass:
            random = get_pseudo_random_i32__intrusively(
                    &p_PLATFORM_audio_context->randomizer)
                & MASK(2);
            switch (random) {
                default:
                case 0:
                    sound = SFX_FOOTSTEP_GRASS_1;
                    break;
                case 1:
                    sound = SFX_FOOTSTEP_GRASS_2;
                    break;
            }
            break;
        case Audio_Effect_Kind__Footstep__Sand:
            random = get_pseudo_random_i32__intrusively(
                    &p_PLATFORM_audio_context->randomizer)
                & MASK(3);
            random = (random + 1) >> 1;
            switch (random) {
                default:
                case 0:
                    sound = SFX_FOOTSTEP_SAND_1;
                    break;
                case 1:
                    sound = SFX_FOOTSTEP_SAND_2;
                    break;
                case 2:
                    sound = SFX_FOOTSTEP_SAND_3;
                    break;
            }
            break;
        case Audio_Effect_Kind__Weapon__Melee:
            random = get_pseudo_random_i32__intrusively(
                    &p_PLATFORM_audio_context->randomizer)
                & MASK(3);
            random = (random + 1) >> 1;
            switch (random) {
                default:
                case 0:
                    sound = SFX_SWING_1;
                    break;
                case 1:
                    sound = SFX_SWING_2;
                    break;
                case 2:
                    sound = SFX_SWING_3;
                    break;
            }
            break;
        case Audio_Effect_Kind__Monster__Skeleton__Alert:
            random = get_pseudo_random_i32__intrusively(
                    &p_PLATFORM_audio_context->randomizer)
                & MASK(2);
            switch (random) {
                default:
                case 0:
                    sound = SFX_SHADE_ALERT_1;
                    break;
                case 1:
                    sound = SFX_SHADE_ALERT_2;
                    break;
            }
            break;
        case Audio_Effect_Kind__Monster__Skeleton__Die:
            sound = SFX_SHADE_DEATH_1;
            break;
    }

    *((mm_sfxhand*)p_audio_effect->p_audio_instance_handle) = mmEffect(sound);
}

void PLATFORM_poll_audio_effects(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {
    for (Index__u8 index_of__audio_effect = 0;
            index_of__audio_effect < NDS_MAX_QUANTITY_OF__AUDIO_EFFECTS;
            index_of__audio_effect++) {
        Audio_Effect *p_audio_effect =
            NDS_get_p_audio_effect_by__index_in__audio_context(
                    p_PLATFORM_audio_context, 
                    index_of__audio_effect);

        if (poll_timer_u32(&p_audio_effect->timer_for__audio)) {
            if (is_audio__released_on_completion(p_audio_effect)) {
                NDS_release_p_audio_effect(p_audio_effect);
            } else {
                reset_timer_u32(&p_audio_effect->timer_for__audio);
                // TODO: support looping.
            }
        }
    }
}

void PLATFORM_play_audio__stream(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        enum Audio_Stream_Kind the_kind_of__audio_stream) {

}

bool PLATFORM_is_audio__streaming(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {
    return p_PLATFORM_audio_context->is_audio_context__streaming;
}
