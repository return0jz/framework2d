#pragma once
#include "../platform/GLPlatformLayer.hpp"
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
<<<<<<< HEAD
    void setViewport(int x, int y, int w, int h);
=======
>>>>>>> efe143511a1ce5bf1c0e78e2f05e648568e8aef6
    void draw(const jzj::Sprite *sprite); // Implement with view matrix from a Camera class
    void draw(const jzj::Spritesheet *spritesheet); // Implement with view matrix from a Camera class
    void draw(const jzj::Rectangle *rect);
    ~Renderer2D();
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}

