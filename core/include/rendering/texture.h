#ifndef TEXTURE_H
#define TEXTURE_H

#include "defines_weak.h"
#include <defines.h>

static inline 
void set_texture_flags_as__hidden(
        Texture_Flags *p_texture_flags) {
    *p_texture_flags |= 
        TEXTURE_FLAG__IS_HIDDEN;
}

static inline 
void set_texture_flags_as__visible(
        Texture_Flags *p_texture_flags) {
    *p_texture_flags &= 
        ~TEXTURE_FLAG__IS_HIDDEN;
}

static inline 
bool is_texture_flags__hidden(
        Texture_Flags texture_flags) {
    return texture_flags 
        & TEXTURE_FLAG__IS_HIDDEN;
}

static inline
bool is_texture_flags__allocated(
        Texture_Flags texture_flags) {
    return texture_flags
        & TEXTURE_FLAG__IS_ALLOCATED;
}

static inline
void set_texture_flags_as__allocated(
        Texture_Flags *p_texture_flags) {
    *p_texture_flags |=
        TEXTURE_FLAG__IS_ALLOCATED;
}

static inline
void set_texture_flags_as__deallocated(
        Texture_Flags *p_texture_flags) {
    *p_texture_flags &=
        ~TEXTURE_FLAG__IS_ALLOCATED;
}

static inline
Texture_Flags get_texture_flags__rendering_method(
        Texture_Flags texture_flags) {
    return texture_flags
        & TEXTURE_FLAG__RENDER_METHOD__MASK;
}

#endif
