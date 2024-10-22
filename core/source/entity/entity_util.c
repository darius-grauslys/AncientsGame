#include <entity/entity_util.h>
#include <vectors.h>
#include <degree.h>
#include <entity/entity.h>

Vector__3i32F4 get_vector_3i32F4_thats__infront_of_this__entity(
        Entity *p_entity) {
    Vector__3i32F4 offset =
        get_2i32F4_offset_from__angle(
            get_angle_from__direction(
                p_entity->direction));
    offset.x__i32F4 <<= 4;
    offset.y__i32F4 <<= 4;
    return
        add_vectors__3i32F4(
                get_vector_3i32F4_from__entity(p_entity), 
                offset);
}
