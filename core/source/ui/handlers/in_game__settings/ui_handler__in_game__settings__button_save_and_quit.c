#include "ui/handlers/in_game__settings/ui_handler__in_game__settings__button_save_and_quit.h"
#include "game.h"
#include "scene/scene_manager.h"
#include "world/serialization/world_directory.h"

void m_ui_button__click_handler__save_and_quit(
        UI_Element *p_this_slider,
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    save_world(
            get_p_PLATFORM_file_system_context_from__game(p_game),
            get_p_world_from__game(p_game));
    quit_scene_state_machine(
            get_p_scene_manager_from__game(p_game));
}
