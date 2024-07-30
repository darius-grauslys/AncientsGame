#include "ui/nds_ui__typer.h"
#include "log/log.h"
#include "nds_defines.h"
#include "rendering/font/typer.h"
#include "rendering/nds_background.h"
#include "vectors.h"

void NDS_initialize_typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    NDS_Background *p_NDS_background_typer =
        &p_PLATFORM_gfx_context->backgrounds__sub[
        NDS_BACKGROUND_SLOT__UI__TYPER];

    Typer *p_typer =
        &p_PLATFORM_gfx_context->typers[0];
    initialize_typer_with__font(
            p_typer, 
            108, 92, 
            160, 24, 
            0, 0, 
            p_typer->p_font);

    NDS_setup_typer_onto__background(
            p_NDS_background_typer, 
            p_typer);
}

void NDS_update_typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Log *p_log) {
    Typer *p_typer =
        &p_PLATFORM_gfx_context->typers[0];
    p_typer->cursor_position__3i32 =
        get_vector__3i32(
                108, 
                92, 
                0);
    Message *p_message =
        get_next_p_message_in__log(p_log);
    put_c_string_in__typer(
            p_PLATFORM_gfx_context, 
            p_typer, 
            (const char*)p_message->message__body, 
            p_message->length_of__message__body);
}

void NDS_clear_typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    // TODO:    impl
    //          might be easiest to just reset background.
}
