//
// Created by Orange on 15/02/2026.
//

#ifndef PROJOPENGL_EBO_H
#define PROJOPENGL_EBO_H


#include<glad/glad.h>

class EBO {
public:
    GLuint ID;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};


#endif //PROJOPENGL_EBO_H