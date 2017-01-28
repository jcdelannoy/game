#include "resourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>

// static variables.
std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

Shader ResourceManager::LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile, const GLchar* geoShaderFile, std::string name)
{
    shaders[name] = LoadShaderFromFile(vertexShaderFile, fragmentShaderFile, geoShaderFile);
    return shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar* file, GLboolean alpha, std::string name)
{
    textures[name] = LoadTextureFromFile(file, alpha);
    return textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return textures[name];
}

void ResourceManager::Clear()
{
    for (auto iter : shaders)
    {
        glDeleteProgram(iter.second.ID);
    }
    for (auto iter : textures)
    {
        glDeleteTextures(1, &iter.second.ID);
    }
}

Shader ResourceManager::LoadShaderFromFile(const GLchar* vertexShaderFile_, const GLchar* fragmentShaderFile_, const GLchar* geoShaderFile_)
{
    // retrieve the source codes from filepaths.
    std::string vertexCodeStr;
    std::string fragmentCodeStr;
    std::string geoCodeStr;
    try
    {
        std::ifstream vertexShaderFile(vertexShaderFile_);
        std::ifstream fragmentShaderFile(fragmentShaderFile_);
        std::stringstream vertexShaderStream, fragmentShaderStream;

        // read file buffer contents into streams.
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        // convert stream into string.
        vertexCodeStr = vertexShaderStream.str();
        fragmentCodeStr = fragmentShaderStream.str();

        // load geometry shader if applicable.
        if (geoShaderFile_ != nullptr)
        {
            std::ifstream geoShaderFile(geoShaderFile_);
            std::stringstream geoShaderStream;
            geoShaderStream << geoShaderFile.rdbuf();
            geoShaderFile.close();
            geoCodeStr = geoShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::Shader: Failed to read shader files." << std::endl;
    }

    const GLchar* vertexShaderCode = vertexCodeStr.c_str();
    const GLchar* fragmentShaderCode = fragmentCodeStr.c_str();
    const GLchar* geoShaderCode = geoCodeStr.c_str();

    // create the shader from source code.
    Shader shader;
    shader.Compile(vertexShaderCode, fragmentShaderCode, (geoShaderFile_ != nullptr) ? geoShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const GLchar* file, GLboolean alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }

    // load image.
    int width, height;
    unsigned char* image = SOIL_load_image(file, &width, &height, 0, (texture.imageFormat == GL_RGBA) ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    texture.Generate(width, height, image);
    SOIL_free_image_data(image);
    return texture;
}
