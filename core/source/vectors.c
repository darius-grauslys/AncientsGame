#include "defines.h"
#include "defines_weak.h"
#include <vectors.h>

const Vector__3i32 VECTOR__3i32__OUT_OF_BOUNDS = (Vector__3i32){
    (BIT(31)),
    (BIT(31)),
    (BIT(31))
};
const Vector__3i32F4 VECTOR__3i32F4__OUT_OF_BOUNDS = (Vector__3i32F4){
    (BIT(31)),
    (BIT(31)),
    (BIT(31))
};
const Vector__3i32F8 VECTOR__3i32F8__OUT_OF_BOUNDS = (Vector__3i32F8){
    (BIT(31)),
    (BIT(31)),
    (BIT(31))
};

void offset_vector_by__direction(
        Vector__3i32F4 *p_vector,
        Direction__u8 direction) {
    switch(direction) {
        default:
            break;
        case DIRECTION__NORTH:
            p_vector->y__i32F4++;
            break;
        case DIRECTION__EAST:
            p_vector->x__i32F4++;
            break;
        case DIRECTION__SOUTH:
            p_vector->y__i32F4--;
            break;
        case DIRECTION__WEST:
            p_vector->x__i32F4--;
            break;
        case DIRECTION__NORTH_EAST:
            p_vector->y__i32F4++;
            p_vector->x__i32F4++;
            break;
        case DIRECTION__NORTH_WEST:
            p_vector->y__i32F4++;
            p_vector->x__i32F4--;
            break;
        case DIRECTION__SOUTH_EAST:
            p_vector->y__i32F4--;
            p_vector->x__i32F4++;
            break;
        case DIRECTION__SOUTH_WEST:
            p_vector->y__i32F4--;
            p_vector->x__i32F4--;
            break;
    }
}
