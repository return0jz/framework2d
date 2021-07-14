#pragma once
#include <memory>
#include <string>

namespace jzj {
class Sprite {
    friend class Renderer2D;
public:
    Sprite(const std::string &path);
    ~Sprite();
    void setDimensions(float width, float height);
    void setRotation(float pitch, float yaw, float roll);
    void setPosition(float x, float y, float z);
    void setMixColor(float r, float g, float b); // Color to mix with texture
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
private:
    void activateTexture(int index)const;
    void bindTexture()const;
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}
