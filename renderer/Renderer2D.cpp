#include "Renderer2D.hpp"
#include "glwrapper.hpp"
#include "../helpers/glm/glm.hpp"
#include "../helpers/glm/gtc/matrix_transform.hpp"
#include <vector>

struct jzj::Renderer2D::implementation {
    jzj::GLShader *spriteShader;
    jzj::GLVertexArray *vertexArray;
    jzj::GLVertexBuffer<float> *vertexBuffer;
    jzj::GLContextDisplay *display;
    float near;
    float far;
};

jzj::Renderer2D::Renderer2D(jzj::GLContextDisplay *display, float near, float far) : impl(new Renderer2D::implementation) {
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Hardcoded for now
    
    impl->display = display;
    impl->near = near;
    impl->far = far;
    std::string vertexShader =
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
    std::string fragmentShader =
    "#version 330 core\n"
    "in vec2 TexCoords;\n"
    "out vec4 color;\n"
    "uniform sampler2D spriteTexture;\n"
    "uniform vec3 spriteColor;\n"
    "void main() {\n"
    "   color = vec4(spriteColor, 1.0f) * texture(spriteTexture, TexCoords);\n"
    "}\n";
    impl->spriteShader = new jzj::GLShader(vertexShader, fragmentShader);
    
    std::vector<float> vertices = { // vec3 layoutVertex, vec2 layoutTexCoords
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f
    };
    impl->vertexArray = new jzj::GLVertexArray();
    impl->vertexBuffer = new jzj::GLVertexBuffer<float>(vertices);
    impl->vertexArray->bind();
    impl->vertexArray->layout(impl->vertexBuffer, 0, 3, 0, 5 * sizeof(float));
    impl->vertexArray->enable(0);
    impl->vertexArray->layout(impl->vertexBuffer, 1, 2, 3*sizeof(float), 5 * sizeof(float));
    impl->vertexArray->enable(1);
}

jzj::Renderer2D::~Renderer2D() {
    delete impl->vertexArray;
    delete impl->vertexBuffer;
    delete impl->spriteShader;
}

void jzj::Renderer2D::draw(const Sprite *sprite) {
    std::vector<float> vertices = { // vec3 layoutVertex, vec2 layoutTexCoords
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f
    };
    
    impl->vertexBuffer->bind();
    impl->vertexBuffer->update(vertices); // inefficient as fuck
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(impl->display->getWidth()), static_cast<float>(impl->display->getHeight()), 0.0f, impl->near, impl->far);
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, glm::vec3(sprite->getX(), sprite->getY(), sprite->getZ()));
    
    model = glm::translate(model, glm::vec3(0.5f * sprite->getWidth(), 0.5f * sprite->getHeight(), 0));
    
    model = glm::rotate(model, glm::radians(sprite->getPitch()), glm::vec3(1.0f, 0.0f, .0f));
    model = glm::rotate(model, glm::radians(sprite->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(sprite->getRoll()), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::translate(model, glm::vec3(-0.5f * sprite->getWidth(), -0.5f * sprite->getHeight(), 0));
    
    model = glm::scale(model, glm::vec3(sprite->getWidth(),sprite->getHeight(), 1.0f));
    
    impl->spriteShader->use();
    impl->spriteShader->set("model", model);
    impl->spriteShader->set("projection", projection);
    impl->spriteShader->set("view", glm::mat4(1.0f));
    
    impl->spriteShader->set("spriteColor", glm::vec3(sprite->getR(),sprite->getG(),sprite->getB()));
    sprite->activateTexture(0);
    impl->vertexArray->bind();
    
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
    std::cout << ty << std::endl;
    std::vector<float> vertices = { // vec3 layoutVertex, vec2 layoutTexCoords
        0.0f, 1.0f, 1.0f,   tx, ty+th, // bottom left
        1.0f, 0.0f, 1.0f,   tx+tw, ty, // top right
        0.0f, 0.0f, 1.0f,   tx, ty, // top left
        0.0f, 1.0f, 1.0f,   tx, ty+th, // bottom left
        1.0f, 1.0f, 1.0f,   tx+tw, ty+th, // bottom right
        1.0f, 0.0f, 1.0f,   tx+tw, ty  // top right
    };
    
    impl->vertexBuffer->bind();
    impl->vertexBuffer->update(vertices); //inefficient
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(impl->display->getWidth()), static_cast<float>(impl->display->getHeight()), 0.0f, impl->near, impl->far);
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, glm::vec3(spritesheet->getX(), spritesheet->getY(), spritesheet->getZ()));
    
    model = glm::translate(model, glm::vec3(0.5f * spritesheet->getSpriteWidth(), 0.5f * spritesheet->getSpriteHeight(), 0));
    
    model = glm::rotate(model, glm::radians(spritesheet->getPitch()), glm::vec3(1.0f, 0.0f, .0f));
    model = glm::rotate(model, glm::radians(spritesheet->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(spritesheet->getRoll()), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::translate(model, glm::vec3(-0.5f * spritesheet->getSpriteWidth(), -0.5f * spritesheet->getSpriteHeight(), 0));
    
    model = glm::scale(model, glm::vec3(spritesheet->getSpriteWidth(),spritesheet->getSpriteHeight(), 1.0f));
    
    impl->spriteShader->use();
    impl->spriteShader->set("model", model);
    impl->spriteShader->set("projection", projection);
    impl->spriteShader->set("view", glm::mat4(1.0f));
    
    impl->spriteShader->set("spriteColor", glm::vec3(spritesheet->getR(),spritesheet->getG(),spritesheet->getB()));
    spritesheet->activateTexture(0);
    impl->vertexArray->bind();
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void jzj::Renderer2D::clear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
