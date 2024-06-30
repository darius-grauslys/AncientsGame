#include "defines.h"
#include "defines_weak.h"
#include "nds/arm9/sprite.h"
#include "nds_defines.h"
#include "platform.h"
#include "rendering/nds_background.h"
#include "rendering/nds_background_allocation_specification.h"
#include "rendering/nds_background_engine_allocation_context.h"
#include "ui/game/nds_ui_background__game__hud.h"
#include "ui/game/nds_ui_window__game__equip.h"
#include "ui/game/nds_ui_window__game__idle.h"
#include "ui/game/nds_ui_window__game__labor.h"
#include "ui/game/nds_ui_window__game__trade.h"
#include "ui/game/nds_ui_window__game__typer.h"
#include "ui/menu/nds_ui_window__menu__main.h"
#include "ui/menu/nds_ui_window__menu__multiplayer.h"
#include "ui/menu/nds_ui_window__menu__settings.h"
#include "ui/menu/nds_ui_window__menu__singleplayer.h"
#include "ui/ui_button.h"
#include "ui/ui_element.h"
#include "vectors.h"
#include <nds.h>
#include <ui/nds_ui.h>
#include <assets/ui/default/ui_tileset_default.h>
#include <ui/ui_manager.h>
#include <game.h>

struct NDS_UI__State_Machine_t {
    enum UI_Window_Kind the_kind_of__active_ui_window;
} _ui__state_machine;

void NDS_set_ui_to__debug(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_tileset_defaultMap, 
            p_gfx_context->backgrounds__sub[0]
            .gfx_map,
            ui_tileset_defaultMapLen);
	dmaCopy(ui_tileset_defaultMap, 
            p_gfx_context->backgrounds__sub[1]
            .gfx_map,
            ui_tileset_defaultMapLen);
}

void NDS_set_ui_element_size_using__sprite_size(
        UI_Element *p_ui_element,
        SpriteSize sprite_size) {
    switch (sprite_size) {
        default:
            break;
        case SpriteSize_8x8:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                8;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                8;
            break;
        case SpriteSize_8x16:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                8;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                16;
            break;
        case SpriteSize_8x32:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                8;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                32;
            break;
        case SpriteSize_16x8:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                16;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                8;
            break;
        case SpriteSize_16x16:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                16;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                16;
            break;
        case SpriteSize_16x32:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                16;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                32;
            break;
        case SpriteSize_32x8:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                32;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                8;
            break;
        case SpriteSize_32x16:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                32;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                16;
            break;
        case SpriteSize_32x32:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                32;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                32;
            break;
        case SpriteSize_32x64:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                32;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                64;
            break;
        case SpriteSize_64x32:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                64;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                32;
            break;
        case SpriteSize_64x64:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                64;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                64;
            break;
    }
}

void PLATFORM_open_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__open) {
    if (the_kind_of__ui_window_to__open
            == _ui__state_machine.the_kind_of__active_ui_window)
        return;
    _ui__state_machine.the_kind_of__active_ui_window =
        the_kind_of__ui_window_to__open;
    release_all__ui_elements_from__ui_manager(
            get_p_ui_manager_from__game(p_game),
            p_game);
    switch (the_kind_of__ui_window_to__open) {
        default:
            debug_error("NDS, PLATFORM_open_ui, unsupported UI_Window_Kind.");
            break;
        case UI_Window_Kind__Idle:
            NDS_allocate_ui_for__nds_ui_window__game__idle(p_game);
            break;
        case UI_Window_Kind__Equip:
            NDS_allocate_ui_for__nds_ui_window__game__equip(p_game);
            break;
        case UI_Window_Kind__Trade:
            NDS_allocate_ui_for__nds_ui_window__game__trade(p_game);
            break;
        case UI_Window_Kind__Labor:
            NDS_allocate_ui_for__nds_ui_window__game__labor(p_game);
            break;
        case UI_Window_Kind__Typer:
            NDS_allocate_ui_for__nds_ui_window__game__typer(p_game);
            break;
        case UI_Window_Kind__Main_Menu:
            NDS_allocate_ui_for__nds_ui_window__menu__main(p_game);
            break;
        case UI_Window_Kind__Multiplayer:
            NDS_allocate_ui_for__nds_ui_window__menu__multiplayer(p_game);
            break;
        case UI_Window_Kind__Settings:
            NDS_allocate_ui_for__nds_ui_window__menu__settings(p_game);
            break;
        case UI_Window_Kind__Singleplayer:
            NDS_allocate_ui_for__nds_ui_window__menu__singleplayer(p_game);
            break;
    }

    NDS_set_background_for__ui_window(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            the_kind_of__ui_window_to__open);
}

void PLATFORM_close_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__close) {
    if (the_kind_of__ui_window_to__close
            == UI_Window_Kind__Idle)
        return;
    PLATFORM_open_ui(
            p_game, 
            UI_Window_Kind__Idle);
}

void m_ui_button__clicked_handler__navigate_to__equip(
        UI_Element *p_this_button,
        Game *p_game) {
    enum UI_Window_Kind kind_of_ui_window__currently_open =
        PLATFORM_get_last_opened_ui();
    if (UI_Window_Kind__Equip
            == kind_of_ui_window__currently_open) {
        PLATFORM_open_ui(
                p_game, 
                UI_Window_Kind__Idle);
        return;
    }
    PLATFORM_open_ui(
            p_game, 
            UI_Window_Kind__Equip);
}

