//
// Created by denni on 29/06/2022.
//

#include "Texture2D.h"

#ifndef SHADERENTWICKLUNG_MATERIAL_H
#define SHADERENTWICKLUNG_MATERIAL_H


class Material {

public:
    Material(){}

    Material(Texture2D tex_diff, Texture2D tex_emi, Texture2D tex_spec, GLfloat shini, GLfloat multi) :
        texture_diffuse(tex_diff), texture_emissive(tex_emi), texture_specular(tex_spec),
        shininess(shini) {}

    Material(GLuint diff_id, GLuint emi_id, GLuint spe_id, GLfloat shini, GLfloat multi) :
        diffuse_id(diff_id), emissive_id(emi_id), spec_id(shini), shininess(shini), texMulti(multi) {}

    Material(GLfloat shini, GLfloat multi) :
        shininess(shini), texMulti(multi) {}


    int load_texture(GLuint &id, std::string path);

    Texture2D texture_diffuse;
    Texture2D texture_emissive;
    Texture2D texture_specular;

    GLuint diffuse_id;
    GLuint emissive_id;
    GLuint spec_id;



    GLfloat shininess;
    GLfloat texMulti;

private:

};


#endif //SHADERENTWICKLUNG_MATERIAL_H
