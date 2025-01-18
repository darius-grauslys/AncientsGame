#include "ui/implemented/ui_registrar__implemented.h"
#include "defines.h"
#include "defines_weak.h"
#include "rendering/gfx_context.h"
#include "ui/handlers/ui_gfx_window__closer__default.h"
#include "ui/implemented/generated/game/ui_window__game__settings.h"
#include "ui/implemented/ui_gfx_window__load__equip.h"
#include "ui/implemented/ui_gfx_window__load__station.h"
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

    register_ui_window__loader_into__ui_context(
            p_ui_context,
            f_ui_window_load__equip, 
            UI_Window_Kind__Equip);
    register_ui_window__closer_into__ui_context(
            p_ui_context, 
            f_ui_window__close__default, 
            UI_Window_Kind__Equip);

    register_ui_window__loader_into__ui_context(
            p_ui_context,
            f_ui_window_load__station, 
            UI_Window_Kind__Station);
    register_ui_window__closer_into__ui_context(
            p_ui_context, 
            f_ui_window__close__default, 
            UI_Window_Kind__Station);

    register_ui_window__loader_into__ui_context(
            p_ui_context,
            allocate_ui_for__ui_window__game__settings, 
            UI_Window_Kind__Settings);
    register_ui_window__closer_into__ui_context(
            p_ui_context, 
            f_ui_window__close__default, 
            UI_Window_Kind__Settings);
}
