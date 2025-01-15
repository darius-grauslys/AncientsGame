#include "ui/implemented/ui_registrar__implemented.h"
#include "defines.h"
#include "rendering/gfx_context.h"
#include "ui/handlers/ui_gfx_window__closer__default.h"
#include "ui/implemented/ui_gfx_window__load__trade.h"
#include "ui/ui_context.h"

void register_ui_windows(Gfx_Context *p_gfx_context) {
    UI_Context *p_ui_context =
        get_p_ui_context_from__gfx_context(p_gfx_context);
    register_ui_window__loader_into__ui_context(
            p_ui_context,
            f_ui_window_load__trade, 
            UI_Window_Kind__Trade);
    register_ui_window__closer_into__ui_context(
            p_ui_context, 
            f_ui_window__close__default, 
            UI_Window_Kind__Trade);
}
