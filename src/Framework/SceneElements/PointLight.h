//
// Created by alex1 on 20.06.2022.
//

#ifndef SHADERENTWICKLUNG_POINTLIGHT_H
#define SHADERENTWICKLUNG_POINTLIGHT_H


#include "Transform.h"
#include "ShaderProgram.h"

class PointLight  : public Transform{

public:
    //PointLight(const glm::vec3& pos, const glm::vec3& lightColor, float c, float l , float q);


    PointLight(const glm::vec3 pos, const glm::vec3 lightColor, const glm::vec3 lightAmbient, glm::vec3 lightSpec ,float c, float l , float q)
        : lightPos(pos), lightColor(lightColor), lightAmbient(lightAmbient), lightSpec(lightSpec), constant(c), linear(l), quadratic(q) {}


    void bind(ShaderProgram& shaderProgram);
    //const glm::vec3 &getColor() const;

    const glm::vec3 get_colour() {return lightColor;}
    const glm::vec3 get_ambient() {return lightAmbient;}
    const glm::vec3 get_lightSpec() {return lightSpec;}

    void setVec3(const std::string& name, const glm::vec3& vec, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        glUniform3fv(vec_loc, 1, glm::value_ptr(vec));
    }

    void setFloat(const std::string& name, const GLfloat floatv, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        glUniform1f(vec_loc, floatv);
    }

    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;


private:
    glm::vec3 lightPos;
    glm::vec3 lightColor;

    glm::vec3 lightAmbient;
    glm::vec3 lightSpec;

    float constant;
    float linear;
    float quadratic;
};
#endif //SHADERENTWICKLUNG_POINTLIGHT_H