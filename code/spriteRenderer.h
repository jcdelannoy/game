#pragma once
#include "shader.h"
#include "texture.h"

class SpriteRenderer
{
public:
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();

    void Draw(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    Shader shader;
    GLuint quadVAO;
    void InitRenderData();
};