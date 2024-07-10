#include <defines.h>
#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines_weak.h"
#include "game.h"
#include "input/input.h"
#include "nds/arm9/background.h"
#include "nds/arm9/video.h"
#include "nds_defines.h"
#include "platform.h"
#include "platform_defines.h"
#include "process/process.h"
#include "process/process_manager.h"
#include "rendering/font/message.h"
#include "rendering/font/typer.h"
#include "rendering/nds_background.h"
#include "rendering/sprite.h"
#include "ui/nds_ui.h"
#include "ui/nds_ui__slider.h"
#include "ui/ui_manager.h"
#include "vectors.h"
#include "world/world.h"
#include <scene/nds_scene__test.h>
#include <debug/nds_debug.h>
#include <scene/scene.h>
#include <ui/nds_ui__draggable.h>
#include <rendering/gfx_context.h>
#include <numerics.h>

enum Item_Kind item_kind = Item_Kind__Stick;

PLATFORM_Sprite *p_item_sprite;

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_set_vram_for__backgrounds_on__sub();
    NDS_set_vram_and__oam_for__sprites_on__sub();
    NDS_load_sprite_palletes__default_into__vram();
    NDS_initialize_debug__main();

    Sprite_Allocation_Specification
        sprite_allocation_specification;

    initialize_sprite_allocation_specification_for__item(
            &sprite_allocation_specification, 
            TEXTURE_FLAGS__NONE, 
            get_p_ui_manager_from__game(p_game)
                ->p_PLATFORM_graphics_window_for__ui_manager, 
            Item_Kind__Stick);

    p_item_sprite = PLATFORM_allocate_sprite(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            &sprite_allocation_specification);

    PLATFORM_set_sprite__position(
            p_item_sprite, 40, 40);

    PLATFORM_open_ui(
            p_game,
            UI_Window_Kind__Idle);

    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);
    NDS_Background *p_NDS_background_typer =
        &p_PLATFORM_gfx_context->backgrounds__sub[
        NDS_BACKGROUND_SLOT__UI__TYPER];

    Typer *p_typer =
        &p_PLATFORM_gfx_context->typers[1];
    initialize_typer_with__font(
            p_typer, 
            108, 92, 
            160, 24, 
            0, 0, 
            p_typer->p_font);

    NDS_setup_typer_onto__background(
            p_NDS_background_typer, 
            p_typer);

    debug_info("game: %d", sizeof(Game));
    debug_info("process_manager: %d", sizeof(Process_Manager));
    debug_info("sort_list_manager: %d", sizeof(Sort_List_Manager));
    debug_info("path_list_manager: %d", sizeof(Path_List_Manager));
    debug_info("path: %d", sizeof(Path));
    debug_info("entity: %d", sizeof(Entity));
    debug_info("ray: %d", sizeof(Ray__3i32F8));
    debug_info("inv: %d", sizeof(Inventory));

    put_c_string_in__typer(
            p_PLATFORM_gfx_context, 
            p_typer, 
            //"abcd", 4);
            "The quick brown fox jumped over the lazy dog again and again and again and again!", MESSAGE_MAX_LENGTH_OF);
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {
    enum UI_Window_Kind ui_window_kind = UI_Window_Kind__None;
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
        if (is_input__use_released(get_p_input_from__game(p_game))) {
            item_kind++;
            ui_window_kind++;
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            debug_info("ui_window_kind: %d", ui_window_kind);
        }
        if (is_input__use_secondary_released(get_p_input_from__game(p_game))) {
            item_kind--;
            ui_window_kind--;
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            debug_info("ui_window_kind: %d", ui_window_kind);
        }
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
