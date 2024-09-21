#ifndef SDL_VERTEX_OBJECT_H
#define SDL_VERTEX_OBJECT_H

#include <defines.h>
#include <rendering/opengl/gl_defines.h>

void initialize_vertex_object(GL_Vertex_Object *vertex_object);
void buffer_vertex_object(GL_Vertex_Object *vertex_object,
        uint32_t size_in_bytes, uint32_t vertex_count, float *vertices);
void buffer_vertex_object__element_buffer(
        GL_Vertex_Object *vertex_object,
        uint32_t size_in_bytes__of_indices,
        uint32_t *indices);
void set_attribute_vertex_object(GL_Vertex_Object *vertex_object,
        uint32_t attribute_index,
        uint32_t attribute_size,
        uint32_t gl_attribute_type,
        uint32_t gl_bool_is_normalized,
        uint32_t size_in_bytes__of_attribute,
        void *offset);
void release_vertex_object(GL_Vertex_Object *vertex_object);

void use_vertex_object(GL_Vertex_Object *vertex_object);

#endif
