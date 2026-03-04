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

VAO circleCoords(float radius);

GLFWwindow* StartGLFW();

int main() {
    //initialise the glfw

    std::cout << "Current working directory: "
              << std::filesystem::current_path() << std::endl;

    //making the points of the triangle
    //we use a range of -1 to 1, with the limit of the range being the border of the window
    //also, as openGL is a 3d renderer, the third coordinate is the z axis.


    //just error checks and for debugging
    GLFWwindow* window = StartGLFW();

    Shader shaderProgram("default.vert", "default.frag");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // declare the variables
    // VAO for Vertex Array Object
    // VBO for Vertex Buffer Object
    // EBO for Element Buffer Object

    //bind the variables
    //VAO VAO1;
    //VAO1.Bind();

    //VBO VBO1(points.data(), points.size() * sizeof(GLfloat));
    //EBO EBO1(indices.data(), indices.size() * sizeof(GLuint));


    //link vao to vbo
    //VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    //VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //then unbind the variables
    //VAO1.Unbind();
    //VBO1.Unbind();
    //EBO1.Unbind();

    VAO circleVAO = circleCoords(0.1f);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //finding the amount of vertices
    //int vertAmount = points.size() / sizeof(GLfloat);

    while (!glfwWindowShouldClose(window)) {
        //input
        processInput(window);

        //cool bgd
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        circleVAO.Bind();
        // I wanna make circles work here as a function
        glDrawArrays(GL_TRIANGLE_FAN, 0, 20 * 6);
        //check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //delete the variable so no wasted mem
    circleVAO.Delete();
    //VBO1.Delete();
    //EBO1.Delete();
    shaderProgram.Delete();


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
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


    GLFWwindow* window = glfwCreateWindow(800, 800, "Particle Hopeful", nullptr, nullptr);

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

VAO circleCoords(float radius) {
    const int steps = 20;
    const float angle = 2.0f * M_PI / steps;
    GLfloat color[] = {1.0f, 0.0f, 0.0f};
    std::vector<GLfloat> points;
    points.reserve((steps + 1) * 6);

    points.push_back(0.0f);
    points.push_back(0.0f);
    points.push_back(0.0f);
    for (GLfloat c : color) points.push_back(c);



    for (int i=0; i<=steps; i++) {
        float newX = sin(angle*i) * radius;
        float newY = cos(angle*i) * radius;
        points.push_back(newX);
        points.push_back(newY);
        points.push_back(0.0f);
        //might be a bug here, idk y tho
        for ( GLfloat ic: color) {
            points.push_back(ic);
        }//repeat of before
    }

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(points.data(), points.size() * sizeof(GLfloat));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)nullptr);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();

    return VAO1;
}