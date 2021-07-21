#pragma once
#include <string>
#include "glheader.h"

namespace jzj {
struct GLTexture2DFlags {
    GLTexture2DFlags() :
    wrapS(GLTexture2DFlags::wrap::repeat),
    wrapT(GLTexture2DFlags::wrap::repeat),
    minFilter(GLTexture2DFlags::filter::linear),
    magFilter(GLTexture2DFlags::filter::linear)
    {}
    enum class wrap {
        mirrored_repeat = GL_MIRRORED_REPEAT,
        repeat = GL_REPEAT,
        clampedge = GL_CLAMP_TO_EDGE,
    };
    enum class filter {
        nearest = GL_NEAREST,
        linear = GL_LINEAR,
        linearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
        linearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
        nearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
        nearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST
    };
    GLTexture2DFlags::wrap wrapS;
    GLTexture2DFlags::wrap wrapT;
    GLTexture2DFlags::filter minFilter;
    GLTexture2DFlags::filter magFilter;
};

class GLTexture2D { // Represents an OpenGL texture object made of RGB or RGBA data in bytes.
public:
    GLTexture2D(const GLTexture2DFlags &flags, std::string path) noexcept(false);
    ~GLTexture2D();
    void bind();
    void activate(int unit);
    void setParameters(const GLTexture2DFlags &flags);
    int width;
    int height;
    int nchannels;
private:
    unsigned int id;
};
}
