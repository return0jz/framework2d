#include "glheader.hpp"
#include <string>

void jzj::GLCALLfunc_(std::string funcCall, std::string src, int line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::string errstr;
        switch (err)
        {
            case GL_INVALID_ENUM:
                errstr = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                errstr = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                errstr = "GL_INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                errstr = "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                errstr = "GL_STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                errstr = "GL_OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errstr = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
        }
        std::cerr << "OPENGL ERROR: " << errstr << " FROM FILE " << src << " AT LINE " << line << " FROM CALL " << funcCall << std::endl;
    }
}
