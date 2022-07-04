#include "SpotLight.h"

/*
SpotLight::SpotLight(const glm::vec3 &pos, const glm::vec3 &lightColor, const glm::vec3 Dir, float innerCone,
                     float outerCone, float c, float l , float q) : PointLight(pos,lightColor,c,l,q) {
    this->direction = Dir;
    this->innerCone = innerCone;
    this->outerCone = outerCone;


}
*/


void SpotLight::setInnerCone(float innerCone) {
    SpotLight::innerCone = innerCone;
}



void SpotLight::setOuterCone(float outerCone) {
    SpotLight::outerCone = outerCone;
}

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

    /*
    this->setVec3("spotLight.position", getPosition(), shaderProgram);
    this->setVec3("spotLight.ambient", ambient, shaderProgram);
    this->setVec3("spotLight.diffuse", colour, shaderProgram);
    this->setVec3("spotLight.specular", spec, shaderProgram);

    this->setFloat("pointLight.constant", 1.0f, shaderProgram);
    this->setFloat("pointLight.linear", 0.09f, shaderProgram);
    this->setFloat("pointLight.quadratic", 0.032f, shaderProgram);
    */

    this->setVec3("spotLight.direction", this->getSpotlightDirection(), shaderProgram);
    this->setFloat("spotLight.cutOff", glm::cos(glm::radians(this->innerCone)), shaderProgram);               //TODO: phi
    this->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(this->outerCone)), shaderProgram);        //TODO: theta
    

    /*
    GLint light_pos_loc = glGetUniformLocation(shaderProgram->prog, "lightPosSpot");
    glProgramUniform3fv(shaderProgram->prog, light_pos_loc, 1, &this->getCombinedPosition()[0]);


    GLint light_col_loc = glGetUniformLocation(shaderProgram->prog, "lightColorSpot");
    glProgramUniform3fv(shaderProgram->prog, light_col_loc, 1, &this->getColor()[0]);

    GLint SpotDirection = glGetUniformLocation(shaderProgram->prog, "SpotDirection");
    glProgramUniform3fv(shaderProgram->prog, SpotDirection, 1, &this->getSpotlightDirection()[0]);


    GLint innerCone = glGetUniformLocation(shaderProgram->prog, "innerCone");
    glProgramUniform1f(shaderProgram->prog, innerCone, this->innerCone);
    GLint outerCone = glGetUniformLocation(shaderProgram->prog, "outerCone");
    glProgramUniform1f(shaderProgram->prog, outerCone, this->outerCone);


    GLint c = glGetUniformLocation(shaderProgram->prog, "constantSpot");
    glProgramUniform1f(shaderProgram->prog, c, this->getConstant());
    GLint l = glGetUniformLocation(shaderProgram->prog, "linearSpot");
    glProgramUniform1f(shaderProgram->prog, l, this->getLinear());
    GLint q = glGetUniformLocation(shaderProgram->prog, "quadraticSpot");
    glProgramUniform1f(shaderProgram->prog, q, this->getQuadratic());
     */
}
