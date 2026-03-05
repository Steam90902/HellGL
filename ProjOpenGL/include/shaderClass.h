//
// Created by Orange on 15/02/2026.
//

#ifndef PROJOPENGL_SHADERCLASS_H
#define PROJOPENGL_SHADERCLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
};

#endif //PROJOPENGL_SHADERCLASS_H