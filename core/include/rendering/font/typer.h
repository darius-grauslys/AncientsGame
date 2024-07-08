#ifndef TYPER_H
#define TYPER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_typer(
        Typer *p_typer,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height,
        i32 x__cursor, i32 y__cursor);

void initialize_typer_with__font(
        Typer *p_typer,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height,
        i32 x__cursor, i32 y__cursor,
        Font *p_font);

bool poll_typer_for__cursor_wrapping(
        Typer *p_typer,
        Font_Letter *p_font_letter);

void put_c_string_in__typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Typer *p_typer,
        const char *c_string,
        Quantity__u32 max_length_of__c_string);

static inline
void move_typer_cursor(
        Typer *p_typer,
        Font_Letter *p_font_letter) {
    p_typer->cursor_position__3i32
        .x__i32 +=
        p_font_letter->width_of__font_letter;
}

static inline
Font_Letter *get_p_font_letter_from__typer(
        Typer *p_typer,
        unsigned char letter) {
    return &p_typer->p_font->font_lookup_table[letter];
}

static inline
void set_PLATFORM_texture_target_for__typer(
        Typer *p_typer,
        PLATFORM_Texture *p_PLATFORM_texture) {
    p_typer->p_PLATFORM_texture__typer_target =
        p_PLATFORM_texture;
}

#endif
