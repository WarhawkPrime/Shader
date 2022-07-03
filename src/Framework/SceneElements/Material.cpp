//
// Created by denni on 29/06/2022.
//

#include "Material.h"




int Material::load_texture(GLuint &id, std::string path)
{
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

    return 0;
}