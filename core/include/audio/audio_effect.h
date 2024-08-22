#ifndef AUDIO_EFFECT_H
#define AUDIO_EFFECT_H

#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
void initialize_audio_effect(
        Audio_Effect *p_audio_effect,
        void *p_audio_handle,
        enum Audio_Effect_Kind the_kind_of__audio_effect,
        Audio_Flags__u8 audio_flags,
        Timer__u32 duration_of__audio);

static inline
void set_audio_effect(
        Audio_Effect *p_audio_effect,
        enum Audio_Effect_Kind the_kind_of__audio_effect,
        Audio_Flags__u8 audio_flags,
        Timer__u32 duration_of__audio) {
    initialize_audio_effect(
            p_audio_effect, 
            p_audio_effect->p_audio_instance_handle, 
            the_kind_of__audio_effect, 
            audio_flags
            | (p_audio_effect->audio_flags__u8 & AUDIO_FLAG__IS_ACTIVE), 
            duration_of__audio);
}

Audio_Effect *play_audio_effect_and__forget(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        enum Audio_Effect_Kind the_kind_of__audio_effect,
        Audio_Flags__u8 audio_flags,
        Timer__u32 duration_of__audio);

static inline
bool is_audio__active(Audio_Effect *p_audio_effect) {
    return p_audio_effect->audio_flags__u8
        & AUDIO_FLAG__IS_ACTIVE;
}

static inline
bool is_audio__released_on_completion(Audio_Effect *p_audio_effect) {
    return p_audio_effect->audio_flags__u8
        & AUDIO_FLAG__RELEASE_ON_COMPLETE;
}

static inline
bool is_audio__looping(Audio_Effect *p_audio_effect) {
    return p_audio_effect->audio_flags__u8
        & AUDIO_FLAG__IS_LOOPING;
}

static inline
void set_audio_as__active(Audio_Effect *p_audio_effect) {
    p_audio_effect->audio_flags__u8 |=
        AUDIO_FLAG__IS_ACTIVE;
}

static inline
void set_audio_as__inactive(Audio_Effect *p_audio_effect) {
    p_audio_effect->audio_flags__u8 &=
        ~AUDIO_FLAG__IS_ACTIVE;
}

static inline
void set_audio_as__releasing_on_completion(Audio_Effect *p_audio_effect) {
    p_audio_effect->audio_flags__u8 |=
        AUDIO_FLAG__RELEASE_ON_COMPLETE;
}

static inline
void set_audio_as__not_releasing_on_completion(Audio_Effect *p_audio_effect) {
    p_audio_effect->audio_flags__u8 &=
        ~AUDIO_FLAG__RELEASE_ON_COMPLETE;
}

static inline
void set_audio_as__looping(Audio_Effect *p_audio_effect) {
    p_audio_effect->audio_flags__u8 |=
        AUDIO_FLAG__IS_LOOPING;
}

static inline
void set_audio_as__not_looping(Audio_Effect *p_audio_effect) {
    p_audio_effect->audio_flags__u8 &=
        ~AUDIO_FLAG__IS_LOOPING;
}

#endif
