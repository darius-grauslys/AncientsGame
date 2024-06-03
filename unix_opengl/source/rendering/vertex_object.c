#include <rendering/vertex_object.h>
#include <debug/debug.h>
#include <rendering/glad/glad.h>

void initialize_vertex_object(Vertex_Object *vertex_object) {
    vertex_object->handle__vertex_buffer = 0;
    vertex_object->handle__attribute_array;
    vertex_object->vertex_count = 0;

    glGenVertexArrays(1, &vertex_object->handle__attribute_array);
    glBindVertexArray(vertex_object->handle__attribute_array);
    glGenBuffers(1, &vertex_object->handle__vertex_buffer);
    glGenBuffers(1, &vertex_object->handle__element_buffer);
}

void buffer_vertex_object(Vertex_Object *vertex_object,
        uint32_t size_in_bytes, uint32_t vertex_count, float *vertices) {
    if (!vertex_object->handle__vertex_buffer) {
        debug_error("Cannot buffer vertex_object, it has not been initialized.");
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertex_object->handle__vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, size_in_bytes, vertices, GL_STATIC_DRAW);
}

void buffer_vertex_object__element_buffer(
        Vertex_Object *vertex_object,
        uint32_t size_in_bytes__of_indices,
        uint32_t *indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_object->handle__element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_in_bytes__of_indices,
            indices, GL_STATIC_DRAW);
}

void set_attribute_vertex_object(Vertex_Object *vertex_object,
        uint32_t attribute_index,
        uint32_t attribute_size,
        uint32_t gl_attribute_type,
        uint32_t gl_bool_is_normalized,
        uint32_t size_in_bytes__of_attribute,
        void *offset) {
    use_vertex_object(vertex_object);
    glVertexAttribPointer(
            attribute_index, attribute_size,
            gl_attribute_type, gl_bool_is_normalized,
            size_in_bytes__of_attribute, offset);
    glEnableVertexAttribArray(attribute_index);
}

void release_vertex_object(Vertex_Object *vertex_object) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    if (!vertex_object->handle__vertex_buffer) {
        debug_error("Tried to release when, vertex_object->handle__vertex_buffer == 0.");
    } else {
        glDeleteBuffers(1, &vertex_object->handle__vertex_buffer);
        vertex_object->handle__vertex_buffer = 0;
    }

    if (!vertex_object->handle__attribute_array) {
        debug_error("Tried to release when, vertex_object->handle__attribute_array == 0.");
    } else {
        glDeleteVertexArrays(1, &vertex_object->handle__attribute_array);
        vertex_object->handle__attribute_array = 0;
    }
}

void use_vertex_object(Vertex_Object *vertex_object) {
    glBindVertexArray(vertex_object->handle__attribute_array);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_object->handle__vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_object->handle__element_buffer);
}
