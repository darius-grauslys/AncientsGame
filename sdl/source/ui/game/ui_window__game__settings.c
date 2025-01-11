#include <ui/game/sdl_ui_window__game__settings.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
#include <ui/handlers/in_game__settings/ui_handler__in_game__settings__button_save_and_quit.h>
// THIS CODE IS AUTO GENERATED. Go to ./sdl/assets/ui/xml/ instead of modifying this file.

UI_Element *SDL_allocate_ui_for__sdl_ui_window__game__settings(Game *p_game, PLATFORM_Graphics_Window *p_PLATFORM_gfx_window, UI_Manager *p_ui_manager){
    UI_Element *p_ui_iterator = 0;
    UI_Element *p_ui_iterator_previous_previous = 0;
    UI_Element *p_ui_iterator_previous = 0;
    UI_Element *p_ui_iterator_child = 0;
SDL_allocate_ui_for__sdl_ui_window__game__hud(p_game, p_PLATFORM_gfx_window, p_ui_manager);
    toggle_ui_button(get_p_ui_element_by__index_from__ui_manager(p_ui_manager, 0));
    UI_Element *p_button_setting__resume = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_setting__resume, 104, 32, get_vector__3i32(128 + 0, 28 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_button_setting__save = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_setting__save, 104, 32, get_vector__3i32(128 + 0, 72 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_button_setting__main_menu = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_setting__main_menu, 104, 32, get_vector__3i32(128 + 0, 116 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_button_setting__save_and_quit = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_setting__save_and_quit, 104, 32, get_vector__3i32(128 + 0, 160 + 0, 0), m_ui_button__click_handler__save_and_quit, false, false);

}
