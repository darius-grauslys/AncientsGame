#include "ui/implemented/ui_registrar__implemented.h"
#include "ui/implemented/ui_window__idle.h"
#include "ui/implemented/ui_window__equip.h"
#include "ui/implemented/ui_window__station.h"
#include "ui/implemented/ui_window__trade.h"
#include "ui/implemented/ui_window__in_game__settings.h"

void register_ui_windows(Gfx_Context *p_gfx_context) {
    register_ui_window__idle(p_gfx_context);
    register_ui_window__station(p_gfx_context);
    register_ui_window__trade(p_gfx_context);
    register_ui_window__equip(p_gfx_context);
    register_ui_window__in_game__settings(p_gfx_context);
}
