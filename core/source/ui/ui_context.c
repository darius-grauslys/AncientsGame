#include "ui/ui_context.h"
#include "rendering/gfx_context.h"

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

bool open_ui(
        Gfx_Context *p_gfx_context,
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

    return f_ui_window__load(
            p_gfx_context,
            the_kind_of__window_to__open);
}

void close_ui(
        Gfx_Context *p_gfx_context,
        Graphics_Window_Kind the_kind_of__window_to__close) {
    debug_abort("close_ui, impl");
}
