//
// Created by Orange on 15/02/2026.
//

#ifndef PROJOPENGL_VBO_H
#define PROJOPENGL_VBO_H

#include<glad/glad.h>

class VBO {
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};

#endif //PROJOPENGL_VBO_H