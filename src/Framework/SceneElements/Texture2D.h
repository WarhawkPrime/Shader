//
// Created by Benjamin Meyer on 25.12.2020.
//

#ifndef CGA218_TEXTURE2D_H
#define CGA218_TEXTURE2D_H

#include <libheaders.h>
#include <glerror.h>
#include "ShaderProgram.h"


class Texture2D {
private:

    GLuint texid = 0;

public:

    Texture2D();
    Texture2D(const std::string & path, bool genMipMaps, GLuint id);



    void load_texture(const std::string & path, GLuint &txid);



    inline GLint maxTextureUnits()
    {
        static GLint mtu = -1;
        if (mtu == -1)
        {
            glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &mtu);
        }
        return mtu;
    }

    void setInt(const std::string& name, const GLuint gluintv, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        if ( vec_loc == -1) {
            std::cout << "uniform not set in shader" << std::endl;
        }

        glUniform1f(vec_loc, gluintv);
    }

    //TODO: Was jedoch noch fehlt, ist eine Methode zum binden der Textur,
    // also Hochladen des entsprechenden Wertes an den Fragment-Shader
    bool bind(ShaderProgram &sp, std::string uni_name, GLuint texture_unit);

    //TODO: Vergessen Sie nicht, eine weitere Methode zu schreiben, um die Textur zu parametrisieren
        //bool parameterise();

    //TODO: unbind coorect?

    //. Setzen Sie daher am Ende der bind() des
    //Meshes die aktuelle TU des Shaderprogramms auf den Wert zu Beginn des bind()
    // (den Sie sich vorher
    //speichern müssen) zurück. So
    // 'löschen' Sie die Zuordnung der für dieses Mesh benötigten Texturen zu
    //den TUs, erhalten aber etwaige Voreinstellungen
    // (falls beispielsweise die Lichtquelle auch mit einer LichtTextur ausgestattet war).


        //GLuint get_Tex_ID() const {return texid;}

};





#endif //CGA218_TEXTURE2D_H
