#include "ui/handlers/ui_gfx_window__closer__default.h"
#include "ui/ui_manager.h"

bool f_ui_window__close__default(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        UI_Manager *p_ui_manager) {
    release_all__ui_elements_from__ui_manager(
            p_ui_manager, 
            p_gfx_context,
            p_gfx_window,
            p_world);
    return true;
}
