#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "spriteRenderer.h"
#include "gameObject.h"

class GameLevel
{
public:
    GameLevel() {};

    void Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight);
    void Draw(SpriteRenderer& renderer);
    GLboolean IsCompleted();

    std::vector<GameObject> mBricks;

private:
    void Init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};