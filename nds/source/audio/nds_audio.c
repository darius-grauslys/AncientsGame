#include "audio/nds_audio.h"
#include "defines.h"
#include "defines_weak.h"
#include "mm_types.h"
#include "random.h"
#include "soundbank_bin.h"
#include "soundbank.h"

PLATFORM_Audio_Context _NDS_audio_context;

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
}

void PLATFORM_play_audio__effect(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        enum Audio_Effect_Kind the_kind_of__audio_effect) {
    // TODO:    implemenet audio handles in core
    //          to allow ownership of audio instance.
    //          That way we can prevent interruptions of it.
    Psuedo_Random__u32 random = 0;
    mm_word sound = 0;
    switch (the_kind_of__audio_effect) {
        default:
            debug_error("NDS::PLATFORM_play_audio__effect, unsupported audio effect kind: %d", the_kind_of__audio_effect);
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
    mm_sfxhand sound_handle = mmEffect(sound);
    //Allow sound to be interrupted
    mmEffectRelease(sound_handle);
}

void PLATFORM_play_audio__stream(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        enum Audio_Stream_Kind the_kind_of__audio_stream) {

}

bool PLATFORM_is_audio__streaming(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {
    return p_PLATFORM_audio_context->is_audio_context__streaming;
}
