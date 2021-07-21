#pragma once
#include <vector>
#include "glheader.h"

namespace jzj {
enum class GLBufferTarget {
    static_draw = GL_STATIC_DRAW,
    dynamic_draw = GL_DYNAMIC_DRAW,
    stream_draw = GL_STREAM_DRAW
};

template <typename T>
class GLVertexBuffer {
public:
    GLVertexBuffer(const std::vector<T> &vertices, enum GLBufferTarget flag = GLBufferTarget::stream_draw);
    ~GLVertexBuffer();
    void bind();
    void unbind();
    void update(const std::vector<T> &vertices);
    unsigned int get();
private:
    unsigned int id;
};

template <typename T>
class GLIndexBuffer {
public:
    GLIndexBuffer(const std::vector<T> &indices, enum GLBufferTarget flag = GLBufferTarget::stream_draw);
    ~GLIndexBuffer();
    void bind();
    void unbind();
    void update(const std::vector<T> &indices);
    unsigned int get();
private:
    unsigned int id;
};
}
