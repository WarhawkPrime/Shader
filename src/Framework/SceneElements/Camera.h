//
// Created by denni on 15/06/2022.
//

#ifndef SHADERENTWICKLUNG_CAMERA_H
#define SHADERENTWICKLUNG_CAMERA_H

#include <string>
#include <memory>
#include "Transform.h"
#include "ShaderProgram.h"
#include "Renderable.h"

enum CamDir
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};


const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 3.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera : public Transform{

public:
    Camera(){}

    Camera(GLfloat width, GLfloat height, GLfloat opening_angle, GLfloat min_distance, GLfloat max_distance)
    : width(width), height(height), opening_angle(opening_angle), min_distance(min_distance), max_distance(max_distance)
    {
        yaw = -90.0f;
        pitch = 0.0f;
    }

    void init(glm::vec3 pos, glm::vec3 up )
    {
        this->setPosition(pos);
        this->v_upVector = up;

        updateCameraVectors();
    }

    void setViewVector(glm::vec3 view_m) {this->v_viewVector = view_m;}
    glm::vec3 getViewVector() {return v_viewVector;}

    void setUpVector(glm::vec3 up) {this->v_upVector = up;}
    glm::vec3 getUpVector() {return v_upVector;}

    void setViewMatrix(glm::mat4 viewM) {this->m_viewmatrix = viewM;}
    glm::mat4 getViewMatrix() {return m_viewmatrix;}

    void setProjectionMatrix(glm::mat4 projectionM) {this->m_projectionmatrix;}
    glm::mat4 getProjectionMatrix() {return m_projectionmatrix;}

    //c_up or up_vector
    void calcViewMatrix() {
        this->m_viewmatrix = glm::lookAt(this->getPosition(), this->getPosition() + v_viewVector, v_upVector );
    }

    void calcProjectionMatrix() {
        this->m_projectionmatrix = glm::perspective(glm::radians(opening_angle), width/height, min_distance, max_distance);
    }

    void setPitch(float p) {this->pitch = p;}
    float getPitch() {return this->pitch;}
    void setYaw(float y) {this->yaw = y;}
    float getYaw() {return this->yaw;}

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

    bool bind(ShaderProgram& sp);

    /*
    glm::vec3 v_direction;
    glm::vec3 v_right;
    glm::vec3 c_up;
    */
    glm::vec3 v_right;

    //input handling
    void handleMouseInput(float xoffset, float yoffset, GLboolean constrainPitch);
    void handleKeyboardInput(CamDir, float delta_time);

    void set_parent(std::shared_ptr<Renderable> &parent) {this->parent = parent;}
    void get_parent(std::shared_ptr<Renderable> &parent) {parent = this->parent;}


private:

    GLfloat width;
    GLfloat height;
    GLfloat opening_angle;
    GLfloat min_distance;
    GLfloat max_distance;

    glm::vec3 v_viewVector;
    glm::vec3 v_upVector;

    float pitch;
    float yaw;
    float mouseSensitivity;

    glm::mat4 m_viewmatrix;
    glm::mat4 m_projectionmatrix;   //use perspektivische Projektion

    void updateCameraVectors();


    std::shared_ptr<Renderable> parent;
};


#endif //SHADERENTWICKLUNG_CAMERA_H
