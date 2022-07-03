//
// Created by denni on 28/06/2022.
//

#ifndef SHADERENTWICKLUNG_SPOTLIGHT_H
#define SHADERENTWICKLUNG_SPOTLIGHT_H

#include "PointLight.h"

class SpotLight : public PointLight{

public:
    SpotLight() {};

    SpotLight(float phi, glm::vec3 light_dir, glm::vec3 pos, glm::vec3 colour, glm::vec3 ambient, glm::vec3 spec) :
        phi(phi), light_direction(light_dir), PointLight(pos, colour, ambient, spec) {};

    bool bind(ShaderProgram& sp);

    void setFloat(const std::string& name, const GLfloat floatv, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        glUniform1f(vec_loc, floatv);
    }

private:
    float phi;  //cutoff, specifies radius

    //float spot_dir; ?

    float theta;    //theta, angle between lightdir and spotdir. should be inside phi. Calculated in shader

    glm::vec3 light_direction;
};


#endif //SHADERENTWICKLUNG_SPOTLIGHT_H
