#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "defines_weak.h"
#include <defines.h>

void initialize_equipment(
        Equipment *p_equipment);

static inline
Item_Stack *get_p_item_stack__main_hand_slot_from__equipment(
        Equipment *p_equipment) {
    return &p_equipment->item_stack__main_hand;
}

static inline
Item_Stack *get_p_item_stack__off_hand_slot_from__equipment(
        Equipment *p_equipment) {
    return &p_equipment->item_stack__off_hand;
}

static inline
Item_Stack *get_p_item_stack__armor_slot_from__equipment(
        Equipment *p_equipment) {
    return &p_equipment->item_stack__armor;
}

static inline
Item_Stack *get_p_item_stack__consumable_slot_from__equipment(
        Equipment *p_equipment,
        Index__u8 index_of__consumable) {
#ifndef NDEBUG
    if (INVENTORY_CONSUMABLES_QUANTITY_OF
            <= index_of__consumable) {
        debug_error("get_p_item_stack__consumables_slot_from__equipment, index out of bounds: %d", index_of__consumable);
        return 0;
    }
#endif
    return &p_equipment->item_stack__consumables
        [index_of__consumable];
}

static inline
Item_Stack *get_p_item_stack_by__index_in__equipment(
        Equipment *p_equipment,
        Index__u32 index_of__equipment) {
#ifndef NDEBUG
    if (EQUIPMENT_ITEM_STACK_QUANTITY_OF
            <= index_of__equipment) {
        debug_error("get_p_item_stack_by__uuid_in__equipment, uuid out of bounds: %d", index_of__equipment);
        return 0;
    }
#endif
    return &p_equipment
        ->item_stacks[index_of__equipment];
}

#endif
