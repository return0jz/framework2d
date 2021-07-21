#pragma once
#include <string>
#include "../../lib/glm/glm.hpp"
#include "glheader.h"

namespace jzj {
class GLShader {
public:
    GLShader(const std::string &vert, const std::string &frag);
    //GLShader(const std::string &vert, const std::string &frag, const std::string &geom);
        // I'm probably not gonna use geometry shaders
    ~GLShader();
    void use();
    
    // Uniform methods copied from a shader class I found online lol
    void set(const std::string &name, bool value) const;
    void set(const std::string &name, int value) const;
    void set(const std::string &name, float value) const;
    void set(const std::string &name, const glm::vec2 &value) const;
    void set(const std::string &name, float x, float y) const;
    void set(const std::string &name, const glm::vec3 &value) const;
    void set(const std::string &name, float x, float y, float z) const;
    void set(const std::string &name, const glm::vec4 &value) const;
    void set(const std::string &name, float x, float y, float z, float w);
    void set(const std::string &name, const glm::mat2 &mat) const;
    void set(const std::string &name, const glm::mat3 &mat) const;
    void set(const std::string &name, const glm::mat4 &mat) const;
    
    static std::string loadFromFile(const std::string &path) noexcept(false);
private:
    void handleCompileErrors(unsigned int id);
    void handleLinkErrors(unsigned int id);
    
    unsigned int id;
};
}
