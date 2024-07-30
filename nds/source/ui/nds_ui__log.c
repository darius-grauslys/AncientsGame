#include "ui/nds_ui__log.h"
#include "log/log.h"
#include "nds/arm9/background.h"
#include "nds_defines.h"
#include "rendering/font/typer.h"
#include "rendering/nds_background.h"

void NDS_initialize_log(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    NDS_Background *p_NDS_background_typer =
        &p_PLATFORM_gfx_context->backgrounds__sub[
        NDS_BACKGROUND_SLOT__UI__LOG_UPPER];

    Typer *p_typer =
        &p_PLATFORM_gfx_context->typers[0];
    initialize_typer_with__font(
            p_typer, 
            15 << 3, 256, 
            14 << 3, 512,
            0, 0,
            p_typer->p_font);

    // TODO: check for failure
    NDS_setup_typer_onto__background(
            p_NDS_background_typer, 
            p_typer);
}

void NDS_update_log(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Log *p_log) {
    Typer *p_typer =
        &p_PLATFORM_gfx_context->typers[0];
    Message *p_message =
        get_next_p_message_in__log(p_log);
    put_c_string_in__typer(
            p_PLATFORM_gfx_context, 
            p_typer, 
            (const char*)p_message->message__body, 
            p_message->length_of__message__body);
}

void NDS_clear_log(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    //TODO: impl
    //      it may be easiest to just
    //      reset the entire background.
}
