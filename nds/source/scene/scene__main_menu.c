#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "input/input.h"
#include "platform_defines.h"
#include "rendering/nds_gfx_context.h"
#include "scene/scene_manager.h"
#include "ui/nds_ui.h"
#include "ui/ui_button.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include <scene/scene__main_menu.h>
#include <debug/nds_debug.h>

void m_load_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_enter_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

enum Main_Menu_State {
    Main_Menu_State__Idle,
    Main_Menu_State__Singleplayer,
    Main_Menu_State__Multiplayer,
    Main_Menu_State__Settings
};

struct Main_Menu_Data_t {
    enum Main_Menu_State main_menu_state;
    enum Main_Menu_State button_state_configuration[3];
    Identifier__u16 scene_transition_identifier;
    PLATFORM_Gfx_Context *p_gfx_context;
    UI_Element *p_button_ptrs[4];
} main_menu_data;

void init_scene_as__main_menu(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__main_menu_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_as__main_menu_handler;
    p_scene->m_unload_scene_handler =
        m_unload_scene_as__main_menu_handler;

    p_scene->p_scene_data = &main_menu_data;
    main_menu_data.main_menu_state = Main_Menu_State__Idle;
    main_menu_data.button_state_configuration[0] = Main_Menu_State__Singleplayer;
    main_menu_data.button_state_configuration[1] = Main_Menu_State__Multiplayer;
    main_menu_data.button_state_configuration[2] = Main_Menu_State__Settings;
    main_menu_data.scene_transition_identifier = IDENTIFIER__UNKNOWN__u16;
}

void m_main_menu__play_button__clicked_handler(
    UI_Element *p_this_button,
    Game *p_game) {
    p_game->scene_manager.p_active_scene =
        get_scene_ptr_from__scene_manager(
                &p_game->scene_manager, 
                SCENE_IDENTIFIER__GAME);
}

void m_main_menu__menu_button__clicked_handler(
    UI_Element *p_this_button,
    Game *p_game) {
    enum Main_Menu_State button_associated_state =
        *((enum Main_Menu_State*)p_this_button->p_ui_data);
    switch(button_associated_state) {
        case Main_Menu_State__Idle:
            debug_info("idle");
            break;
        case Main_Menu_State__Singleplayer:
            debug_info("singleplayer");
            break;
        case Main_Menu_State__Multiplayer:
            debug_info("multiplayer");
            break;
        case Main_Menu_State__Settings:
            debug_info("settings");
            break;
    }
    if (main_menu_data.main_menu_state
            == button_associated_state) {
        main_menu_data.main_menu_state = Main_Menu_State__Idle;
    } else {
        main_menu_data.main_menu_state = 
            button_associated_state;
    }

    set_ui_element_as__disabled(main_menu_data.p_button_ptrs[3]);
    switch (main_menu_data.main_menu_state) {
        default:
            debug_info("idle");
            NDS_set_ui_to__menu_main(main_menu_data.p_gfx_context);
            break;
        case Main_Menu_State__Singleplayer:
            debug_info("singleplayer");
            NDS_set_ui_to__menu_single_player(main_menu_data.p_gfx_context);
            set_ui_element_as__enabled(main_menu_data.p_button_ptrs[3]);
            break;
        case Main_Menu_State__Multiplayer:
            debug_info("multiplayer");
            NDS_set_ui_to__menu_multiplayer(main_menu_data.p_gfx_context);
            break;
        case Main_Menu_State__Settings:
            debug_info("settings");
            NDS_set_ui_to__menu_settings(main_menu_data.p_gfx_context);
            break;
    }
}

void m_load_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_init_gfx_for__main_menu(
            &p_game->gfx_context);
    NDS_init_gfx_for__ui(
            &p_game->gfx_context);
    NDS_set_ui_to__menu_main(
            &p_game->gfx_context);

    release_all__ui_elements_from__ui_manager(
            &p_game->ui_manager);

    UI_Element **p_button_ptrs =
        main_menu_data.p_button_ptrs;

    get_many_new__ui_elements_from__ui_manager(
            &p_game->ui_manager, 
            p_button_ptrs, 4);

    for (Quantity__u8 i=0;i<3;i++) {
        init_ui_button(
                p_button_ptrs[i],
                80, 24);
        p_button_ptrs[i]->p_ui_data =
            &main_menu_data.button_state_configuration[i];
        main_menu_data.button_state_configuration[i] =
            (enum Main_Menu_State)(i+1);
        set_hitbox__position(
                &p_button_ptrs[i]->ui_bounding_box__aabb,
                52,  
                72 + 44 * i, 
                0);
        set_ui_element__clicked_handler(
                p_button_ptrs[i], m_main_menu__menu_button__clicked_handler);
    }

    init_ui_button(
            p_button_ptrs[3],
            104, 104);
    set_ui_element__clicked_handler(
            p_button_ptrs[3], m_main_menu__play_button__clicked_handler);
    set_ui_element_as__disabled(p_button_ptrs[3]);

    set_hitbox__position(
            &p_button_ptrs[3]->ui_bounding_box__aabb, 
            184, 
            118, 
            0);

    main_menu_data.p_gfx_context =
        &p_game->gfx_context;
}

void m_enter_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game) {
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
    }
}

void m_unload_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game) {
    debug_info("I am leaving main menu");
    p_game->scene_manager.p_active_scene =
        get_scene_ptr_from__scene_manager(
                &p_game->scene_manager, 
                SCENE_IDENTIFIER__GAME);
}
