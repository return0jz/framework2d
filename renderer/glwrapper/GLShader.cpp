#include "GLShader.hpp"
#include "glheader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

jzj::GLShader::GLShader(const std::string &vert, const std::string &frag) {
    unsigned int vertId = JZJGLCALL(glCreateShader(GL_VERTEX_SHADER));
    unsigned int fragId = JZJGLCALL(glCreateShader(GL_FRAGMENT_SHADER));
    
    const char* vertdata = vert.data();
    const char* fragdata = frag.data();
    
    JZJGLCALL(glShaderSource(vertId, 1, &vertdata, 0));
    JZJGLCALL(glShaderSource(fragId, 1, &fragdata, 0));
    
    JZJGLCALL(glCompileShader(vertId));
    this->handleCompileErrors(vertId);
    JZJGLCALL(glCompileShader(fragId));
    this->handleCompileErrors(fragId);
    
    this->id = JZJGLCALL(glCreateProgram());
    JZJGLCALL(glAttachShader(this->id, vertId));
    JZJGLCALL(glAttachShader(this->id, fragId));
    JZJGLCALL(glLinkProgram(this->id));
    this->handleLinkErrors(this->id);
    JZJGLCALL(glDeleteShader(vertId));
    JZJGLCALL(glDeleteShader(fragId));
}

jzj::GLShader::~GLShader() {
    JZJGLCALL(glDeleteProgram(this->id));
}

void jzj::GLShader::use() {
    JZJGLCALL(glUseProgram(this->id));
}

void jzj::GLShader::set(const std::string &name, bool value) const{
     JZJGLCALL(glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value));
}
void jzj::GLShader::set(const std::string &name, int value) const{
     JZJGLCALL(glUniform1i(glGetUniformLocation(this->id, name.c_str()), value));
    
}
void jzj::GLShader::set(const std::string &name, float value) const{
    JZJGLCALL(glUniform1f(glGetUniformLocation(this->id, name.c_str()), value));
    
}
void jzj::GLShader::set(const std::string &name, const glm::vec2 &value) const{
    JZJGLCALL(glUniform2fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]));
    
}
void jzj::GLShader::set(const std::string &name, float x, float y) const{
    JZJGLCALL(glUniform2f(glGetUniformLocation(this->id, name.c_str()), x, y));
    
}
void jzj::GLShader::set(const std::string &name, const glm::vec3 &value) const{
    JZJGLCALL(glUniform3fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]));
    
}
void jzj::GLShader::set(const std::string &name, float x, float y, float z) const{
    JZJGLCALL(glUniform3f(glGetUniformLocation(this->id, name.c_str()), x, y, z));
    
}
void jzj::GLShader::set(const std::string &name, const glm::vec4 &value) const{
    JZJGLCALL(glUniform4fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]));
    
}
void jzj::GLShader::set(const std::string &name, float x, float y, float z, float w){
    JZJGLCALL(glUniform4f(glGetUniformLocation(this->id, name.c_str()), x, y, z, w));
    
}
void jzj::GLShader::set(const std::string &name, const glm::mat2 &mat) const{
    JZJGLCALL(glUniformMatrix2fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]));
    
}
void jzj::GLShader::set(const std::string &name, const glm::mat3 &mat) const
{
    JZJGLCALL(glUniformMatrix3fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]));
    
}
void jzj::GLShader::set(const std::string &name, const glm::mat4 &mat) const
{
    JZJGLCALL(glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]));
    
}

std::string jzj::GLShader::loadFromFile(const std::string &path) {
    std::string src;
    std::ifstream fileInput;
    fileInput.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        fileInput.open(path);
        std::stringstream srcstream;
        srcstream << fileInput.rdbuf();
        fileInput.close();
        src = srcstream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << ("FILE I/O ERROR: FAILED TO LOAD FILE AT FILEPATH " + path) << std::endl;
    }
    return src;
}

void jzj::GLShader::handleCompileErrors(unsigned int id) {
    int param;
    JZJGLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &param));
    if (!param) {
        JZJGLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &param));
        std::string output;
        output.resize(param);
        char* outputdata = &output[0];
        JZJGLCALL(glGetShaderInfoLog(id,param,NULL,outputdata));
        JZJGLCALL(glGetShaderiv(id, GL_SHADER_TYPE, &param));
        
        std::string shaderType;
        if (param == GL_VERTEX_SHADER) {
            shaderType = "VERTEX SHADER";
        }
        else if (param == GL_FRAGMENT_SHADER) {
            shaderType = "FRAGMENT SHADER";
        }
        else if (param == GL_GEOMETRY_SHADER) {
            shaderType = "GEOMETRY SHADER";
        }
        
        std::cerr << shaderType << " " << "COMPILATION LOG_FILE: " << "\n" << output << std::endl;
    }
}

void jzj::GLShader::handleLinkErrors(unsigned int id) {
    int param;
    JZJGLCALL(glGetProgramiv(id, GL_LINK_STATUS, &param));
    if (!param) {
        JZJGLCALL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &param));
        std::string output;
        output.resize(param);
        char* outputdata = &output[0];
        JZJGLCALL(glGetProgramInfoLog(id,param,NULL,outputdata));
        std::cerr << "LINKING LOG_FILE: " << "\n" << output << std::endl;
    }
}
