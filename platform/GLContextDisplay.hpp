#pragma once

#include <string>
#include <memory>
#include "../Base.hpp"

namespace jzj {
class GLPlatformLayer : public Base {
public:
    GLPlatformLayer(std::string title, int width, int height, int glMajorVersion, int glMinorVersion) noexcept(false);
    ~GLPlatformLayer();
    
    void* getWindow(); // Underlying SDL_Window pointer
    void* getContext(); // Underlying SDL_Context
    
    int getWidth();
    int getHeight();
    bool isFullscreen();
    bool isWindowedFullscreen();
    bool isWindowed();
    
    // Todo: Add window setters (setVisible, resize, etc.)
    void swap();

    void setWidth(int width);
    void setHeight(int height);
    void setWidthAndHeight(int width, int height);
    void setVisible(bool makeVisible);
    void setFullscreen();
    void setWindowedFullscreen();
    void setWindowed();
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}
