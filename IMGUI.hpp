#pragma once

// Headers for all imgui stuff
#include "helpers/imgui/imgui.h"
#include "platform/GLContextDisplay.hpp"
#include <utility>

namespace jzj {
class IMGUIcontext { // Simple abstraction for Dear ImGui context management
public:
    IMGUIcontext(jzj::GLContextDisplay *display, void (*styleFunction)(ImGuiStyle* style)); // from ImgGui::GetStyle()
    ~IMGUIcontext();
    void update();
    void render();
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}
