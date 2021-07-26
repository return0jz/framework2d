#pragma once
#include <string>
#include <memory>
#include "Transformable.hpp"

namespace jzj {
class Spritesheet : public Transformable {
    // Crap design don't ask
    // Pretty much like a normal Sprite, except can set index in Spritesheet.
    friend class Renderer2D;
public:
    Spritesheet(const std::string &path, int cellRow, int cellCol);
    ~Spritesheet();
    void setSprite(int index);
    void setCells(int row, int col);
    void setDimensions(float width, float height);
    void setRotation(float pitch, float yaw, float roll);
    void setPosition(float x, float y, float z);
    void setMixColor(float r, float g, float b); // Color to mix with texture
    void setCellCol(int val);
    void setCellRow(int val);
    void setPivot(float px, float py, float pz=0.0f);
    
    unsigned int getSprite()const;
    unsigned int getRow()const;
    unsigned int getCol()const;
    unsigned int getSheetWidth() const;
    unsigned int getSheetHeight() const;
    unsigned int getDefaultSpriteHeight() const;
    unsigned int getDefaultSpriteWidth() const;
    float getSpriteHeight() const;
    float getSpriteWidth() const;
    float getX()const;
    float getY()const;
    float getZ()const;
    float getYaw()const;
    float getPitch()const;
    float getRoll()const;
    float getR()const;
    float getG()const;
    float getB()const;
    float getPivotX() const;
    float getPivotY() const;
    float getPivotZ() const;
private:
    void activateTexture(int index)const;
    void bindTexture()const;
    struct implementation;
    jzj::Spritesheet::implementation *impl;
};
}
