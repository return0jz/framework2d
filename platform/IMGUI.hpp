#pragma once

// Headers for all imgui stuff
#include "../lib/imgui/imgui.h"
#include "GLPlatformLayer.hpp"
#include "Base.hpp"
#include <utility>

namespace jzj {
class IMGUIcontext : public Base { // context management
public:
    IMGUIcontext(jzj::GLPlatformLayer *display, void (*styleFunction)(ImGuiStyle* style) = NULL); // from ImgGui::GetStyle()
    ~IMGUIcontext();
    void update();
    void render();
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}
