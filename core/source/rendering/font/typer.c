#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "rendering/font/message.h"
#include "vectors.h"
#include <rendering/font/typer.h>

void initialize_typer(
        Typer *p_typer,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height,
        i32 x__cursor, i32 y__cursor) {
    initialize_hitbox(
            &p_typer->text_bounding_box, 
            width, height, 
            get_vector__3i32F4_using__i32(
                x, y, 0));
    p_typer->cursor_position__3i32 =
        get_vector__3i32(
                x__cursor,
                y__cursor, 
                0);
    p_typer->p_font = 0;
    p_typer->p_PLATFORM_texture__typer_target = 0;
}

void initialize_typer_with__font(
        Typer *p_typer,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height,
        i32 x__cursor, i32 y__cursor,
        Font *p_font) {
    initialize_typer(
            p_typer, 
            x, 
            y, 
            width, 
            height, 
            x__cursor, 
            y__cursor);

    p_typer->p_font = p_font;
    p_typer->p_PLATFORM_texture__typer_target = 0;
}

bool poll_typer_for__cursor_wrapping(
        Typer *p_typer,
        Font_Letter *p_font_letter) {

    Hitbox_AABB font_letter_hitbox;
    initialize_hitbox(
            &font_letter_hitbox, 
            p_font_letter->width_of__font_letter, 
            p_font_letter->height_of__font_letter,
            get_vector__3i32F4_using__i32(0, 0, 0));

    Vector__3i32F4 hitbox_position =
        get_vector__3i32F4_using__i32(
                p_typer->cursor_position__3i32.x__i32
                + (p_font_letter->width_of__font_letter >> 1),
                p_typer->cursor_position__3i32.y__i32
                + (p_font_letter->height_of__font_letter >> 1),
                0);

    add_p_vectors__3i32F4(
            &hitbox_position, 
            &p_typer->text_bounding_box.position__3i32F4);

    hitbox_position.x__i32F4 -=
        i32_to__i32F4(p_typer->text_bounding_box.width__quantity_u32 >> 1);
    hitbox_position.y__i32F4 -=
        i32_to__i32F4(p_typer->text_bounding_box.height__quantity_u32 >> 1);

    font_letter_hitbox.position__3i32F4 =
        hitbox_position;

    if (is_this_hitbox__fully_inside_this_hitbox__without_velocity(
                &font_letter_hitbox,
                &p_typer->text_bounding_box)) {
        // debug_info(
        //         "good: %d, %d",
        //         hitbox_position.x__i32F4 >> 4,
        //         hitbox_position.y__i32F4 >> 4);
        return true;
    }

    // debug_info(
    //         "-- BAD -- %d, %d",
    //         hitbox_position.x__i32F4 >> 4,
    //         hitbox_position.y__i32F4 >> 4);
    // debug_info(
    //         "from: %d, %d",
    //         (p_typer->text_bounding_box.position__3i32F4.x__i32F4 >> 4)
    //         - (p_typer->text_bounding_box.width__quantity_u32 >> 1),
    //         (p_typer->text_bounding_box.position__3i32F4.y__i32F4 >> 4)
    //         - (p_typer->text_bounding_box.height__quantity_u32 >> 1)
    //         );
    // debug_abort(
    //         "to: %d, %d",
    //         (p_typer->text_bounding_box.position__3i32F4.x__i32F4 >> 4)
    //         + (p_typer->text_bounding_box.width__quantity_u32 >> 1),
    //         (p_typer->text_bounding_box.position__3i32F4.y__i32F4 >> 4)
    //         + (p_typer->text_bounding_box.height__quantity_u32 >> 1)
    //         );

    Vector__3i32 aa;
    initialize_vector_3i32_as__aa_bb_without__velocity(
            &aa, 
            &p_typer->text_bounding_box, 
            DIRECTION__SOUTH_WEST);

    p_typer->cursor_position__3i32.x__i32 = 0;
    p_typer->cursor_position__3i32.y__i32 +=
        p_typer->p_font->max_height_of__font_letter;

    hitbox_position =
        get_vector__3i32F4_using__i32(
                p_typer->cursor_position__3i32.x__i32
                + (p_font_letter->width_of__font_letter >> 1),
                p_typer->cursor_position__3i32.y__i32
                + (p_font_letter->height_of__font_letter >> 1),
                0);

    add_p_vectors__3i32F4(
            &hitbox_position, 
            &p_typer->text_bounding_box.position__3i32F4);

    hitbox_position.x__i32F4 -=
        i32_to__i32F4(p_typer->text_bounding_box.width__quantity_u32 >> 1);
    hitbox_position.y__i32F4 -=
        i32_to__i32F4(p_typer->text_bounding_box.height__quantity_u32 >> 1);

    font_letter_hitbox.position__3i32F4 =
        hitbox_position;

    return is_this_hitbox__fully_inside_this_hitbox__without_velocity(
                &font_letter_hitbox,
                &p_typer->text_bounding_box);
}

void put_c_string_in__typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Typer *p_typer,
        const char *c_string,
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
