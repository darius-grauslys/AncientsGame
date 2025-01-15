#include "ui/ui_context.h"
#include "rendering/gfx_context.h"
#include "rendering/graphics_window_manager.h"

void initialize_ui_context(UI_Context *p_ui_context) {
    memset(
            p_ui_context,
            0,
            sizeof(UI_Context));
}

void register_ui_window__loader_into__ui_context(
        UI_Context *p_ui_context,
        f_UI_Window__Load f_ui_window__load,
        Graphics_Window_Kind the_kind_of__window) {
    // TODO: validate args
#warning validate args
    p_ui_context->F_ui_window__loaders[
        the_kind_of__window] = f_ui_window__load;
}

void register_ui_window__closer_into__ui_context(
        UI_Context *p_ui_context,
        f_UI_Window__Close f_ui_window__close,
        Graphics_Window_Kind the_kind_of__window) {
    // TODO: validate args
#warning validate args
    p_ui_context->F_ui_window__closers[
        the_kind_of__window] = f_ui_window__close;
}

Graphics_Window *open_ui(
        Gfx_Context *p_gfx_context,
        UI_Manager *p_ui_manager,
        World *p_world,
        Graphics_Window_Kind the_kind_of__window_to__open) {
    // TODO: validate args
#warning validate args
    UI_Context *p_ui_context =
        get_p_ui_context_from__gfx_context(p_gfx_context);
    
    f_UI_Window__Load f_ui_window__load =
        p_ui_context->F_ui_window__loaders[
            the_kind_of__window_to__open];

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
            p_world,
            p_ui_manager);

    return p_graphics_window;
}

void close_ui(
        Gfx_Context *p_gfx_context,
        UI_Manager *p_ui_manager,
        World *p_world,
        Graphics_Window_Kind the_kind_of__window_to__close) {
    // TODO: validate args
#warning validate args
    UI_Context *p_ui_context =
        get_p_ui_context_from__gfx_context(p_gfx_context);
    
    f_UI_Window__Close f_ui_window__close =
        p_ui_context->F_ui_window__closers[
            the_kind_of__window_to__close];

    if (!f_ui_window__close) {
        debug_warning("Did you forget to register the window?");
        debug_error("close_ui, f_ui_window__close == 0.");
        return;
    }

    Graphics_Window *p_graphics_window =
        allocate_graphics_window_with__graphics_window_manager(
                p_gfx_context, 
                get_p_graphics_window_manager_from__gfx_context(
                    p_gfx_context),
                the_kind_of__window_to__close);

    if (!p_graphics_window) {
        debug_error("close_ui, p_PLATFORM_gfx_window == 0.");
        return;
    }

    f_ui_window__close(
            p_gfx_context,
            p_graphics_window,
            p_world,
            p_ui_manager);
}
