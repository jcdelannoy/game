#include <algorithm>

#include "game.h"
#include "gameObject.h"
#include "resourceManager.h"
#include "spriteRenderer.h"

SpriteRenderer* renderer;
GameObject* paddle;

// forward declarations.
GLboolean CheckCollision(GameObject& one, GameObject& two);
Direction GetClosestDirection(glm::vec2 target);

Game::Game(GLuint width, GLuint height) :
    state(GAME_ACTIVE),
    keys(),
    width(width),
    height(height)
{
}

Game::~Game()
{
    delete renderer;
    delete paddle;
 }

void Game::Init()
{
    ResourceManager::LoadShader("code\\shaders\\sprite.vert", "code\\shaders\\sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("code\\shaders\\particle.vert", "code\\shaders\\particle.frag", nullptr, "particle");
    ResourceManager::LoadShader("code\\shaders\\postProcessing.vert", "code\\shaders\\postProcessing.frag", nullptr, "postProcessing");

    // left, right, bottom, top.
    GLfloat glWidth = static_cast<GLfloat>(this->width);
    GLfloat glHeight = static_cast<GLfloat>(this->height);
    glm::mat4 projection = glm::ortho(0.0f, glWidth, glHeight, 0.0f, -1.0f, 1.0f);

    // configure sprite shader.
    Shader spriteShader = ResourceManager::GetShader("sprite");
    spriteShader.Use();
    spriteShader.SetInteger("image", 0);
    spriteShader.SetMatrix4("projection", projection);

    // configure particle shader.
    Shader partShader = ResourceManager::GetShader("particle");
    partShader.Use();
    partShader.SetInteger("sprite", 0);
    partShader.SetMatrix4("projection", projection);

    // create renderer.
    renderer = new SpriteRenderer(spriteShader);

    // load textures.
    ResourceManager::LoadTexture("data\\img\\background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("data\\img\\awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("data\\img\\block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("data\\img\\block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("data\\img\\awesomeface.png", GL_TRUE, "paddle");
    ResourceManager::LoadTexture("data\\img\\particle.png", GL_TRUE, "particle");
 
    // load levels.
    GameLevel one;
    GLuint levelWidth = (GLuint)(this->width);
    GLuint levelHeight = (GLuint)(this->height * 0.5f);
    one.Load("data\\levels\\one.lvl", levelWidth, levelHeight);
    mLevels.push_back(one);
    
    GameLevel two;
    two.Load("data\\levels\\two.lvl", levelWidth, levelHeight);
    mLevels.push_back(two);

    GameLevel three;
    three.Load("data\\levels\\three.lvl", levelWidth, levelHeight);
    mLevels.push_back(three);

    GameLevel four;
    four.Load("data\\levels\\four.lvl", levelWidth, levelHeight);
    mLevels.push_back(four);

    // create paddle.
    Texture2D paddleTex = ResourceManager::GetTexture("paddle");
    glm::vec2 paddlePos = glm::vec2((this->width - PADDLE_SIZE.x) * 0.5f, this->height - PADDLE_SIZE.y);
    paddle = new GameObject(paddlePos, PADDLE_SIZE, paddleTex);
 }

void Game::Update(GLfloat dt)
{
    DoCollisions();
 }

void Game::ProcessInput(GLfloat dt)
{
    if (this->state == GAME_ACTIVE)
    {
        GLfloat velocity = PADDLE_VELOCITY * dt;
        
        // move paddle.
        if (this->keys[GLFW_KEY_A])
        {
            if (paddle->mPosition.x >= 0)
            {
                paddle->mPosition.x -= velocity;
            }
        }
        if (this->keys[GLFW_KEY_D])
        {
            if (paddle->mPosition.x <= this->width - paddle->mSize.x)
            { 
                paddle->mPosition.x += velocity;
            }
        }
    }
}

void Game::Render()
{
    if (this->state == GAME_ACTIVE)
    {
        // draw background.
        Texture2D backgroundTex = ResourceManager::GetTexture("background");
        renderer->Draw(backgroundTex, glm::vec2(0.0f, 0.0f), glm::vec2(width, height), 0.0f);

        // draw level.
        mLevels[mLevelIdx].Draw(*renderer);

        // draw paddle.
        paddle->Draw(*renderer);
    }
}

void Game::ResetLevel()
{
    GLuint levelWidth = (GLuint)(this->width);
    GLuint levelHeight = (GLuint)(this->height * 0.5f);
    if (mLevelIdx == 0)
    {
        mLevels[0].Load("data\\levels\\one.lvl", levelWidth, levelHeight);
    }
    else if (mLevelIdx == 1)
    {
        mLevels[1].Load("data\\levels\\two.lvl", levelWidth, levelHeight);
    }
    else if (mLevelIdx == 2)
    {
        mLevels[2].Load("data\\levels\\three.lvl", levelWidth, levelHeight);
    }
    else if (mLevelIdx == 3)
    {
        mLevels[3].Load("data\\levels\\four.lvl", levelWidth, levelHeight);
    }
}

void Game::ResetPlayer()
{
    paddle->mSize = PADDLE_SIZE;
    paddle->mPosition = glm::vec2((this->width * 0.5f) - (PADDLE_SIZE.x * 0.5f), this->height - PADDLE_SIZE.y);
}

GLboolean ShouldSpawn(GLuint chance)
{
    GLuint random = rand() % chance;
    return (random == 0);
}

void Game::DoCollisions()
{
    // collision detection between with each box.
    //for (GameObject& box : mLevels[mLevelIdx].mBricks)
    //{
    //    if (!box.mIsDestroyed)
    //    {
    //        // perform collision detection and response here.
    //    }
    //}
}

Direction GetClosestDirection(glm::vec2 target)
{
    glm::vec2 compass[] =
    {
        glm::vec2(0.0f, 1.0f), // UP
        glm::vec2(1.0f, 0.0f), // RIGHT
        glm::vec2(0.0f, -1.0f), // DOWN
        glm::vec2(-1.0f, 0.0f) // LEFT
    };

    GLfloat max = 0.0f;
    GLuint bestMatch = 0;
    for (GLuint i = 0; i <= LEFT; ++i)
    {
        GLfloat dotProduct = glm::dot(glm::normalize(target), compass[i]);
        if (dotProduct > max)
        {
            max = dotProduct;
            bestMatch = i;
        }
    }

    return ((Direction)bestMatch);
}

GLboolean CheckCollision(GameObject& one, GameObject& two)
{
    bool collisionX = ((one.mPosition.x + one.mSize.x) >= two.mPosition.x) && ((two.mPosition.x + two.mSize.x) >= one.mPosition.x);
    bool collisionY = ((one.mPosition.y + one.mSize.y) >= two.mPosition.y) && ((two.mPosition.y + two.mSize.y) >= one.mPosition.y);
    return collisionX && collisionY;
}


