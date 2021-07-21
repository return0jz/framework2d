#include "Rect.hpp"
#include "Renderer2D.hpp"
#include "glwrapper.hpp"
#include "../helpers/glm/glm.hpp"
#include "../helpers/glm/gtc/matrix_transform.hpp"
#include <vector>

struct jzj::Rect::implementation {
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

jzj::Rect::Rect(float x, float y, float z, float width, float height) : impl(new Rect::implementation) {
    impl->x=x;
    impl->y=y;
    impl->z=z;
    impl->rx=0.0f;
    impl->ry=0.0f;
    impl->rz=0.0f;
    impl->r=1.0f;
    impl->g=1.0f;
    impl->b=1.0f;
}

jzj::Rect::~Rect() {
    delete impl->texture;
}

void jzj::Rect::setDimensions(float width, float height) {
    impl->w = width;
    impl->h = height;
}

void jzj::Rect::setRotation(float pitch, float yaw, float roll) {
    impl->rx=pitch;
    impl->ry=yaw;
    impl->rz=roll;
}
void jzj::Rect::setPosition(float x, float y, float z) {
    impl->x=x;
    impl->y=y;
    impl->z=z;
}

void jzj::Rect::setColor(float r, float g, float b) {
    impl->r=r;
    impl->g=g;
    impl->b=b;
}
float jzj::Rect::getWidth() const{
    return impl->w;
}
float jzj::Rect::getHeight() const{
    return impl->h;
}
float jzj::Rect::getX() const{
    return impl->x;
}
float jzj::Rect::getY() const{
    return impl->y;
}
float jzj::Rect::getZ() const{
    return impl->z;
}
float jzj::Rect::getPitch() const{
    return impl->rx;
}
float jzj::Rect::getYaw() const{
    return impl->ry;
}
float jzj::Rect::getRoll() const{
    return impl->rz;
}
float jzj::Rect::getR() const{
    return impl->r;
}
float jzj::Rect::getG() const{
    return impl->g;
}
float jzj::Rect::getB() const{
    return impl->b;
}
