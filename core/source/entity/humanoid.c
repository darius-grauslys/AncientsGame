#include "defines_weak.h"
#include "entity/handlers/body/body_handler__living.h"
#include "entity/handlers/serialization/serialization_handler__humanoid__default.h"
#include "game.h"
#include "inventory/item.h"
#include "inventory/implemented/tool.h"
#include "inventory/equipment.h"
#include "inventory/inventory_manager.h"
#include "rendering/animate_humanoid.h"
#include "timer.h"
#include <entity/humanoid.h>
#include <entity/entity.h>
#include <inventory/inventory.h>
#include <serialization/serialized_field.h>
#include <inventory/item_stack.h>

void initialize_entity_as__humanoid(
        Gfx_Context *p_gfx_context,
        Graphics_Window 
            *p_gfx_window,
        World *p_world,
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4,
        Quantity__u32 width,
        Quantity__u32 height) {
    initialize_entity_with__sprite(
            p_gfx_context,
            p_gfx_window,
            p_entity, 
            kind_of_entity, 
            position__3i32F4, 
            width, 
            height);
    p_entity->_serializer.m_serialize_handler =
        m_serialize_handler__humanoid__default;
    p_entity->_serializer.m_deserialize_handler =
        m_deserialize_handler__humanoid__default;
    set_entity__game_action_handler(
            p_entity, 
            m_humanoid_handler__game_action_handler);
    
    initialize_equipment(
            &p_entity->equipment);
    set_entity__armor(
            p_entity, 
            Entity_Armor_Kind__None, 
            Entity_Armor_Modification_Kind__None);
    Inventory *p_inventory =
        allocate_p_inventory_in__inventory_manager(
                get_p_inventory_manager_from__world(p_world));
    if (p_inventory) {
        point_serialized_field_to__this_serialized_struct(
                &p_entity->s_humanoid__inventory_ptr, 
                p_inventory);
    }
}

void humanoid__use(
        Game *p_game,
        Entity *p_humanoid) {
    // TODO: make this a bit better:
    // TODO: make this as a game action.
    if (p_humanoid->sprite_wrapper.the_kind_of_animation__this_sprite_has
            == Sprite_Animation_Kind__Humanoid__Use)
        return;
    Item *p_item =
        &p_humanoid->equipment.item_stack__main_hand.item;
    if (!does_item_have__use_handler(p_item)) {
        return;
    }

    animate_humanoid__use(p_humanoid);
    p_item->m_item_use_handler(
            p_item,
            p_humanoid,
            0,
            p_game);
}

void humanoid__tool_mode(
        Game *p_game,
        Entity *p_humanoid) {
    // TODO: make this as a game action.
    Item *p_item =
        &p_humanoid->equipment.item_stack__main_hand.item;
    switch (p_item->item_tool_mode) {
        default:
            set_item_tool_mode_to__next_tool_mode(
                    p_item);
            break;
        case Tool_Mode__Combat_Lockon:
            // TODO: impl lockon
            set_item_tool_mode(
                    p_item, 
                    Tool_Mode__Labor);
            break;
    }
}

bool is_entity_a__humanoid(Entity *entity) {
    switch (entity->the_kind_of_entity__this_entity_is) {
        default:
            return false;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            return true;
    }
}

Inventory *resolve_p_inventory_of__humanoid(
        Game *p_game,
        Entity *p_humanoid) {
    if (resolve_s_inventory_ptr_to__inventory_manager(
                get_p_inventory_manager_from__game(p_game), 
                &p_humanoid->s_humanoid__inventory_ptr)) {
        return 
            p_humanoid
            ->s_humanoid__inventory_ptr
            .p_serialized_field__inventory
            ;
    }
    // fail, try to alloc one.
    Inventory *p_inventory =
        allocate_p_inventory_in__inventory_manager(
                get_p_inventory_manager_from__game(p_game));

    if (!p_inventory) {
        debug_warning("resolve_p_inventory_of__humanoid, failed to allocate inventory.");
        return 0;
    }

    initialize_serialized_field(
            &p_humanoid
            ->s_humanoid__inventory_ptr, 
            p_inventory, 
            p_inventory->_serialization_header.uuid);

    return p_inventory;
}

bool is_humanoid__dead(Entity *p_humanoid) {
    return p_humanoid->hearts.resource_symbols[0] 
        == Heart_Kind__Empty;
}

void humanoid__poll_player_update_inventory(
        Game *p_game,
        Entity_Kind the_kind_of__entity) {
    switch (the_kind_of__entity) {
        default:
            break;
        case Entity_Kind__Player:
            // TODO: dispatch to player via game_action
#warning TODO: impl
            // PLATFORM_refresh_ui(
            //         p_game, 
            //         UI_Window_Kind__Equip);
            // PLATFORM_refresh_ui(
            //         p_game, 
            //         UI_Window_Kind__Trade);
            // PLATFORM_refresh_ui(
            //         p_game, 
            //         UI_Window_Kind__Station);
            break;
    }
}

void humanoid__add_item_to__inventory(
        Game *p_game,
        Entity *p_entity,
        Item item,
        Quantity__u32 quantity_of__items,
        Quantity__u32 max_quantity_of__items) {
    Inventory *p_inventory =
        resolve_s_inventory(
                p_game,
                &p_entity->s_humanoid__inventory_ptr);

    if (!p_inventory)
        return;

    add_item_to__inventory(
            p_inventory, 
            item, 
            quantity_of__items, 
            max_quantity_of__items);

    humanoid__poll_player_update_inventory(
            p_game, 
            get_entity_kind_of__entity(p_entity));
}

void humanoid__remove_quantity_of__item_kinds_from__inventory(
        Game *p_game,
        Entity *p_entity,
        Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items) {
    Inventory *p_inventory =
        resolve_s_inventory(
                p_game,
                &p_entity->s_humanoid__inventory_ptr);

    if (!p_inventory)
        return;

    remove_this_many_item_kinds_from__inventory(
            p_inventory, 
            the_kind_of__item, 
            quantity_of__items);

    humanoid__poll_player_update_inventory(
            p_game, 
            get_entity_kind_of__entity(p_entity));
}

void humanoid__remove_quantity_of__item_kinds_from__posessions(
        Game *p_game,
        Entity *p_entity,
        Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items) {
    Quantity__u32 quantity_of__items_remaining_to__remove =
        remove_quantity_of_items_from__item_stack(
                get_p_item_stack__off_hand_slot_from__equipment(
                    &p_entity->equipment), 
                quantity_of__items);
    if (quantity_of__items_remaining_to__remove == 0) {
        humanoid__poll_player_update_inventory(
                p_game, 
                get_entity_kind_of__entity(p_entity));
        return;
    }

    humanoid__remove_quantity_of__item_kinds_from__inventory(
            p_game,
            p_entity,
            the_kind_of__item,
            quantity_of__items_remaining_to__remove);
}
