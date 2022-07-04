//
// Created by Benjamin Meyer on 25.12.2020.
//


#include "Texture2D.h"
Texture2D::Texture2D()
{}

Texture2D::Texture2D(const std::string & path, bool genMipMaps)
{
    GLsizei width;
    GLsizei height;
    GLsizei channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (image == nullptr)
    {
        throw std::logic_error("Texture file coudn't be read.");
    }
    else
    {
        GLint internalformat;
        GLenum format;
        switch (channels)
        {
            case 1:
                internalformat = GL_R8;
                format = GL_RED;
                break;
            case 2:
                internalformat = GL_RG8;
                format = GL_RG;
                break;
            case 3:
                internalformat = GL_RGB8;
                format = GL_RGB;
                break;
            case 4:
                internalformat = GL_RGBA8;
                format = GL_RGBA;
                break;
            default:
                internalformat = GL_RGB8;
                format = GL_RGB;
                break;
        }
        glGenTextures(1, &texid); GLERR
        if (texid == 0)
        {
            stbi_image_free(image);
            throw std::logic_error("OpenGL texture object creation failed.");
        }
        glBindTexture(GL_TEXTURE_2D, texid); GLERR
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                internalformat,
                width,
                height,
                0,
                format,
                GL_UNSIGNED_BYTE,
                image
        );
        if (checkglerror())
        {
            glDeleteTextures(1, &texid);
            stbi_image_free(image);
            throw std::logic_error("Error. Could not buffer texture data.");
        }
        if (genMipMaps)
            glGenerateMipmap(GL_TEXTURE_2D); GLERR
        glBindTexture(GL_TEXTURE_2D, 0); GLERR
        stbi_image_free(image);
    }
}