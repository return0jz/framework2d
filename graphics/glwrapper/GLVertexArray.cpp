#include "GLVertexArray.hpp"
#include "glheader.h"


jzj::GLVertexArray::GLVertexArray() {
    JZJGLCALL(glGenVertexArrays(1, &id));
}

jzj::GLVertexArray::~GLVertexArray() {
    JZJGLCALL(glDeleteVertexArrays(1, &id));
}

void jzj::GLVertexArray::bind() {
    JZJGLCALL(glBindVertexArray(id));
}

void jzj::GLVertexArray::layout(GLVertexBuffer<float> *vb, unsigned int index, int count, std::size_t offset, std::size_t stride) {
    vb->bind();
    JZJGLCALL(glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, (GLsizei) stride, (const void*)offset));
}

void jzj::GLVertexArray::enable(unsigned int index) {
    JZJGLCALL(glEnableVertexAttribArray(index));
}
