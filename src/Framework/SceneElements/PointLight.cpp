//
// Created by denni on 18/06/2022.
//

#include "PointLight.h"

PointLight::PointLight(glm::vec3 pos, glm::vec3 colour)
{
    setPosition(pos);
    this->colour = colour;
}

PointLight::PointLight(glm::vec3 pos, glm::vec3 colour, glm::vec3 ambient, glm::vec3 spec)
{
    setPosition(pos);
    this->colour = colour;
    this->ambient = ambient;
    this->spec = spec;
}

bool PointLight::bind(ShaderProgram& sp)
{
    /*
    this->setVec3("lightpos_v", getPosition(), sp );

    this->setVec3("lightcolour_v", colour, sp );

    //extra
    this->setVec3("light_amb", ambient, sp);
    this->setVec3("light_spec", spec, sp);
     */

    //fill struct Point
    // Lightstruct PointLight {
    //    vec3 position;
    //
    //    float constant;
    //    float linear;
    //    float quadratic;
    //
    //    vec3 ambient;
    //    vec3 diffuse;
    //    vec3 specular;
    //};

    //uniform PointLight pointLight;

    this->setVec3("pointLight.position", getPosition(), sp);
    this->setVec3("pointLight.ambient", ambient, sp);
    this->setVec3("pointLight.diffuse", colour, sp);
    this->setVec3("pointLight.specular", spec, sp);

    this->setFloat("pointLight.constant", 1.0f, sp);
    this->setFloat("pointLight.linear", 0.09f, sp);
    this->setFloat("pointLight.quadratic", 0.032f, sp);


    return true;
}