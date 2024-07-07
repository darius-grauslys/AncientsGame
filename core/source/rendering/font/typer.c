#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "vectors.h"
#include <rendering/font/typer.h>

void initialize_typer(
        Typer *p_typer,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height,
        i32 x__cursor, i32 y__cursor) {
	debug_abort("not impl");
}

void initialize_typer_with__font(
        Typer *p_typer,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height,
        i32 x__cursor, i32 y__cursor,
        Font *p_font) {
	debug_abort("not impl");
}

bool poll_typer_for__cursor_wrapping(
        Typer *p_typer,
        Font_Letter *p_font_letter) {

    Hitbox_AABB font_letter_hitbox;
    initialize_hitbox(
            &font_letter_hitbox, 
            p_font_letter->width_of__font_letter, 
            p_font_letter->height_of__font_letter,
            vector_3i32_to__vector_3i32F4(p_typer->cursor_position__3i32));

    if (is_this_hitbox__fully_inside_this_hitbox__without_velocity(
                &font_letter_hitbox,
                &p_typer->text_bounding_box))
        return true;

    Vector__3i32 aa;
    initialize_vector_3i32_as__aa_bb_without__velocity(
            &aa, 
            &p_typer->text_bounding_box, 
            DIRECTION__SOUTH_WEST);

    p_typer->cursor_position__3i32.x__i32 =
        aa.x__i32;
    p_typer->cursor_position__3i32.y__i32 +=
        p_typer->p_font->max_height_of__font_letter;

    set_hitbox__position_with__3i32(
            &font_letter_hitbox,
            p_typer->cursor_position__3i32);

    return is_this_hitbox__fully_inside_this_hitbox__without_velocity(
                &font_letter_hitbox,
                &p_typer->text_bounding_box);
}

void put_c_string_in__typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Typer *p_typer,
        const unsigned char *c_string,
        Quantity__u32 max_length_of__c_string) {
    if (!max_length_of__c_string)
        return;
    if (!*c_string)
        return;

    do {
        PLATFORM_put_char_in__typer(
                p_PLATFORM_gfx_context, 
                p_typer, 
                *c_string);
    } while (*(++c_string) && --max_length_of__c_string);
}
