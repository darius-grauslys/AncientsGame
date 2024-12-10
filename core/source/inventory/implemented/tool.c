#include "defines_weak.h"
#include "entity/entity.h"
#include "entity/humanoid.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
#include "world/tile_logic_manager.h"
#include "world/tile_logic_record.h"
#include "world/world.h"
#include <inventory/implemented/tool.h>
#include <defines.h>
#include <game_util.h>

void initialize_item_as__tool(
        Item *p_item__weapon,
        enum Item_Kind the_kind_of__item,
        Item_Usage_Flags item_usage_flags,
        i32F20 weight_of_each__item,
        Tool_Kind the_kind_of__tool,
        m_Item_Use m_item_use_handler,
        m_Item_Equip_Event m_item_equip_handler,
        m_Item_Equip_Event m_item_unequip_handler) {
    initialize_item(
            p_item__weapon,
            the_kind_of__item,
            item_usage_flags,
            ITEM_FILTER_FLAG__INTERACTABLE,
            weight_of_each__item,
            m_item_use_handler,
            m_item_equip_handler, 
            m_item_unequip_handler);
    p_item__weapon->the_kind_of__tool =
        the_kind_of__tool;
}

void set_item_tool_mode_to__next_tool_mode(
        Item *p_item) {
    if (p_item->item_usage_flags
            == ITEM_USAGE_FLAGS__NONE) {
        return;
    }

    switch (p_item->item_tool_mode) {
        default:
            p_item->item_tool_mode =
                Tool_Mode__None;
            break;
        case Tool_Mode__Labor:
            if (set_item_tool_mode(
                        p_item, 
                        Tool_Mode__Labor_Secondary)) {
                break;
            }
        case Tool_Mode__Labor_Secondary:
            if (set_item_tool_mode(
                        p_item, 
                        Tool_Mode__Combat)) {
                break;
            }
        case Tool_Mode__Combat:
        case Tool_Mode__Combat_Lockon:
            if (set_item_tool_mode(
                        p_item, 
                        Tool_Mode__Labor)) {
                break;
            }
    }
}

bool set_item_tool_mode(
        Item *p_item,
        Tool_Mode tool_mode) {
    if (tool_mode < Tool_Mode__None
            || tool_mode >= Tool_Mode__Unknown) {
        return false;
    }
    switch (tool_mode) {
        default:
        case Tool_Mode__None:
            if (p_item->item_usage_flags
                    == ITEM_USAGE_FLAGS__NONE) {
                break;
            }
            return false;
        case Tool_Mode__Labor:
            if (is_item_usable_for__labor(p_item)) {
                break;
            }
            return false;
        case Tool_Mode__Labor_Secondary:
            if (is_item_possessing__secondary_labor(p_item)) {
                break;
            }
            return false;
        case Tool_Mode__Combat:
            if (is_item_usable_for__combat(p_item)) {
                break;
            }
            return false;
        case Tool_Mode__Combat_Lockon:
            if (is_item_usable_for__combat(p_item)) {
                break;
            }
            return false;
    }
    p_item->item_tool_mode =
        tool_mode;
    // TODO: remove, this is here out of a lack of UI
    switch (tool_mode) {
        default:
            debug_info("TOOL MODE: Unknown");
            break;
        case Tool_Mode__Labor:
            debug_info("TOOL MODE: Labor");
            break;
        case Tool_Mode__Labor_Secondary:
            debug_info("TOOL MODE: Labor Secondary");
            break;
        case Tool_Mode__Combat:
            debug_info("TOOL MODE: Combat");
            break;
        case Tool_Mode__Combat_Lockon:
            debug_info("TOOL MODE: Combat Lockon");
            break;
    }
    return true;
}

void m_item_use_handler__harvest(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game) {
    Tile_Vector__3i32 tile_vector__3i32 =
        get_tile_vector_thats__infront_of_this__entity(
                p_entity_user);
    Tile *p_tile =
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__game(p_game),
                tile_vector__3i32);

    Tile_Logic_Record *p_tile_logic_record;
    if (is_item_tool_mode__labor_secondary(p_item_self)) {
        p_tile_logic_record =
            get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                    get_p_tile_logic_manager_from__world(
                        get_p_world_from__game(
                            p_game)), 
                    get_tile_kind_from__tile(p_tile));
    } else if (is_item_tool_mode__labor(p_item_self)) {
        p_tile_logic_record =
            get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
                    get_p_tile_logic_manager_from__world(
                        get_p_world_from__game(
                            p_game)), 
                    get_tile_cover_kind_from__tile(p_tile));
    } else {
        return;
    }

    Tool_Kind the_kind_of__tool =
        get_tool_kind_of__tool(
                p_item_self);

    if (!is_tile_logic_record__harvestable_for__this_kind_of__tool(
                p_tile_logic_record,
                the_kind_of__tool)) {
        return;
    }

    Item resource = get_item_from__item_manager(
            get_p_item_manager_from__game(p_game), 
            get_tile_logic_record__resource_kind(
                p_tile_logic_record));
    Quantity__u32 quantity_of__items =
        get_tile_logic_record__quantity_of__resource(
                p_tile_logic_record);
    if (is_item_tool_mode__labor_secondary(p_item_self)) {
        if (!remove_tile__ground(
                p_game,
                tile_vector__3i32)) {
            return;
        }
    } else {
        if (!remove_tile__cover(
                p_game,
                tile_vector__3i32)) {
            return;
        }
    }
    humanoid__add_item_to__inventory(
            p_game, 
            p_entity_user, 
            resource, 
            quantity_of__items, 
            128); //TODO: magic number, item max
    update_chunk_at__tile_vector__3i32(
            p_game, 
            tile_vector__3i32);
}
