#include "Sprite.hpp"
#include "Renderer2D.hpp"
#include "glwrapper.hpp"
#include "../helpers/glm/glm.hpp"
#include "../helpers/glm/gtc/matrix_transform.hpp"
#include <vector>

struct jzj::Sprite::implementation {
    jzj::GLTexture2D *texture;
    float w;
    float h;
    
    float x;
    float y;
    float z;
    
    float rx;
    float ry;
    float rz;
    
    float r;
    float g;
    float b;
};

jzj::Sprite::Sprite(const std::string &path) : impl(new Sprite::implementation) {
    impl->texture = new jzj::GLTexture2D(jzj::GLTexture2DFlags(), path);

    impl->w = impl->texture->width;
    impl->h = impl->texture->height;
    impl->x=0.0f;
    impl->y=0.0f;
    impl->z=0.0f;
    impl->rx=0.0f;
    impl->ry=0.0f;
    impl->rz=0.0f;
    impl->r=1.0f;
    impl->g=1.0f;
    impl->b=1.0f;
}

jzj::Sprite::~Sprite() {
    delete impl->texture;
}

void jzj::Sprite::setDimensions(float width, float height) {
    impl->w = width;
    impl->h = height;
}

void jzj::Sprite::setRotation(float pitch, float yaw, float roll) {
    impl->rx=pitch;
    impl->ry=yaw;
    impl->rz=roll;
}
void jzj::Sprite::setPosition(float x, float y, float z) {
    impl->x=x;
    impl->y=y;
    impl->z=z;
}

void jzj::Sprite::setMixColor(float r, float g, float b) {
    impl->r=r;
    impl->g=g;
    impl->b=b;
}

float jzj::Sprite::getWidth() const{
    return impl->w;
}
float jzj::Sprite::getHeight() const{
    return impl->h;
}

float jzj::Sprite::getX() const{
    return impl->x;
}
float jzj::Sprite::getY() const{
    return impl->y;
}
float jzj::Sprite::getZ() const{
    return impl->z;
}
float jzj::Sprite::getPitch() const{
    return impl->rx;
}
float jzj::Sprite::getYaw() const{
    return impl->ry;
}
float jzj::Sprite::getRoll() const{
    return impl->rz;
}
float jzj::Sprite::getR() const{
    return impl->r;
}
float jzj::Sprite::getG() const{
    return impl->g;
}
float jzj::Sprite::getB() const{
    return impl->b;
}

void jzj::Sprite::activateTexture(int index) const{
    impl->texture->activate(index);
}

void jzj::Sprite::bindTexture() const{
    impl->texture->bind();
}
