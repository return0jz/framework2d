#pragma once
#include <memory>
#include <string>

namespace jzj {
class Rectangle {
    friend class Renderer2D;
public:
    Rectangle(float x, float y, float z, float width, float height);
    ~Rectangle();
    void setDimensions(float width, float height);
    void setRotation(float pitch, float yaw, float roll);
    void setPosition(float x, float y, float z);
    void setColor(float r, float g, float b); // Color to mix with texture
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
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}

