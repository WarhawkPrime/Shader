//
// Created by Benjamin Meyer on 25.12.2020.
//


#include "Texture2D.h"
Texture2D::Texture2D()
{}

Texture2D::Texture2D(const std::string & path, bool genMipMaps, GLuint id)
{
    /*
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    //============= �nderung f�r 2. Texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    //unsigned char* data = SOIL_load_image("resources/greymetal.jpg", &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        std::cout << "data is valid" << std::endl;

        //The crash problem is probably caused by glTexImage2D reading past the bounds of your data buffer.

        //glPixelStorei sets pixel storage modes that affect the operation of subsequent glReadPixels
        //as well as the unpacking of texture patterns (see glTexImage2D and glTexSubImage2D).

        //Specifies the alignment requirements for the start of each pixel row in memory. The allowable values are
        //1 (byte-alignment), 2 (rows aligned to even-numbered bytes), 4 (word-alignment), and 8 (rows start on double-word boundaries).
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to Texture" << std::endl;
    }

    stbi_image_free(data);
     */

    texid = id;


    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLsizei width;
    GLsizei height;
    GLsizei channels;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (image)
    {
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

    }


    /*
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

                std::cout << "RGB" << std::endl;

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

        glGenTextures(1, &texid); //GLERR //create ID

        if (texid == 0)
        {
            stbi_image_free(image);
            throw std::logic_error("OpenGL texture object creation failed.");
        }

        //glActiveTexture(1 );
        glBindTexture(GL_TEXTURE_2D, texid); //GLERR  //bind texture

        //target, name, value
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        //filtering:
        //when scaling down
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //when scaling up
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        glPixelStorei(GL_PACK_ALIGNMENT, 1);

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
        );                                      //define texture and send optional data

        if (checkglerror())
        {
            glDeleteTextures(1, &texid);
            stbi_image_free(image);
            throw std::logic_error("Error. Could not buffer texture data.");
        }
        if (genMipMaps)
            glGenerateMipmap(GL_TEXTURE_2D); //GLERR
        */

        //============================
        //wrapping:



        //============================


        //free bind
            //glBindTexture(GL_TEXTURE_2D, 0); GLERR

            stbi_image_free(image);





}

bool Texture2D::bind(ShaderProgram &sp, std::string uni_name, GLuint texture_unit)
{
    std::cout << "bind" << std::endl;
    //Über getFreeTU() bekommen Sie die
    //nächste freie TU, der Aufruf von shader->use() zu Beginn jedes Rendercalls setzt den Counter wieder
    //auf 0 zurück.




    //maxTextureUnits() liefert zudem die maximale Anzahl an zur Verfügung stehenden TUs.
    //Holen Sie sich also die nächste freie TU, aktivieren Sie diese über glActiveTexture() und binden Sie
    //die Textur anhand der TexturID mit glBindTexture()

    //select active texture unit (GL_TEXTURE0 + active_texture Unit)

    std::cout << "activate texture Unit: " << texture_unit << std::endl;


    glActiveTexture(texture_unit); GLERR



    //bind a named texture to a texturing target: target, texture(int, return of glGenTextures)
    //glBindTexture(GL_TEXTURE_2D, freeTex);

        //glGetError();
    glBindTexture(GL_TEXTURE_2D, this->texid);




    //Setzen Sie dann den Wert des sampler2D im
    //Shader, wie gewohnt mittels setUniform()

    //name of texture uniform in shader, TextureUnit (not ID!), shaderprogram
    //setInt("",freeTex, sp );

    //setInt(uni_name, texture_unit, sp);



    //. Setzen Sie daher am Ende der bind() des
    //Meshes die aktuelle TU des Shaderprogramms auf den Wert zu Beginn des bind() (den Sie sich vorher
    //speichern müssen) zurück

    //unbind
    //sp.resetTU(oldTU);

    return true;
}


void Texture2D::load_texture(const std::string &path, GLuint &txid)
{
    glGenTextures(1, & txid );
    glBindTexture(GL_TEXTURE_2D, txid);

    //============= �nderung f�r 2. Texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    //unsigned char* data = SOIL_load_image("resources/greymetal.jpg", &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        std::cout << "data is valid" << std::endl;

        //The crash problem is probably caused by glTexImage2D reading past the bounds of your data buffer.

        //glPixelStorei sets pixel storage modes that affect the operation of subsequent glReadPixels
        //as well as the unpacking of texture patterns (see glTexImage2D and glTexSubImage2D).

        //Specifies the alignment requirements for the start of each pixel row in memory. The allowable values are
        //1 (byte-alignment), 2 (rows aligned to even-numbered bytes), 4 (word-alignment), and 8 (rows start on double-word boundaries).
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to Texture" << std::endl;
    }

    stbi_image_free(data);
}





/*
bool Texture2D::parameterise()
{
    //Sie müssen
    //sowohl Filtering- als auch Wrapping-Parameter setzen, mittels glTexParameteri(). Binden Sie vorher
    //die entsprechende Textur und unbinden Sie sie danach!

    //wrapping:

    //target, name, value
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    //filtering:
        //when scaling down
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //when scaling up
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}
*/