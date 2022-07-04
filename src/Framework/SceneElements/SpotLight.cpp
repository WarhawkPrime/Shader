#include "SpotLight.h"

/*
SpotLight::SpotLight(const glm::vec3 &pos, const glm::vec3 &lightColor, const glm::vec3 Dir, float innerCone,
                     float outerCone, float c, float l , float q) : PointLight(pos,lightColor,c,l,q) {
    this->direction = Dir;
    this->innerCone = innerCone;
    this->outerCone = outerCone;


}
*/

/*
void SpotLight::setInnerCone(float innerCone) {
    SpotLight::innerCone = innerCone;
}

void SpotLight::setOuterCone(float outerCone) {
    SpotLight::outerCone = outerCone;
}
*/

const glm::vec3 &SpotLight::getSpotlightDirection() const {
    return direction;
}

void SpotLight::setDirection(const glm::vec3 &direction) {
    SpotLight::direction = direction;
}

void SpotLight::bind(ShaderProgram& shaderProgram)
{

    setVec3("spotLight.position", this->getCombinedPosition(), shaderProgram  );

    setVec3("spotLight.diffuse", this->get_colour(), shaderProgram  );

    setVec3("spotLight.ambient", this->get_ambient(), shaderProgram  );

    setVec3("spotLight.specular", this->get_lightSpec(), shaderProgram  );


    setFloat("spotLight.constant", this->getConstant(), shaderProgram);

    setFloat("spotLight.linear", this->getLinear(), shaderProgram);

    setFloat("spotLight.quadratic", this->getQuadratic(), shaderProgram);


    this->setVec3("spotLight.direction", this->getSpotlightDirection(), shaderProgram);
    this->setFloat("spotLight.cutOff", glm::cos(glm::radians(this->innerCone)), shaderProgram);
    this->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(this->outerCone)), shaderProgram);
}
