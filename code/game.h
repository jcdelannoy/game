#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

#include "gameLevel.h"
#include "gameObject.h"
#include "keyboard.h"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction
{
    UP, 
    RIGHT, 
    DOWN, 
    LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

const glm::vec2 PADDLE_SIZE(100.0f, 100.0f);
const GLfloat PADDLE_VELOCITY(500.0f);

class Game
{
    public:
        GameState state;
        GLboolean keys[1024];
        GLuint width, height;
        std::vector<GameLevel> mLevels;
        GLuint mLevelIdx;

        Game(GLuint width, GLuint height);
        ~Game();

        void Init();
        void ProcessInput(GLfloat dt, KeyBoard* keyboard);
        void Update(GLfloat dt);
        void Render();
        void DoCollisions();
        void ResetLevel();
        void ResetPlayer();
};

