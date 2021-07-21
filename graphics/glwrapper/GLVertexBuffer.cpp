#include "GLBuffer.hpp"

template <typename T>
jzj::GLVertexBuffer<T>::GLVertexBuffer(const std::vector<T> &vertices, enum GLBufferTarget flag) {
    JZJGLCALL(glGenBuffers(1,&this->id));
    this->bind();
    JZJGLCALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), &vertices[0], static_cast<int>(flag)));
}

template <typename T>
jzj::GLVertexBuffer<T>::~GLVertexBuffer() {
    JZJGLCALL(glDeleteBuffers(1,&id));
}

template <typename T>
void jzj::GLVertexBuffer<T>::bind() {
    JZJGLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->id));
}

template <typename T>
void jzj::GLVertexBuffer<T>::unbind() {
    JZJGLCALL(glBindBuffer(GL_ARRAY_BUFFER,0));
}

template <typename T>
unsigned int jzj::GLVertexBuffer<T>::get() {
    return this->id;
}

template <typename T>
void jzj::GLVertexBuffer<T>::update(const std::vector<T> &vertices) {
    this->bind();
    JZJGLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(T), vertices.data()));
}

template class jzj::GLVertexBuffer<float>;
