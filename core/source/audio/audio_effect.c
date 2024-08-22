#include "defines.h"
#include <audio/audio_effect.h>

void initialize_audio_effect(
        Audio_Effect *p_audio_effect,
        void *p_audio_handle,
        enum Audio_Effect_Kind the_kind_of__audio_effect,
        Audio_Flags__u8 audio_flags,
        Timer__u32 duration_of__audio) {
    p_audio_effect->the_kind_of__audio_effect =
        the_kind_of__audio_effect;
    p_audio_effect->p_audio_instance_handle =
        p_audio_handle;
    p_audio_effect->audio_flags__u8 =
        audio_flags;
    p_audio_effect->timer_for__audio =
        duration_of__audio;
}

Audio_Effect *play_audio_effect_and__forget(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        enum Audio_Effect_Kind the_kind_of__audio_effect,
        Audio_Flags__u8 audio_flags,
        Timer__u32 duration_of__audio) {
    Audio_Effect *p_audio_effect = 
        PLATFORM_allocate_audio_effect(
            p_PLATFORM_audio_context);
    if (!p_audio_effect)
        return 0;
    set_audio_effect(
            p_audio_effect, 
            the_kind_of__audio_effect, 
            audio_flags | AUDIO_FLAG__RELEASE_ON_COMPLETE,  
            duration_of__audio);
    PLATFORM_play_audio_effect(
            p_PLATFORM_audio_context, 
            p_audio_effect);
    return p_audio_effect;
}
