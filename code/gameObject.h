#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "texture.h"
#include "spriteRenderer.h"

class GameObject
{
public:
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));

    virtual void Draw(SpriteRenderer& renderer);

    glm::vec2 mPosition;
    glm::vec2 mSize;
    glm::vec2 mVelocity;
    glm::vec3 mColor;
    GLfloat mRotation;

    GLboolean mIsSolid;
    GLboolean mIsDestroyed;

    Texture2D mSpriteTexture;
};