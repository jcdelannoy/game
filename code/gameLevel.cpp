#include "gameLevel.h"
#include "gameObject.h"
#include "resourceManager.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight)
{
    mBricks.clear();

    GLuint tileCode;
    GameLevel gameLevel;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode)
            {
                row.push_back(tileCode);
            }
            tileData.push_back(row);
        }

        if (tileData.size() > 0)
        {
            this->Init(tileData, levelWidth, levelHeight);
        }
    }
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    // could this be optimized to have all bricks in one VBO?
    for (GameObject& tile : mBricks)
    {
        if (!tile.mIsDestroyed)
        {
            tile.Draw(renderer);
        }
    }
}

GLboolean GameLevel::IsCompleted()
{
    for (GameObject& tile : mBricks)
    {
        if (!tile.mIsSolid && !tile.mIsDestroyed)
        {
            return GL_FALSE;
        }
    }
    return GL_TRUE;
}

void GameLevel::Init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
    GLuint height = tileData.size();
    GLuint width = tileData[0].size();
    GLfloat unitWidth = levelWidth / static_cast<GLfloat>(width);
    GLfloat unitHeight = (GLfloat)(levelHeight / height);
    for (GLuint y = 0; y < height; ++y)
    {
        for (GLuint x = 0; x < width; ++x)
        {
            if (tileData[y][x] == 1) // Solid
            {
                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                Texture2D texture = ResourceManager::GetTexture("block_solid");
                GameObject gameObject(pos, size, texture, glm::vec3(0.8f, 0.8f, 0.7f));
                gameObject.mIsSolid = GL_TRUE;
                mBricks.push_back(gameObject);
            }
            else if (tileData[y][x] > 1)
            {
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                {
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                }
                else if (tileData[y][x] == 3)
                {
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                }
                else if (tileData[y][x] == 4)
                {
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                }
                else if (tileData[y][x] == 5)
                {
                    color = glm::vec3(1.0f, 0.5f, 0.0f);
                }

                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                mBricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
            }
        }
    }
}