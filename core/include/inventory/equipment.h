#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <defines.h>

void initialize_equipment(
        Equipment *p_equipment);

static inline
Item_Stack *get_p_item_stack_in__slot_armor_of__equipment(
        Equipment *p_equipment) {
    return &p_equipment->slot__armor;
}

static inline
Item_Stack *get_p_item_stack_in__slot_main_hand_of__equipment(
        Equipment *p_equipment) {
    return &p_equipment->slot__main_hand;
}

static inline
Item_Stack *get_p_item_stack_in__slot_off_hand_of__equipment(
        Equipment *p_equipment) {
    return &p_equipment->slot__off_hand;
}

static inline
Item_Stack *get_p_item_stack_in__slot_consumable_of__equipment(
        Equipment *p_equipment,
        Quantity__u8 consumable_slot) {
#ifndef NDEBUG
    if (consumable_slot
            >= INVENTORY_CONSUMABLES_QUANTITY_OF) {
        debug_abort("get_p_item_stack_in__slot_consumable_of__equipment, index out of bounds: %d", consumable_slot);
        return 0;
    }
#endif
    return &p_equipment->slot__consumable[consumable_slot];
}

#endif
