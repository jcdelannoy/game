#pragma once

#include <GL/glew.h>

class Texture2D
{
public:
    GLuint ID;
    GLuint width, height;

    // texture format.
    GLuint internalFormat;
    GLuint imageFormat;

    // texture configuration.
    GLuint wrapS; // wrapping mode on S axis.
    GLuint wrapT; // wrapping mode on T axis.
    GLuint filterMin; // filtering mode if [texture pixels] < [screen pixels].
    GLuint filterMag; // filtering mode if [texture pixels] > [screen pixels].

    Texture2D();
    void Generate(GLuint width, GLuint height, unsigned char* data);

    // bind as the current active GL_TEXTURE_2D texture object.
    void Bind() const;
};