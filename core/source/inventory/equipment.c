#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_stack.h"
#include <inventory/equipment.h>

void initialize_equipment(
        Equipment *p_equipment) {
    for (Index__u8 uuid = 0;
            uuid 
            < EQUIPMENT_ITEM_STACK_QUANTITY_OF;
            uuid++) {
        initialize_item_stack_as__empty(
                get_p_item_stack_by__index_in__equipment(
                    p_equipment, uuid), uuid);
    }
}

