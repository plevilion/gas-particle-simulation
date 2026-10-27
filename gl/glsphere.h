#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

// Sphere mesh used to draw the atoms. Provided by the course's graphics tutorials.

class GLSphere {
public:
    GLSphere() : vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer) {}

    void initialize(GLuint slices = 25, GLuint stacks = 25);

    void draw(QOpenGLShaderProgram& program, int attributeLocation);

    void bind();
    void release();

private:
    QOpenGLBuffer vbo, ibo;
    GLuint vbo_sz;
    GLuint ibo_sz[3];
};
