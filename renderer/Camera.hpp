#pragma once
#include <memory>

namespace jzj {
class Camera {
    Camera(int x, int y);
    ~Camera();
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}
