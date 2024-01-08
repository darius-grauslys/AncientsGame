#ifndef VERTEX_OBJECT_H
#define VERTEX_OBJECT_H

#include <stdint.h>

typedef struct Vertex_Object_t {
    uint32_t handle__vertex_buffer;
    uint32_t handle__attribute_array;
    uint32_t handle__element_buffer;
    uint32_t vertex_count;
} Vertex_Object;

void init_vertex_object(Vertex_Object *vertex_object);
void buffer_vertex_object(Vertex_Object *vertex_object,
        uint32_t size_in_bytes, uint32_t vertex_count, float *vertices);
void buffer_vertex_object__element_buffer(
        Vertex_Object *vertex_object,
        uint32_t size_in_bytes__of_indices,
        uint32_t *indices);
void set_attribute_vertex_object(Vertex_Object *vertex_object,
        uint32_t attribute_index,
        uint32_t attribute_size,
        uint32_t gl_attribute_type,
        uint32_t gl_bool_is_normalized,
        uint32_t size_in_bytes__of_attribute,
        void *offset);
void release_vertex_object(Vertex_Object *vertex_object);

void use_vertex_object(Vertex_Object *vertex_object);

#endif
