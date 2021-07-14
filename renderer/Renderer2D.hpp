#pragma once
#include "../platform/GLContextDisplay.hpp"
#include "Sprite.hpp"
#include "Spritesheet.hpp"
#include <memory>
#include <string>

namespace jzj {
class Renderer2D {
public:
    Renderer2D(jzj::GLContextDisplay *display, float near, float far);
    void clear(float r, float g, float b, float a);
    void draw(const jzj::Sprite *sprite); // Implement with view matrix from a Camera class
    void draw(const jzj::Spritesheet *spritesheet); // Implement with view matrix from a Camera class
    ~Renderer2D();
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}

