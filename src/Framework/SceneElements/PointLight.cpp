//
// Created by alex1 on 20.06.2022.
//

#include "PointLight.h"

/*
PointLight::PointLight(const glm::vec3& pos, const glm::vec3& lightColor, float c, float l, float q) : Transform(pos, glm::quat(0, 0, 0, 0), glm::vec3(1)) {

    LightPos = pos;
    this->lightColor = lightColor;
    constant = c;
    linear = l;
    quadratic = q;

}
*/

void PointLight::bind(ShaderProgram& shaderProgram) {


    setVec3("pointLight.position", this->getCombinedPosition(), shaderProgram  );

    setVec3("pointLight.diffuse", this->get_colour(), shaderProgram  );

    setVec3("pointLight.ambient", this->get_ambient(), shaderProgram  );

    setVec3("pointLight.specular", this->get_lightSpec(), shaderProgram  );


    setFloat("pointLight.constant", this->getConstant(), shaderProgram);

    setFloat("pointLight.linear", this->getLinear(), shaderProgram);

    setFloat("pointLight.quadratic", this->getQuadratic(), shaderProgram);


}

/*
const glm::vec3 &PointLight::getColor() const {
    return lightColor;
}
 */

float PointLight::getConstant() const {
    return constant;
}

float PointLight::getLinear() const {
    return linear;
}

float PointLight::getQuadratic() const {
    return quadratic;
}
