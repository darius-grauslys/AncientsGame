#include "defines.h"
#include "defines_weak.h"
#include "entity/entity_manager.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "inventory/item_recipe_manager.h"
#include "inventory/item_stack.h"
#include "inventory/station_inventory_map.h"
#include "rendering/nds_graphics_window.h"
#include "serialization/serialized_field.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include "world/tiles/tile__cover__table.h"
#include "world/world.h"
#include <ui/handlers/inventory/nds_ui_handler__button_craft.h>

void m_NDS_ui_button__click_handler__craft(
        UI_Element *p_this_slider,
        Game *p_game) {
    Game_Action *p_game_action_for__station =
        NDS_get_p_copy_of__associated_game_action_of__sub_graphics_window(
                p_game);

    if (!p_game_action_for__station)
        return;

    Serialized_Field s_station_inventory;

    initialize_serialized_field_as__unlinked(
            &s_station_inventory, 
            get_uuid_for__container(
                    p_game_action_for__station
                    ->game_action__container__tile_vector_3i32)
            );

    Inventory *p_inventory_of__station =
        resolve_s_inventory(
                p_game,
                &s_station_inventory);

    if (!p_inventory_of__station) {
        debug_error("NDS::m_NDS_ui_button__click_handler__craft, failed to get station inventory.");
        return;
    }

    if (!resolve_p_serialized_entity_ptr_with__entity_manager(
            get_p_entity_manager_from__game(p_game), 
            &p_game_action_for__station
            ->s_game_action__inventory__entity_source)) {
        debug_error("NDS::m_NDS_ui_button__click_handler__craft, failed to get entity using station.");
        return;
    }

    Entity *p_entity =
        p_game_action_for__station
        ->s_game_action__inventory__entity_source
        .p_serialized_field__entity
        ;

    Inventory *p_inventory_of__entity =
        resolve_s_inventory(
                p_game,
                &p_entity
                ->s_humanoid__inventory_ptr);

    Station_Inventory_Map station_inventory_map;
    map_station_inventory(
            p_inventory_of__station, 
            &station_inventory_map);

    if (is_p_item_stack__empty(
                station_inventory_map
                .p_item_stack__recipe)) {
        return;
    }

    Item_Kind the_kind_of__item_to__craft =
        station_inventory_map
        .p_item_stack__recipe
        ->item
        .the_kind_of_item__this_recipe_produces;

    Item_Recipe_Flags item_recipe_flags =
        station_inventory_map
        .p_item_stack__recipe
        ->item
        .item_recipe_flags;

    bool is_crafting__successful =
        make_item_with__this_inventory(
                get_p_item_recipe_manager_from__game(p_game), 
                p_inventory_of__entity, 
                the_kind_of__item_to__craft, 
                item_recipe_flags);

    if (!is_crafting__successful) {
        return;
    }

    add_item_to__inventory(
            p_inventory_of__entity, 
            get_item_from__item_manager(
                get_p_item_manager_from__game(p_game), 
                the_kind_of__item_to__craft), 
            1, 
            1); // TODO: determine max item stack count by item.
}
