#ifndef DEGREE_H
#define DEGREE_H

#include <defines.h>

///
/// Log(N) complexity get degree.
///
Degree__u9 get_angle_between__vectors_3i32(
        Vector__3i32 source__3i32, 
        Vector__3i32 target__3i32);

static inline
bool is_degree_u9__out_of_bounds(
        Degree__u9 angle) {
    return angle >= ANGLE__OUT_OF_BOUNDS;
}

static Degree__u9 inline add_angles(
        Degree__u9 angle_1,
        Degree__u9 angle_2) {
    return (angle_1 + angle_2) & ANGLE__MASK;
}

///
/// Subtract angle_2 from angle_2.
///
static Degree__u9 inline subtract_angles(
        Degree__u9 angle_1,
        Degree__u9 angle_2) {
    return 
        (angle_1 < angle_2)
        ? ANGLE__360 - (angle_2 - angle_1)
        : angle_1 - angle_2
        ;
}

///
/// NOTE: Not super accurate beyond distances of 10 integer units, for best
/// accuracy, look at raycast/ray.h
///
/// Excelent for short range applications however.
///
Vector__3i32F4 get_2i32F4_offset_from__angle(
        Degree__u9 angle);

///
/// Deliciously accurate. So accurate in fact that long distance inaccuracy will
/// be first be caused by limitiations of Degree__u9.
///
/// However, Vector_3i32F20 is not used frequently in the code base.
/// See raycast/ray.h for practical applications.
Vector__3i32F20 get_2i32F20_offset_from__angle(
        Degree__u9 angle);

#endif
