#pragma once

// Headers for all imgui stuff
#include "../lib/imgui/imgui.h"
#include "GLPlatformLayer.hpp"
#include "Base.hpp"
#include <utility>

namespace jzj {
class IMGUIcontext : public Base { // Simple abstraction for Dear ImGui context management
public:
    IMGUIcontext(jzj::GLPlatformLayer *display, void (*styleFunction)(ImGuiStyle* style)); // from ImgGui::GetStyle()
    ~IMGUIcontext();
    void update();
    void render();
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}
