#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <math.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
//#include "errorReporting.h"


void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);



int main() {
    //initialise the glfw
    glfwInit();

    std::cout << "Current working directory: "
              << std::filesystem::current_path() << std::endl;

    //enableReportGlErrors();
    //no clue yet
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


    //making the points of the triangle
    //we use a range of -1 to 1, with the limit of the range being the border of the window
    //also, as openGL is a 3d renderer, the third coordinate is the z axis.
    GLfloat points[] = {
        //Coordinates,            Colors,
         0.5f,   0.5f,  0.0f,       0.0f, 0.1f, 0.3f,
         0.5f,  -0.5f,  0.0f,       1.0f, 0.2f, 0.2f,
        -0.5f,  -0.5f,  0.0f,       0.0f, 0.3f, 0.1f,
        -0.5f,   0.5f,  0.0f,       0.0f, 1.0f, 0.3f,
    };

    GLuint indices[] ={
        0, 1, 2, //pos of 1st triangle and etc
        0, 2, 3

    };

    //just error checks and for debugging
    GLFWwindow* window = glfwCreateWindow(600, 600, "Triangle", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //just little error checks to give a reason for progam failing
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glViewport(0, 0, 600, 600);

    Shader shaderProgram("default.vert", "default.frag");



    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // declare the variables
    // VAO for Vertex Array Object
    // VBO for Vertex Buffer Object
    // EBO for Element Buffer Object

    //bind the variables
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(points, sizeof(points));
    EBO EBO1(indices, sizeof(indices));


    //link vao to vbo
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //then unbind the variables
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();



    glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //finding the amount of vertices
    int vertAmount = sizeof(points) / sizeof(points[0]) * 6;

    while (!glfwWindowShouldClose(window)) {
        //input
        processInput(window);

        //funny
        glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, vertAmount, GL_UNSIGNED_INT, 0);
        //check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //delete the variable so no wasted mem
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();





    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
