#include "Spritesheet.hpp"
#include "Sprite.hpp"
#include "Renderer2D.hpp"
#include "glwrapper.hpp"
#include "../helpers/glm/glm.hpp"
#include "../helpers/glm/gtc/matrix_transform.hpp"
#include <vector>

struct jzj::Spritesheet::implementation {
    jzj::GLTexture2D *texture;
    unsigned int cellRow;
    unsigned int cellCol;
    unsigned int sheetW;
    unsigned int sheetH;
    float spriteW;
    float spriteH;
    unsigned int spriteIndex;
    
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

jzj::Spritesheet::Spritesheet(const std::string &path, int cellRow, int cellCol) : impl(new Spritesheet::implementation) {
    impl->texture = new jzj::GLTexture2D(jzj::GLTexture2DFlags(), path);
    impl->spriteIndex = 0;
    impl->sheetW = impl->texture->width;
    impl->sheetH = impl->texture->height;
    impl->cellRow = cellRow;
    impl->cellCol = cellCol;
    impl->spriteW = impl->sheetW/impl->cellRow;
    impl->spriteH = impl->sheetH/impl->cellCol;

    impl->x=0.0f;
    impl->y=0.0f;
    impl->z=0.0f;
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

jzj::Spritesheet::~Spritesheet() {
    delete impl->texture;
}

void jzj::Spritesheet::setSprite(int index) {
    impl->spriteIndex = index % (impl->cellCol*impl->cellRow);
    // Technically clamp is not needed because of GL_TEXTURE_REPEAT, but it's fine to have it anyway
}

void jzj::Spritesheet::setDimensions(float width, float height) {
    impl->spriteW = width;
    impl->spriteH = height;
}

void jzj::Spritesheet::setCells(int row, int col) {
    impl->cellRow = row;
    impl->cellCol = col;
}

void jzj::Spritesheet::setRotation(float pitch, float yaw, float roll) {
    impl->rx=pitch;
    impl->ry=yaw;
    impl->rz=roll;
}
void jzj::Spritesheet::setPosition(float x, float y, float z) {
    impl->x=x;
    impl->y=y;
    impl->z=z;
}

void jzj::Spritesheet::setMixColor(float r, float g, float b) {
    impl->r=r;
    impl->g=g;
    impl->b=b;
}
void jzj::Spritesheet::setPivot(float px, float py, float pz) {
    impl->px=px;
    impl->py=py;
    impl->pz=pz;
}
unsigned int jzj::Spritesheet::getSprite() const{
    return impl->spriteIndex;
}
unsigned int jzj::Spritesheet::getSheetWidth() const{
    return impl->sheetW;
}
unsigned int jzj::Spritesheet::getSheetHeight() const{
    return impl->sheetH;
}
float jzj::Spritesheet::getSpriteWidth() const{
    return impl->spriteW;
}
float jzj::Spritesheet::getSpriteHeight() const{
    return impl->spriteH;
}
unsigned int jzj::Spritesheet::getDefaultSpriteWidth() const{
    return impl->sheetW/impl->cellRow;
}
unsigned int jzj::Spritesheet::getDefaultSpriteHeight() const{
    return impl->sheetH/impl->cellCol;
}
unsigned int jzj::Spritesheet::getRow() const{
    return impl->cellRow;
}
unsigned int jzj::Spritesheet::getCol() const{
    return impl->cellCol;
}
float jzj::Spritesheet::getX() const{
    return impl->x;
}
float jzj::Spritesheet::getY() const{
    return impl->y;
}
float jzj::Spritesheet::getZ() const{
    return impl->z;
}
float jzj::Spritesheet::getPitch() const{
    return impl->rx;
}
float jzj::Spritesheet::getYaw() const{
    return impl->ry;
}
float jzj::Spritesheet::getRoll() const{
    return impl->rz;
}
float jzj::Spritesheet::getR() const{
    return impl->r;
}
float jzj::Spritesheet::getG() const{
    return impl->g;
}
float jzj::Spritesheet::getB() const{
    return impl->b;
}

float jzj::Spritesheet::getPivotX() const{
    return impl->px;
}

float jzj::Spritesheet::getPivotY() const{
    return impl->py;
}

float jzj::Spritesheet::getPivotZ() const{
    return impl->pz;
}

void jzj::Spritesheet::activateTexture(int index) const{
    impl->texture->activate(index);
}

void jzj::Spritesheet::bindTexture() const{
    impl->texture->bind();
}

