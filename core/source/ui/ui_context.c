#include "ui/ui_context.h"
#include "rendering/gfx_context.h"
#include "rendering/graphics_window_manager.h"

void initialize_ui_context(UI_Context *p_ui_context) {
    memset(
            p_ui_context,
            0,
            sizeof(UI_Context));
}

void register_ui_window_into__ui_context(
        UI_Context *p_ui_context,
        UI_Window_Record *p_ui_window_record,
        Graphics_Window_Kind the_kind_of__window) {
    // TODO: validate args
    p_ui_context->ui_window_records[
        the_kind_of__window] = *p_ui_window_record;
}

Graphics_Window *open_ui(
        Gfx_Context *p_gfx_context,
        UI_Manager *p_ui_manager,
        Graphics_Window_Kind the_kind_of__window_to__open) {
    // TODO: validate args
    UI_Context *p_ui_context =
        get_p_ui_context_from__gfx_context(p_gfx_context);
    
    f_UI_Window__Load f_ui_window__load =
        p_ui_context->ui_window_records[
            the_kind_of__window_to__open].f_ui_window__load;

    if (!f_ui_window__load) {
        debug_warning("Did you forget to register the window?");
        debug_error("open_ui, f_ui_window__load == 0.");
        return false;
    }

    Graphics_Window *p_graphics_window =
        allocate_graphics_window_with__graphics_window_manager(
                p_gfx_context, 
                get_p_graphics_window_manager_from__gfx_context(
                    p_gfx_context),
                the_kind_of__window_to__open);

    if (!p_graphics_window) {
        debug_error("open_ui, p_PLATFORM_gfx_window == 0.");
        return false;
    }

    f_ui_window__load(
            p_gfx_context,
            p_graphics_window,
            p_ui_manager);

    return p_graphics_window;
}

void close_ui(
        Gfx_Context *p_gfx_context,
        UI_Manager *p_ui_manager,
        Graphics_Window_Kind the_kind_of__window_to__close) {
    debug_abort("close_ui, impl");
}
