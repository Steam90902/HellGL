//
// Created by Orange on 15/02/2026.
//

#ifndef PROJOPENGL_VAO_H
#define PROJOPENGL_VAO_H

#include "glad/glad.h"
#include "VBO.h"

class VAO {
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif //PROJOPENGL_VAO_H