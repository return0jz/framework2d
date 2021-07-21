#pragma once
#include <memory>
#include <string>
#include "Transformable.hpp"

namespace jzj {
class Sprite : public Transformable {
    friend class Renderer2D;
public:
    Sprite(const std::string &path);
    ~Sprite();
    void setDimensions(float width, float height);
    void setRotation(float pitch, float yaw, float roll);
    void setPosition(float x, float y, float z);
    void setMixColor(float r, float g, float b); // Color to mix with texture
    void setPivot(float px, float py, float pz=0.0f);
    float getWidth()const;
    float getHeight()const;
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
    std::unique_ptr<implementation> impl;
};
}

