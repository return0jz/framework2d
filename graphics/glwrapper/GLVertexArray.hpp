#pragma once
#include <cstdio>
#include "GLBuffer.hpp"
#include "glheader.h"

namespace jzj {
class GLVertexArray {
public:
    GLVertexArray();
    ~GLVertexArray();
    void bind();
    
    // stride is the offset between one attribute of a vertex and the same attribute of the next vertex. (
    // offset is the offset between the beginning of a vertex and the specified attribute.
    void layout(GLVertexBuffer<float> *vb, unsigned int index, int count, std::size_t offset, std::size_t stride);
    void enable(unsigned int index);
private:
    unsigned int id;
};
}