void m_ui_button__clicked_handler__navigate_to__trade(
        UI_Element *p_this_button,
        Game *p_game) {
    enum UI_Window_Kind kind_of_ui_window__currently_open =
        PLATFORM_get_last_opened_ui();
    if (UI_Window_Kind__Trade
            == kind_of_ui_window__currently_open) {
        PLATFORM_open_ui(
                p_game, 
                UI_Window_Kind__Idle);
        return;
    }
    PLATFORM_open_ui(
            p_game, 
            UI_Window_Kind__Trade);
}

void m_ui_button__clicked_handler__navigate_to__labor(
        UI_Element *p_this_button,
        Game *p_game) {
    enum UI_Window_Kind kind_of_ui_window__currently_open =
        PLATFORM_get_last_opened_ui();
    if (UI_Window_Kind__Labor
            == kind_of_ui_window__currently_open) {
        PLATFORM_open_ui(
                p_game, 
                UI_Window_Kind__Idle);
        return;
    }
    PLATFORM_open_ui(
            p_game, 
            UI_Window_Kind__Labor);
}

UI_Element *NDS_allocate_ui_for__game_hud(
        Game *p_game) {
    UI_Element *p_buttons = 
        allocate_many_ui_elements_from__ui_manager_in__succession(
                get_p_ui_manager_from__game(p_game),
                3);
    UI_Element *p_current = p_buttons;
    for (Index__u8 index_of__next_itteration = 0;
            itterate_to_next__ui_element(&p_current);
            index_of__next_itteration++) {
        m_UI_Clicked m_ui_clicked_handler;
        switch (index_of__next_itteration) {
            default:
            case 0:
                m_ui_clicked_handler =
                    m_ui_button__clicked_handler__navigate_to__equip;
                break;
            case 1:
                m_ui_clicked_handler =
                    m_ui_button__clicked_handler__navigate_to__trade;
                break;
            case 2:
                m_ui_clicked_handler =
                    m_ui_button__clicked_handler__navigate_to__labor;
                break;
        }
        initialize_ui_element_as__button(
                p_current, 
                104, 32,
                get_vector__3i32(56 + 72 
                    * index_of__next_itteration, 52, 0),
                m_ui_clicked_handler
                );
    }
}

enum UI_Window_Kind PLATFORM_get_last_opened_ui(void) {
    return _ui__state_machine.the_kind_of__active_ui_window;
}

Quantity__u8 PLATFORM_get_all_opened_ui(
        enum UI_Window_Kind *p_ui_window_kind__buffer,
        Quantity__u8 size_of__buffer) {
    if (size_of__buffer == 0) return 0;
    p_ui_window_kind__buffer[0] = 
        _ui__state_machine.the_kind_of__active_ui_window;
    return 1;
}

void NDS_set_background_for__ui_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum UI_Window_Kind the_kind_of__ui_window) {
    NDS_Background_Engine_Allocation_Context
        nds_background_engine_allocation_context;
    NDS_initialize_background_engine_allocation_context(
            &nds_background_engine_allocation_context, 
            the_kind_of__ui_window);

#warning impl extended background palletes
    //TODO: need to add extended background palletes
    dmaCopy(nds_background_engine_allocation_context
                .pal_background,
            BG_PALETTE_SUB, 
            nds_background_engine_allocation_context
                .length_of__background_pal);

    for (Index__u8 index=0;
            index < NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
            index++) {
        NDS_Background_Allocation_Specification 
            *p_background_allocation_specification =
            &nds_background_engine_allocation_context
                .nds_background_allocation_specifications[index];

        NDS_Background *p_background =
                &p_PLATFORM_gfx_context->backgrounds__sub[
                    p_background_allocation_specification
                        ->background_slot];

        NDS_initialize_background_with__allocation_specification(
                p_background,
                p_background_allocation_specification);

        if (UI_Window_Kind__None
                == p_background_allocation_specification
                ->the_kind_of__ui_background_allocation) {
            bgHide(p_background->background_index_from__hardware);
            continue;
        }
        bgShow(p_background->background_index_from__hardware);

        dmaCopy(p_background_allocation_specification
                    ->p_gfx_background, 
                p_background
                ->gfx_tileset, 
                p_background_allocation_specification
                    ->length_of__p_background_gfx);
        dmaCopy(p_background_allocation_specification
                    ->p_map_background,
                p_background
                ->gfx_map, 
                p_background_allocation_specification
                    ->length_of__p_background_map);
        NDS_set_background_priority(
                p_background,
                p_background_allocation_specification
                    ->priority_of__background);

        if (p_background_allocation_specification
                ->background_slot == NDS_BACKGROUND_SLOT__UI__BASE) {
            NDS_put_hud_onto__background(
                    p_PLATFORM_gfx_context, 
                    &p_PLATFORM_gfx_context->backgrounds__sub[
                        p_background_allocation_specification
                            ->background_slot]);
        }
    }
}
