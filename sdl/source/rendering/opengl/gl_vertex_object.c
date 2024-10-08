#include <rendering/opengl/gl_vertex_object.h>

void initialize_vertex_object_as__unit_square(
        GL_Vertex_Object *vertex_object) {
// void create_rect(unsigned int *vao, unsigned int *vbo, unsigned int *ebo)
    float rect_vertices[] = {
        -1.0f,  1.0f,  0.0f,        0.0f, 1.0f, // top left
         1.0f,  1.0f,  0.0f,        1.0f, 1.0f, // top right
         1.0f, -1.0f,  0.0f,        1.0f, 0.0f, // bottom right
        -1.0f, -1.0f,  0.0f,        0.0f, 0.0f  // bottom left
    };
    unsigned int rect_indices[] = { 0, 1, 2, 0, 2, 3 };

    uint32_t *vao = &vertex_object->handle__attribute_array;
    uint32_t *vbo = &vertex_object->handle__vertex_buffer;
    uint32_t *ebo = &vertex_object->handle__element_buffer;

    initialize_vertex_object(vertex_object);

    buffer_vertex_object(
            vertex_object, 
            sizeof(rect_vertices),
            sizeof(rect_vertices) / (sizeof(float) * 5), 
            rect_vertices);
    buffer_vertex_object__element_buffer(
            vertex_object,
            sizeof(rect_indices),
            rect_indices);
    set_attribute_vertex_object(
            vertex_object, 
            0, 
            3, 
            GL_FLOAT, 
            false, 
            5 * sizeof(float), 
            (void *)0);
    set_attribute_vertex_object(
            vertex_object, 
            1, 
            2, 
            GL_FLOAT, 
            false, 5 * sizeof(float), 
            (void *)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void initialize_vertex_object(GL_Vertex_Object *vertex_object) {
    vertex_object->handle__vertex_buffer = 0;
    vertex_object->handle__attribute_array = 0;
    vertex_object->vertex_count = 0;

    glGenVertexArrays(1, &vertex_object->handle__attribute_array);
    glBindVertexArray(vertex_object->handle__attribute_array);
    glGenBuffers(1, &vertex_object->handle__vertex_buffer);
    glGenBuffers(1, &vertex_object->handle__element_buffer);
}

void buffer_vertex_object(GL_Vertex_Object *vertex_object,
        uint32_t size_in_bytes, uint32_t vertex_count, float *vertices) {
    if (!vertex_object->handle__vertex_buffer) {
        debug_error("Cannot buffer vertex_object, it has not been initialized.");
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertex_object->handle__vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, size_in_bytes, vertices, GL_STATIC_DRAW);
}

void buffer_vertex_object__element_buffer(
        GL_Vertex_Object *vertex_object,
        uint32_t size_in_bytes__of_indices,
        uint32_t *indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_object->handle__element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_in_bytes__of_indices,
            indices, GL_STATIC_DRAW);
}

void set_attribute_vertex_object(GL_Vertex_Object *vertex_object,
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

void release_vertex_object(GL_Vertex_Object *vertex_object) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    if (!vertex_object->handle__vertex_buffer) {
        debug_warning("Tried to release when, vertex_object->handle__vertex_buffer == 0.");
    } else {
        glDeleteBuffers(1, &vertex_object->handle__vertex_buffer);
        vertex_object->handle__vertex_buffer = 0;
    }

    if (!vertex_object->handle__attribute_array) {
        debug_warning("Tried to release when, vertex_object->handle__attribute_array == 0.");
    } else {
        glDeleteVertexArrays(1, &vertex_object->handle__attribute_array);
        vertex_object->handle__attribute_array = 0;
    }
}

void use_vertex_object(GL_Vertex_Object *vertex_object) {
    glBindVertexArray(vertex_object->handle__attribute_array);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_object->handle__vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_object->handle__element_buffer);
}

void GL_set_vertex_object__unit_square__UVs_within__texture_atlas(
        GL_Vertex_Object *p_GL_vertex_object,
        PLATFORM_Texture *p_PLATFORM_texture,
        GLint column,
        GLint row,
        GLint quantity_of__columns,
        GLint quantity_of__rows) {
    float width_of__uv  = 
        ((float)p_PLATFORM_texture->width 
        / quantity_of__columns)
        / (float)p_PLATFORM_texture->width;
    float height_of__uv = 
        ((float)p_PLATFORM_texture->height 
        / quantity_of__rows)
        / (float)p_PLATFORM_texture->height;


    float rect_vertices[] = {
        -1.0f,  1.0f,  0.0f,  
            (width_of__uv * column), 
            (height_of__uv * (row+1)), // top left
         1.0f,  1.0f,  0.0f,
            (width_of__uv * (column+1)), 
            (height_of__uv * (row+1)), // top right
         1.0f, -1.0f,  0.0f,  
            (width_of__uv * (column+1)), 
            (height_of__uv * row), // bottom right
            1.0f, 0.0f, // bottom right
        -1.0f, -1.0f,  0.0f,  
            (width_of__uv * column), 
            (height_of__uv * row), // bottom left
    };

    glBindVertexArray(
            p_GL_vertex_object
            ->handle__attribute_array);
    buffer_vertex_object(
            p_GL_vertex_object, 
            sizeof(rect_vertices),
            sizeof(rect_vertices) / (sizeof(float) * 5), 
            rect_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
