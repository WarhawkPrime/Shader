//
// Created by alex1 on 20.06.2022.
//

#include "PointLight.h"


void PointLight::bind(ShaderProgram& shaderProgram) {


    setVec3("pointLight.position", this->getCombinedPosition(), shaderProgram  );

    setVec3("pointLight.diffuse", this->get_colour(), shaderProgram  );

    setVec3("pointLight.ambient", this->get_ambient(), shaderProgram  );

    setVec3("pointLight.specular", this->get_lightSpec(), shaderProgram  );


    setFloat("pointLight.constant", this->getConstant(), shaderProgram);

    setFloat("pointLight.linear", this->getLinear(), shaderProgram);

    setFloat("pointLight.quadratic", this->getQuadratic(), shaderProgram);


}


float PointLight::getConstant() const {
    return constant;
}

float PointLight::getLinear() const {
    return linear;
}

float PointLight::getQuadratic() const {
    return quadratic;
}
