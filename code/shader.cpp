#include "shader.h"
#include <iostream>

Shader& Shader::Use()
{
    glUseProgram(this->ID);
    return (*this);
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource)
{
    // vertex shader.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    CheckCompileErrors(vertexShader, "VERTEX");

    // fragment shader.
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    CheckCompileErrors(fragmentShader, "FRAGMENT");

    // geometry shader.
    GLuint geoShader;
    if (geometrySource != nullptr)
    {
        geoShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geoShader, 1, &geometrySource, NULL);
        glCompileShader(geoShader);
        CheckCompileErrors(geoShader, "GEOMETRY");
    }

    // shader program.
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    if (geometrySource != nullptr)
    {
        glAttachShader(this->ID, geoShader);
    }
    glLinkProgram(this->ID);
    CheckCompileErrors(this->ID, "PROGRAM");

    // shaders are linked to the program, no longer necessary.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometrySource != nullptr)
    {
        glDeleteShader(geoShader);
    }
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniform1f(uniformLoc, value);
}

void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniform1i(uniformLoc, value);
}

void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniform2f(uniformLoc, x, y);
}

void Shader::SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniform2f(uniformLoc, value.x, value.y);
}

void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniform3f(uniformLoc, x, y, z);
}

void Shader::SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniform3f(uniformLoc, value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniform4f(uniformLoc, x, y, z, w);
}

void Shader::SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniform4f(uniformLoc, value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }
    GLint uniformLoc = glGetUniformLocation(this->ID, name);
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::CheckCompileErrors(GLuint object, std::string type)
{
    const int logSize = 1024;
    GLint success;
    GLchar infoLog[logSize];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, logSize, NULL, infoLog);
            std::cout << "| ERROR::Shader:: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -------------------------------------------------------------------"
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -------------------------------------------------------------------"
                << std::endl;
        }
    }
}
