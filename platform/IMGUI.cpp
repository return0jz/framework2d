#include "IMGUI.hpp"
#include "../lib/imgui/imgui_impl_sdl.h"
#include "../lib/imgui/imgui_impl_opengl3.h"
#include <SDL2/SDL.h>

struct jzj::IMGUIcontext::implementation {
    jzj::GLPlatformLayer *display;
};

jzj::IMGUIcontext::IMGUIcontext(jzj::GLPlatformLayer *display, void (*styleFunction)(ImGuiStyle* style)) : impl(new implementation){
    this->impl->display = display;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    styleFunction(&ImGui::GetStyle());
    
    ImGui_ImplSDL2_InitForOpenGL((SDL_Window *)display->getWindow(), display->getContext());
    ImGui_ImplOpenGL3_Init(NULL);
}

jzj::IMGUIcontext::~IMGUIcontext() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void jzj::IMGUIcontext::update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame((SDL_Window *)this->impl->display->getWindow());
    ImGui::NewFrame();
}

void jzj::IMGUIcontext::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

