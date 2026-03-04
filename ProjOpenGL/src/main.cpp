#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <math.h>
#include <vector>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
//#include "errorReporting.h"


void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

std::vector<GLfloat> circleCoords(float radius);

GLFWwindow* StartGLFW();

int main() {
    //initialise the glfw

    std::cout << "Current working directory: "
              << std::filesystem::current_path() << std::endl;

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
    GLFWwindow* window = StartGLFW();

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



    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //finding the amount of vertices
    int vertAmount = sizeof(points) / sizeof(points[0]);

    while (!glfwWindowShouldClose(window)) {
        //input
        processInput(window);

        //funny
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();
        // I wanna make circles work here as a function
        glDrawElements(GL_TRIANGLES, vertAmount, GL_UNSIGNED_INT, nullptr);
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

GLFWwindow *StartGLFW()
{

    glfwInit();

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


    GLFWwindow* window = glfwCreateWindow(800, 800, "Particle Hopeful", NULL, NULL);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
    }


    glViewport(0, 0, 800, 800);

    return window;
}


std::vector<GLfloat> circleCoords(float radius) {
    const int steps = 20;
    const float angle = 2.0f * M_PI / steps;
    GLfloat color[] = {1.0f, 0.0f, 0.0f};
    std::vector<GLfloat> newCoords = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    newCoords.reserve((steps + 1) * 6);

    newCoords.push_back(0.0f);
    newCoords.push_back(0.0f);
    newCoords.push_back(0.0f);
    for (GLfloat c : color) newCoords.push_back(c);



    for (int i=0; i<=steps; i++) {
        float newX = sin(angle*i) * radius;
        float newY = cos(angle*i) * radius;
        newCoords.push_back(newX);
        newCoords.push_back(newY);
        newCoords.push_back(0.0f);
        //might be a bug here, idk y tho
        for ( GLfloat ic: color) {
            newCoords.push_back(ic);
        }//repeat of before
    }

    return newCoords;
}