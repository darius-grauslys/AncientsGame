#ifndef DEGREE_H
#define DEGREE_H

#include <defines.h>

///
/// Log(N) complexity get degree.
///
Degree__u8 get_angle_between__vectors_3i32F4(
        Vector__3i32F4 source__3i32F4, 
        Vector__3i32F4 target__3i32F4);

static Degree__u8 inline add_angles(
        Degree__u8 angle_1,
        Degree__u8 angle_2) {
    return (angle_1 + angle_2) % 256;
}

///
/// Subtract angle_2 from angle_2.
///
static Degree__u8 inline subtract_angles(
        Degree__u8 angle_1,
        Degree__u8 angle_2) {
    return 
        (angle_1 < angle_2)
        ? 256 - (angle_2 - angle_1)
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
        Degree__u8 angle);

///
/// Deliciously accurate. So accurate in fact that long distance inaccuracy will
/// be first be caused by limitiations of Degree__u8.
///
/// However, Vector_3i32F8 is not used frequently in the code base.
/// See raycast/ray.h for practical applications.
Vector__3i32F8 get_2i32F8_offset_from__angle(
        Degree__u8 angle);

#endif
