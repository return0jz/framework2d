#include "Renderer2D.hpp"
#include "glwrapper.h"
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include <vector>

struct jzj::Renderer2D::implementation {
    jzj::GLShader *rectShader;
    jzj::GLVertexArray *rectVertexArray;
    jzj::GLVertexBuffer<float> *rectVertexBuffer;
    
    jzj::GLShader *spriteShader;
    jzj::GLVertexBuffer<float> *spriteVertexBuffer;
    jzj::GLVertexArray *spriteVertexArray;

    jzj::GLPlatformLayer *display;
    float near;
    float far;
};

jzj::Renderer2D::Renderer2D(jzj::GLPlatformLayer *display, float near, float far) {
    this->impl = new jzj::Renderer2D::implementation;
    impl->display = display;
    impl->near = near;
    impl->far = far;
    std::string spriteVertexShader =
    "#version 330 core\n"
    "layout (location = 0) in vec3 layoutVertex;\n"
    "layout (location = 1) in vec2 layoutTexCoords;\n"
    "out vec2 TexCoords;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   TexCoords = layoutTexCoords;\n"
    "   gl_Position = projection * view * model * vec4(layoutVertex,1.0);\n"
    "}\n";
    std::string spriteFragmentShader =
    "#version 330 core\n"
    "in vec2 TexCoords;\n"
    "out vec4 color;\n"
    "uniform sampler2D spriteTexture;\n"
    "uniform vec3 spriteColor;\n"
    "void main() {\n"
    "   color = vec4(spriteColor, 1.0f) * texture(spriteTexture, TexCoords);\n"
    "}\n";
    std::string rectVertexShader =
    "#version 330 core\n"
    "layout (location = 0) in vec3 layoutVertex;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   gl_Position = projection * view * model * vec4(layoutVertex,1.0f);\n"
    "}\n";
    std::string rectFragmentShader =
    "#version 330 core\n"
    "out vec4 color;\n"
    "uniform vec3 rectColor;\n"
    "void main() {\n"
    "   color = vec4(rectColor, 1.0f);\n"
    "}\n";
    
    std::vector<float> spriteVertices = { // vec3 layoutVertex, vec2 layoutTexCoords
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };
    std::vector<float> rectVertices = { // vec3 layoutVertex
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Hardcoded for now
    
    impl->spriteShader = new jzj::GLShader(spriteVertexShader, spriteFragmentShader);
    impl->rectShader = new jzj::GLShader(rectVertexShader, rectFragmentShader);

    impl->rectVertexArray = new jzj::GLVertexArray();
    impl->rectVertexArray->bind();
    impl->rectVertexBuffer = new jzj::GLVertexBuffer<float>(rectVertices);
    impl->rectVertexArray->layout(impl->rectVertexBuffer, 0, 3, 0, 3 * sizeof(float));
    impl->rectVertexArray->enable(0);

    impl->spriteVertexArray = new jzj::GLVertexArray();
    impl->spriteVertexArray->bind();
    impl->spriteVertexBuffer = new jzj::GLVertexBuffer<float>(spriteVertices);
    impl->spriteVertexArray->layout(impl->spriteVertexBuffer, 0, 3, 0, 5 * sizeof(float));
    impl->spriteVertexArray->enable(0);
    impl->spriteVertexArray->layout(impl->spriteVertexBuffer, 1, 2, 3*sizeof(float), 5 * sizeof(float));
    impl->spriteVertexArray->enable(1);
}

jzj::Renderer2D::~Renderer2D() {
    delete impl->spriteVertexArray;
    delete impl->spriteVertexBuffer;
    delete impl->rectVertexArray;
    delete impl->rectVertexBuffer;
    
    delete impl->rectShader;
    delete impl->spriteShader;
    delete impl;
}

void jzj::Renderer2D::draw(const Sprite *sprite) {
    std::vector<float> vertices = { // vec3 layoutVertex, vec2 layoutTexCoords
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };
    
    impl->spriteVertexBuffer->bind();
    impl->spriteVertexBuffer->update(vertices); // inefficient as fuck
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(impl->display->getWidth()), static_cast<float>(impl->display->getHeight()), 0.0f, impl->near, impl->far);
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, glm::vec3(sprite->getX(), sprite->getY(), sprite->getZ()));
    
    model = glm::translate(model, glm::vec3(sprite->getPivotX(), sprite->getPivotY(), sprite->getPivotZ()));
    model = glm::rotate(model, glm::radians(sprite->getPitch()), glm::vec3(1.0f, 0.0f, .0f));
    model = glm::rotate(model, glm::radians(sprite->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(sprite->getRoll()), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-sprite->getPivotX(), -sprite->getPivotY(), -sprite->getPivotZ()));
    
    model = glm::scale(model, glm::vec3(sprite->getWidth(),sprite->getHeight(), 1.0f));
    
    impl->spriteShader->use();
    impl->spriteShader->set("model", model);
    impl->spriteShader->set("projection", projection);
    impl->spriteShader->set("view", glm::mat4(1.0f));
    
    impl->spriteShader->set("spriteColor", glm::vec3(sprite->getR(),sprite->getG(),sprite->getB()));
    sprite->activateTexture(0);
    impl->spriteVertexArray->bind();
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void jzj::Renderer2D::draw(const Spritesheet *spritesheet) {
    // The actual default width and heights (unscaled)
    const int sw = (float)spritesheet->getSheetWidth()/spritesheet->getRow();
    const int sh = (float)spritesheet->getSheetHeight()/spritesheet->getCol();
    
    const float tw = sw / (float)spritesheet->getSheetWidth();
    const float th = sh / (float)spritesheet->getSheetHeight();
    const float tx = (spritesheet->getSprite() % spritesheet->getRow())*tw;
    const float ty = (spritesheet->getSprite() / spritesheet->getRow())*th;
    std::vector<float> vertices = { // vec3 layoutVertex, vec2 layoutTexCoords
        0.0f, 1.0f, 0.0f,   tx, ty+th, // bottom left
        1.0f, 0.0f, 0.0f,   tx+tw, ty, // top right
        0.0f, 0.0f, 0.0f,   tx, ty, // top left
        0.0f, 1.0f, 0.0f,   tx, ty+th, // bottom left
        1.0f, 1.0f, 0.0f,   tx+tw, ty+th, // bottom right
        1.0f, 0.0f, 0.0f,   tx+tw, ty  // top right
    };
    
    impl->spriteVertexBuffer->bind();
    impl->spriteVertexBuffer->update(vertices); //inefficient
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(impl->display->getWidth()), static_cast<float>(impl->display->getHeight()), 0.0f, impl->near, impl->far);
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, glm::vec3(spritesheet->getX(), spritesheet->getY(), spritesheet->getZ()));
    
    model = glm::translate(model, glm::vec3(spritesheet->getPivotX(), spritesheet->getPivotY(), spritesheet->getPivotZ()));
    model = glm::rotate(model, glm::radians(spritesheet->getPitch()), glm::vec3(1.0f, 0.0f, .0f));
    model = glm::rotate(model, glm::radians(spritesheet->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(spritesheet->getRoll()), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-spritesheet->getPivotX(), -spritesheet->getPivotY(), -spritesheet->getPivotZ()));
    
    model = glm::scale(model, glm::vec3(spritesheet->getSpriteWidth(),spritesheet->getSpriteHeight(), 1.0f));
    
    impl->spriteShader->use();
    impl->spriteShader->set("model", model);
    impl->spriteShader->set("projection", projection);
    impl->spriteShader->set("view", glm::mat4(1.0f));
    
    impl->spriteShader->set("spriteColor", glm::vec3(spritesheet->getR(),spritesheet->getG(),spritesheet->getB()));
    spritesheet->activateTexture(0);
    impl->spriteVertexArray->bind();
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void jzj::Renderer2D::draw(const jzj::Rectangle *rect) {
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(impl->display->getWidth()), static_cast<float>(impl->display->getHeight()), 0.0f, impl->near, impl->far);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(rect->getX(), rect->getY(), rect->getZ()));

    model = glm::translate(model, glm::vec3(rect->getPivotX(), rect->getPivotY(), rect->getPivotZ()));
    model = glm::rotate(model, glm::radians(rect->getPitch()), glm::vec3(1.0f, 0.0f, .0f));
    model = glm::rotate(model, glm::radians(rect->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rect->getRoll()), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-rect->getPivotX(), -rect->getPivotY(), -rect->getPivotZ()));

    model = glm::scale(model, glm::vec3(rect->getWidth(),rect->getHeight(), 1.0f));

    impl->rectShader->use();
    impl->rectShader->set("model", model);
    impl->rectShader->set("projection", projection);
    impl->rectShader->set("view", glm::mat4(1.0f));

    impl->rectShader->set("rectColor", glm::vec3(rect->getR(),rect->getG(),rect->getB()));

    impl->rectVertexArray->bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
 
void jzj::Renderer2D::clear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void jzj::Renderer2D::setViewport(int x, int y, int w, int h) {
    glViewport(x, y, w, h);
}
