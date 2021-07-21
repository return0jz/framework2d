#include "GLBuffer.hpp"

template <typename T>
jzj::GLIndexBuffer<T>::GLIndexBuffer(const std::vector<T> &indices, enum GLBufferTarget flag) {
    JZJGLCALL(glGenBuffers(1,&this->id));
    this->bind();
    JZJGLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(T), indices.data(), static_cast<int>(flag) ));
}

template <typename T>
jzj::GLIndexBuffer<T>::~GLIndexBuffer() {
    JZJGLCALL(glDeleteBuffers(1,&this->id));
}

template <typename T>
void jzj::GLIndexBuffer<T>::bind() {
    JZJGLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id));
}

template <typename T>
void jzj::GLIndexBuffer<T>::unbind() {
    JZJGLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}

template <typename T>
unsigned int jzj::GLIndexBuffer<T>::get() {
    return this->id;
}

template <typename T>
void jzj::GLIndexBuffer<T>::update(const std::vector<T> &indices) {
    this->bind();
    JZJGLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(T), indices.data()));
}

template class jzj::GLIndexBuffer<unsigned int>;
template class jzj::GLIndexBuffer<unsigned short>;
template class jzj::GLIndexBuffer<unsigned char>;

