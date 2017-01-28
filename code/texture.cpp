#include "texture.h"

Texture2D::Texture2D()
    : width(0),
    height(0),
    internalFormat(GL_RGB),
    imageFormat(GL_RGB),
    wrapS(GL_REPEAT),
    wrapT(GL_REPEAT),
    filterMin(GL_LINEAR),
    filterMag(GL_LINEAR)
{
    glGenTextures(1, &(this->ID));
}

void Texture2D::Generate(GLuint width, GLuint height, unsigned char* data)
{
    this->width = width;
    this->height = height;

    // create texture.
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

    // texture wrap and filter modes.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMag);

    // unbind texture.
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
