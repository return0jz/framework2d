#include "GLContextDisplay.hpp"
#include <SDL2/SDL.h>

#ifdef _WIN32
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <utility>
#include <iostream>
#include <stdexcept>

#define JZJSDLINITERROR 0
#define JZJSDLWINDOWINITERROR 1
#define JZJCONTEXTINITERROR 2
#define JZJGLEWINTIERROR 3

struct jzj::GLContextDisplay::implementation {
    implementation() {}
    SDL_Window *window;
    void* glContext;
    void initSDL(std::string title, int width, int height, int glMajorVersion, int glMinorVersion) {
        glMajorVersion = std::max(glMajorVersion, 3);
        if(SDL_Init(SDL_INIT_EVERYTHING)<0) {
            throw JZJSDLINITERROR;
        }
        
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glMajorVersion);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glMinorVersion);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        
        window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
        if(!window) {
            throw JZJSDLWINDOWINITERROR;
        }
        glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            throw JZJCONTEXTINITERROR;
        }
    }
    
    void loadGLRoutines() {
        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            throw JZJGLEWINTIERROR;
        }
    }
    
    void handleErrors(int n) {
        std::string msg1;
        std::string msg2;
        switch(n) {
            case JZJSDLINITERROR:
                msg1 = "SDL2 Library Initialization Error:";
                msg2 = SDL_GetError();
                break;
            case JZJSDLWINDOWINITERROR:
                msg1 = "Window Initialization Error:";
                msg2 = SDL_GetError();
                break;
            case JZJCONTEXTINITERROR:
                msg1 = "OpenGL Context Initialization Error:";
                msg2 = SDL_GetError();
                break;
            case JZJGLEWINTIERROR:
                msg1 = "OpenGL Loading Error:";
                msg2 = "Unable to load OpenGL routines";
            break;
        }
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, msg1.c_str(), msg2.c_str(), nullptr);
        throw std::runtime_error(msg1 + " " + msg2);
    }
};

jzj::GLContextDisplay::GLContextDisplay(std::string title, int width, int height, int glMajorVersion, int glMinorVersion) : impl(new implementation){
    try {
        this->impl->initSDL(title,width,height,glMajorVersion,glMinorVersion);
        this->impl->loadGLRoutines();
    }
    catch(int n) {
        this->impl->handleErrors(n);
    }
}

jzj::GLContextDisplay::~GLContextDisplay() {
    SDL_GL_DeleteContext(this->impl->glContext);
    SDL_DestroyWindow(this->impl->window);
    SDL_Quit();
}

int jzj::GLContextDisplay::getWidth() {
    int width;
    SDL_GetWindowSize(this->impl->window, &width, nullptr);
    return width;
}

int jzj::GLContextDisplay::getHeight() {
    int height;
    SDL_GetWindowSize(this->impl->window, nullptr, &height);
    return height;
}

void *jzj::GLContextDisplay::getWindow() {
    return static_cast<void*>(this->impl->window);
}

void *jzj::GLContextDisplay::getContext() {
    return this->impl->glContext;
}

bool jzj::GLContextDisplay::isFullscreen() {
    return SDL_GetWindowFlags(this->impl->window) & SDL_WINDOW_FULLSCREEN;
}

bool jzj::GLContextDisplay::isWindowedFullscreen() {
    return SDL_GetWindowFlags(this->impl->window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
}

bool jzj::GLContextDisplay::isWindowed() {
    return !(this->isFullscreen() | this->isWindowedFullscreen());
}


void jzj::GLContextDisplay::swap() {
    SDL_GL_SwapWindow(this->impl->window);
}

void jzj::GLContextDisplay::setWidth(int width) {
    SDL_SetWindowSize(this->impl->window, width, this->getHeight());
}

void jzj::GLContextDisplay::setHeight(int height) {
    SDL_SetWindowSize(this->impl->window, this->getWidth(), height);
}

void jzj::GLContextDisplay::setWidthAndHeight(int width, int height) {
    SDL_SetWindowSize(this->impl->window, width, height);
}

void jzj::GLContextDisplay::setVisible(bool makeVisible) {
    if(makeVisible) {
        SDL_ShowWindow(this->impl->window);
    } else {
        SDL_HideWindow(this->impl->window);
    }
}

void jzj::GLContextDisplay::setFullscreen() {
    SDL_SetWindowFullscreen(this->impl->window, SDL_WINDOW_FULLSCREEN);
}

void jzj::GLContextDisplay::setWindowedFullscreen() {
    SDL_SetWindowFullscreen(this->impl->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void jzj::GLContextDisplay::setWindowed() {
    SDL_SetWindowFullscreen(this->impl->window, 0);
}

