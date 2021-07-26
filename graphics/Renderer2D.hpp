#pragma once
#include "GLPlatformLayer.hpp"
#include "Sprite.hpp"
#include "Spritesheet.hpp"
#include "Rectangle.hpp"
#include <memory>
#include <string>
#include "Base.hpp"

namespace jzj {
class Renderer2D : public Base {
public:
    Renderer2D(jzj::GLPlatformLayer *display, float near, float far);
    void clear(float r, float g, float b, float a);
    void setViewport(int x, int y, int w, int h);
    void draw(const jzj::Sprite *sprite); // Implement with view matrix from a Camera class
    void draw(const jzj::Spritesheet *spritesheet); // Implement with view matrix from a Camera class
    void draw(const jzj::Rectangle *rect);
    ~Renderer2D();
private:
    struct implementation;
    jzj::Renderer2D::implementation * impl;
};
}

