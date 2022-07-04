//
// Created by denni on 29/06/2022.
//

#include "Texture2D.h"

#ifndef SHADERENTWICKLUNG_MATERIAL_H
#define SHADERENTWICKLUNG_MATERIAL_H


class Material {

public:
    Material(){}

    Material(GLuint diff_id, GLuint emi_id, GLuint spe_id, GLfloat shini, GLfloat multi) :
        diffuse_id(diff_id), emissive_id(emi_id), spec_id(shini), shininess(shini), texMulti(multi) {}

    Material(GLfloat shini, GLfloat multi) :
        shininess(shini), texMulti(multi) {}


    int load_texture(GLuint &id, std::string path);

    GLuint diffuse_id;
    GLuint emissive_id;
    GLuint spec_id;


    GLfloat shininess;
    GLfloat texMulti;

private:

};


#endif //SHADERENTWICKLUNG_MATERIAL_H
