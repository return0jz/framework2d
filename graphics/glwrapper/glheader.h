#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <iostream>
#include <string>
namespace jzj {
void GLCALLfunc_(std::string funcCall, std::string src, int line);

#ifdef DEBUG
#define JZJGLCALL(x) x; jzj::GLCALLfunc_(#x, __FILE__, __LINE__)
#else
#define JZJGLCALL(x) x
#endif
}
