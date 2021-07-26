#include "GLTexture2D.hpp"
#include "../../lib/stb_image/stb_image.hpp"
#include <stdexcept>

jzj::GLTexture2D::GLTexture2D(const GLTexture2DFlags &flags, std::string path) {
    JZJGLCALL(glGenTextures(1,&this->id));
    this->bind();
    this->setParameters(flags);
    unsigned char *imgData = stbi_load(path.c_str(), &this->width, &this->height, &this->nchannels, 0);
    if (!imgData)
        throw std::runtime_error("FILE I/O ERROR: UNABLE TO LOAD IMAGE FROM " + path);
    int format = (nchannels==4) ? GL_RGBA : GL_RGB;
    JZJGLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imgData));
    JZJGLCALL(glGenerateMipmap(GL_TEXTURE_2D));
    stbi_image_free(imgData);
}

jzj::GLTexture2D::~GLTexture2D() {
    JZJGLCALL(glDeleteTextures(1, &this->id));
}

void jzj::GLTexture2D::bind() {
    JZJGLCALL(glBindTexture(GL_TEXTURE_2D, this->id));
}

void jzj::GLTexture2D::activate(int unit) {
    JZJGLCALL(glActiveTexture(GL_TEXTURE0 + unit));
    this->bind();
}

void jzj::GLTexture2D::setParameters(const GLTexture2DFlags &flags) {
    JZJGLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(flags.wrapS)));
    JZJGLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(flags.wrapT)));
    JZJGLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(flags.minFilter)));
    JZJGLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(flags.magFilter)));
}
