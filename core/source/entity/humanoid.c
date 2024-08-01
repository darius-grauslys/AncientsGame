#include "defines_weak.h"
#include "entity/handlers/body/body_handler__living.h"
#include "game.h"
#include "inventory/item.h"
#include "inventory/equipment.h"
#include "inventory/inventory_manager.h"
#include "rendering/animate_humanoid.h"
#include "timer.h"
#include <entity/humanoid.h>
#include <entity/entity.h>
#include <inventory/inventory.h>
#include <serialization/serialized_field.h>

void initialize_entity_as__humanoid(
        Game *p_game,
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4,
        Quantity__u32 width,
        Quantity__u32 height) {
    initialize_entity(
            p_entity, 
            kind_of_entity, 
            position__3i32F4, 
            width, 
            height);
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
                get_p_inventory_manager_from__game(p_game));
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
