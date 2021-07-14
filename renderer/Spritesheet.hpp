#pragma once
#include <string>
#include <memory>

namespace jzj {
class Spritesheet {
    // Crap design don't ask
    // Pretty much like a normal Sprite, except can set index in Spritesheet.
    // Sheet itself and default divisions are unchangeable since I can't find a possible reason to need it,
    // but may add it later.
    friend class Renderer2D;
public:
    Spritesheet(const std::string &path, int cellRow, int cellCol);
    ~Spritesheet();
    void setSprite(int index);
    int getSprite()const;
    void setCells(int row, int col);
    void setDimensions(float width, float height);
    void setRotation(float pitch, float yaw, float roll);
    void setPosition(float x, float y, float z);
    void setMixColor(float r, float g, float b); // Color to mix with texture
    void setCellCol(int val);
    void setCellRow(int val);
    
    unsigned int getRow()const;
    unsigned int getCol()const;
    unsigned int getSheetWidth() const;
    unsigned int getSheetHeight() const;
    unsigned int getSpriteHeight() const;
    unsigned int getSpriteWidth() const;
    unsigned int getDefaultSpriteHeight() const;
    unsigned int getDefaultSpriteWidth() const;
    float getX()const;
    float getY()const;
    float getZ()const;
    float getYaw()const;
    float getPitch()const;
    float getRoll()const;
    float getR()const;
    float getG()const;
    float getB()const;
private:
    void activateTexture(int index)const;
    void bindTexture()const;
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}
