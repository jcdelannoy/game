#include "gameObject.h"

GameObject::GameObject()
    : mPosition(0.0f, 0.0f),
    mSize(1.0f, 1.0f),
    mVelocity(0.0f, 0.0f),
    mColor(1.0f, 1.0f, 1.0f),
    mRotation(0.0f),
    mSpriteTexture(),
    mIsSolid(GL_FALSE),
    mIsDestroyed(GL_FALSE)
{
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color_)
    : mPosition(pos),
    mSize(size),
    mVelocity(0.0f, 0.0f),
    mColor(color_),
    mRotation(0.0f),
    mSpriteTexture(sprite),
    mIsSolid(GL_FALSE),
    mIsDestroyed(GL_FALSE)
{
}

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.Draw(mSpriteTexture, mPosition, mSize, mRotation, mColor);
}