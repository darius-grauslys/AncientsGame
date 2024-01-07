#ifndef VERTEX_OBJECT_H
#define VERTEX_OBJECT_H

#include <stdint.h>

typedef struct Vertex_Object_t {
    uint32_t handle__buffer;
    uint32_t handle__attribute_array;
    uint32_t vertex_count;
} Vertex_Object;

void init_vertex_object(Vertex_Object *vertex_object);
void release_vertex_object(Vertex_Object *vertex_object);

#endif
