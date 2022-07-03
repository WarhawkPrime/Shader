//
// Created by denni on 18/06/2022.
//

#ifndef SHADERENTWICKLUNG_POINTLIGHT_H
#define SHADERENTWICKLUNG_POINTLIGHT_H


#include <string>
#include <memory>
#include "Transform.h"
#include "ShaderProgram.h"
#include "Renderable.h"


class PointLight : public Transform {

public:
    PointLight() {}

    PointLight(glm::vec3 pos, glm::vec3 colour);

    //pos, diffuse,
    PointLight(glm::vec3 pos, glm::vec3 colour, glm::vec3 ambient, glm::vec3 spec);

    void setColour(glm::vec3 colour) {this->colour = colour;}
    glm::vec3 getColour() {return colour;}

    void setMat4(const std::string& name, const glm::mat4& mat, ShaderProgram& sp) const
    {
        GLint mat_loc = glGetUniformLocation(sp.prog, name.c_str());
        glUniformMatrix4fv( mat_loc, 1, GL_FALSE, &mat[0][0]);
    }


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


    bool bind(ShaderProgram& sp);

    void set_parent(std::shared_ptr<Renderable> &parent) {this->parent = parent;}
    void get_parent(std::shared_ptr<Renderable> &parent) {parent = this->parent;}

//protected:
public:
    glm::vec3 colour;//diffuse

    glm::vec3 ambient;
    glm::vec3 spec;

    std::shared_ptr<Renderable> parent;
};


#endif //SHADERENTWICKLUNG_POINTLIGHT_H
