
#include <stdbool.h>
#include <stdio.h>
#include <debug/debug.h>

#include <rendering/glad/glad.h>
#include <GLFW/glfw3.h>
// #include <glew/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <rendering/stb_image.h>
#include <rendering/shader_passthrough.h>

#include <world/chunk.h>
#include <rendering/chunk_renderer.h>
#include <rendering/vertex_object.h>
#include <rendering/framebuffer.h>

void create_rect(Vertex_Object *vertex_object) {
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

    init_vertex_object(vertex_object);

    buffer_vertex_object(vertex_object, sizeof(rect_vertices),
            sizeof(rect_vertices) / (sizeof(float) * 5), rect_vertices);
    buffer_vertex_object__element_buffer(
            vertex_object,
            sizeof(rect_indices),
            rect_indices);
    set_attribute_vertex_object(vertex_object, 
            0, 3, GL_FLOAT, false, 5 * sizeof(float), (void *)0);
    set_attribute_vertex_object(vertex_object, 
            1, 2, GL_FLOAT, false, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLAPIENTRY
debug_callback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

int main(void) {
    if (!glfwInit())
        return 1;

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *window = glfwCreateWindow(900, 600, "my opengl window", NULL, NULL);
    if (window == NULL) {
        debug_abort("Failed to create GLFWwindow!");
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
        debug_abort("Failed to initalize GLAD!");
        return 1;
    }

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( debug_callback, 0 );

    // int code = glewInit();
    // bool err = code != GLEW_OK;

    // if (err)
    // {
    //     debug_abort("Failed to initalize OpenGL loader! Error: %d", code);
    //     return 1;
    // }

    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);

    Vertex_Object vertex_object;
    create_rect(&vertex_object);

    Texture texture;
    Texture texture_chunk;
    init_texture__with_size(&texture_chunk, 
            TILE_PIXEL_WIDTH * CHUNK__WIDTH,
            TILE_PIXEL_HEIGHT * CHUNK__HEIGHT);
    init_texture__with_path(&texture, 
            "/home/shalidor/Projects/AncientsGame/build/unix_opengl/assets/tiles.png");

    Chunk chunk;

    init_chunk(&chunk, 0, 0);
    for (int i=0;i<CHUNK__QUANTITY_OF_TILES;i++) {
        chunk.tiles[i].the_kind_of_tile__this_tile_is =
            (enum Tile_Kind)(i / CHUNK__WIDTH);
        chunk.tiles[i].flags = (i % CHUNK__WIDTH);
    }

    Framebuffer framebuffer_source;
    Framebuffer framebuffer_target;

    init_framebuffer(&framebuffer_source);
    init_framebuffer(&framebuffer_target);

    set_framebuffer__color_attachment__with_a_texture(
            &framebuffer_source,
            &texture);
    set_framebuffer__color_attachment__with_a_texture(
            &framebuffer_target,
            &texture_chunk);
    
    render_chunk(&chunk, 
            &framebuffer_source,
            &framebuffer_target);

    release_framebuffer(&framebuffer_source);
    release_framebuffer(&framebuffer_target);

    Shader_2D shader;
    init_shader_2d_as__shader_passthrough(&shader);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        int display_width, display_height;
        glfwGetFramebufferSize(window, &display_width, &display_height);
        glViewport(0, 0, display_width, display_height);

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        use_shader_2d(&shader);
        // image_shader.use();

        use_texture(&texture_chunk);
        use_vertex_object(&vertex_object);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    release_shader_2d(&shader);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
