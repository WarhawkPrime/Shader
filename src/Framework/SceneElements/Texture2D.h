//
// Created by Benjamin Meyer on 25.12.2020.
//

#ifndef CGA218_TEXTURE2D_H
#define CGA218_TEXTURE2D_H

#include <libheaders.h>
#include <glerror.h>
#include "ShaderProgram.h"

//Aufgrund von nicht-lösbaren Fehlern wurde die Klasse Texture2D nicht genutzt, die selbe Funktionalität wurde auf
// die Klasse Material verschoben.

class Texture2D {
private:

    GLuint texid = 0;

public:

    Texture2D();
    Texture2D(const std::string & path, bool genMipMaps);


    inline GLint maxTextureUnits()
    {
        static GLint mtu = -1;
        if (mtu == -1)
        {
            glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &mtu);
        }
        return mtu;
    }
};

#endif //CGA218_TEXTURE2D_H
