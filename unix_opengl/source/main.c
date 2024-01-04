
#include <stdbool.h>
#include <stdio.h>
#include <debug/debug.h>

#include <rendering/glad/glad.h>
#include <GLFW/glfw3.h>
// #include <glew/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <rendering/stb_image.h>
#include <rendering/shader.h>

const char *source_img_vert = "\n\
#version 330 core\n\
layout(location = 0) in vec3 position;\n\
layout(location = 1) in vec2 uv;\n\
\n\
out vec2 TexCoord;\n\
\n\
void main()\n\
{\n\
    gl_Position = vec4(position, 1);\n\
    TexCoord = uv;\n\
}";

const char *source_img_frag = " \n\
#version 330 core\n\
uniform sampler2D _sample;\n\
\n\
in vec2 TexCoord;\n\
out vec4 color;\n\
\n\
void main()\n\
{\n\
    color = texture(_sample, TexCoord);\n\
    color = vec4(color.xyz, 1);\n\
    //if (color.x == color.y && color.y == color.z && color.z == 0)\n\
    //    color = vec4(1, 0, 0, 1);\n\
    //color = vec4(1,0,0,1);\n\
}";

void create_rect(unsigned int *vao, unsigned int *vbo, unsigned int *ebo)
{
    float rect_vertices[] = {
        -1.0f,  1.0f,  0.0f,        0.0f, 1.0f, // top left
         1.0f,  1.0f,  0.0f,        1.0f, 1.0f, // top right
         1.0f, -1.0f,  0.0f,        1.0f, 0.0f, // bottom right
        -1.0f, -1.0f,  0.0f,        0.0f, 0.0f  // bottom left
    };
    unsigned int rect_indices[] = { 0, 1, 2, 0, 2, 3 };

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);
    glGenBuffers(1, vbo);
    glGenBuffers(1, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertices), rect_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_indices), rect_indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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

    unsigned int rect_vao, rect_vbo, rect_ebo;
    create_rect(&rect_vao, &rect_vbo, &rect_ebo);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(
            "/home/shalidor/Projects/AncientsGame/build/unix_opengl/assets/tiles.png", 
            &width, &height, &channels, 0);

    if (bytes)
    {
        glTexImage2D
        (
            GL_TEXTURE_2D, 
            0, 
            GL_RGB, 
            width, 
            height, 
            0, 
            GL_RGB, 
            GL_UNSIGNED_BYTE,
            bytes
        );
    }
    else
    {
        debug_abort("failed to load image");
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    Shader_2D shader;
    init_shader_2d(&shader, source_img_vert, source_img_frag);

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

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(rect_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    release_shader_2d(&shader);
    stbi_image_free(bytes);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
