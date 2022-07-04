#ifndef SHADERENTWICKLUNG_SPOTLIGHT_H
#define SHADERENTWICKLUNG_SPOTLIGHT_H
#include "PointLight.h"

class SpotLight : public PointLight {
public:

    SpotLight(const glm::vec3 pos, const glm::vec3 lightColor,  const glm::vec3 lightAmbient, glm::vec3 lightSpec, const glm::vec3 Dir, float innerCone, float outerCone, float c, float l , float q)
        : direction(Dir), innerCone(innerCone), outerCone(outerCone), PointLight(pos, lightColor, lightAmbient, lightSpec, c, l, q) {}


    void bind(ShaderProgram& shaderProgram);

    //void setInnerCone(float innerCone);

    //void setOuterCone(float outerCone);

    const glm::vec3 &getSpotlightDirection() const;

    void setDirection(const glm::vec3 &direction);

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

private:
    glm::vec3 direction;
    float innerCone;
    float outerCone;

};


#endif //SHADERENTWICKLUNG_SPOTLIGHT_H