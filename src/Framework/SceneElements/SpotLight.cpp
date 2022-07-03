//
// Created by denni on 28/06/2022.
//

#include "SpotLight.h"
bool SpotLight::bind(ShaderProgram& sp)
{
    /*
    this->setVec3("lightpos_spot", getPosition(), sp );

    this->setVec3("lightcolour_spot", colour, sp );

    //extra
    this->setVec3("light_amb_spot", ambient, sp);
    this->setVec3("light_spec_spot", spec, sp);

    this->setFloat("cutOff_spot", glm::cos(glm::radians(phi)), sp);

    this->setVec3("lightDir_spot", light_direction, sp);
    */

    //fill spotLight struct
    // struct SpotLight {
    //    vec3 position;
    //    vec3 direction;
    //    float cutOff;
    //    float outerCutOff;
    //
    //    float constant;
    //    float linear;
    //    float quadratic;
    //
    //    vec3 ambient;
    //    vec3 diffuse;
    //    vec3 specular;
    //};

    //uniform SpotLight spotLight;

    this->setVec3("spotLight.position", getPosition(), sp);
    this->setVec3("spotLight.ambient", ambient, sp);
    this->setVec3("spotLight.diffuse", colour, sp);
    this->setVec3("spotLight.specular", spec, sp);

    this->setFloat("pointLight.constant", 1.0f, sp);
    this->setFloat("pointLight.linear", 0.09f, sp);
    this->setFloat("pointLight.quadratic", 0.032f, sp);

    this->setVec3("spotLight.direction", light_direction, sp);
    this->setFloat("pointLight.cutOff", glm::cos(glm::radians(12.5f)), sp);               //TODO: phi
    this->setFloat("pointLight.outerCutOff", glm::cos(glm::radians(15.0f)), sp);        //TODO: theta


    return true;
}