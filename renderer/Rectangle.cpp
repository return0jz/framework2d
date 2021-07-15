#include "Rectangle.hpp"
#include "Renderer2D.hpp"
#include "glwrapper.hpp"
#include "../helpers/glm/glm.hpp"
#include "../helpers/glm/gtc/matrix_transform.hpp"
#include <vector>

struct jzj::Rectangle::implementation {
    float w;
    float h;
    
    float x;
    float y;
    float z;
    
    float rx;
    float ry;
    float rz;
    
    float px;
    float py;
    float pz;
    
    float r;
    float g;
    float b;
};

jzj::Rectangle::Rectangle(float x, float y, float z, float width, float height) : impl(new Rectangle::implementation) {
    impl->x=x;
    impl->y=y;
    impl->z=z;
    impl->w=width;
    impl->h=height;
    impl->rx=0.0f;
    impl->ry=0.0f;
    impl->rz=0.0f;
    impl->px=0.0f;
    impl->py=0.0f;
    impl->pz=0.0f;
    impl->r=1.0f;
    impl->g=1.0f;
    impl->b=1.0f;
}

jzj::Rectangle::~Rectangle() {
}

void jzj::Rectangle::setDimensions(float width, float height) {
    impl->w = width;
    impl->h = height;
}

void jzj::Rectangle::setRotation(float pitch, float yaw, float roll) {
    impl->rx=pitch;
    impl->ry=yaw;
    impl->rz=roll;
}
void jzj::Rectangle::setPosition(float x, float y, float z) {
    impl->x=x;
    impl->y=y;
    impl->z=z;
}

void jzj::Rectangle::setColor(float r, float g, float b) {
    impl->r=r;
    impl->g=g;
    impl->b=b;
}
void jzj::Rectangle::setPivot(float px, float py, float pz) {
    impl->px=px;
    impl->py=py;
    impl->pz=pz;
}
float jzj::Rectangle::getWidth() const{
    return impl->w;
}
float jzj::Rectangle::getHeight() const{
    return impl->h;
}
float jzj::Rectangle::getX() const{
    return impl->x;
}
float jzj::Rectangle::getY() const{
    return impl->y;
}
float jzj::Rectangle::getZ() const{
    return impl->z;
}
float jzj::Rectangle::getPitch() const{
    return impl->rx;
}
float jzj::Rectangle::getYaw() const{
    return impl->ry;
}
float jzj::Rectangle::getRoll() const{
    return impl->rz;
}
float jzj::Rectangle::getR() const{
    return impl->r;
}
float jzj::Rectangle::getG() const{
    return impl->g;
}
float jzj::Rectangle::getB() const{
    return impl->b;
}

float jzj::Rectangle::getPivotX() const{
    return impl->px;
}

float jzj::Rectangle::getPivotY() const{
    return impl->py;
}

float jzj::Rectangle::getPivotZ() const{
    return impl->pz;
}
