#pragma once

#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "texture.h"
#include "shader.h"

class ResourceManager
{
public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;

    // load and generate a shader program from [vertex, fragment, geo] shader source code. 
    static Shader LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile, const GLchar* geoShaderFile, std::string name);
    static Shader GetShader(std::string name);

    // load and generate texture from file.
    static Texture2D LoadTexture(const GLchar* file, GLboolean alpha, std::string name);
    static Texture2D GetTexture(std::string name);

    // deallocate all.
    static void Clear();

private:
    ResourceManager() {};
    static Shader LoadShaderFromFile(const GLchar* vertexShaderFile_, const GLchar* fragmentShaderFile_, const GLchar* geoShaderFile_ = nullptr);
    static Texture2D LoadTextureFromFile(const GLchar* file, GLboolean alpha);
};