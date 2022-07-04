//
// Created by alex1 on 13.06.2022.
//

#include "Camera.h"

glm::mat4 Camera::getViewMatrix() {

    glm::vec3 pos = getPosition();

    if (target != nullptr) {
        if (this->getParent() != nullptr) {
            pos = pos + this->getParent()->getPosition();
        }
        glm::vec3 targetPos = target->getPosition();
        return glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), targetPos, getYAxis());
    } else {
        return glm::inverse(getMatrix());
    }

}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(angle, (width / height), minDistance, maxDistance);
}

void Camera::bind(ShaderProgram* shaderProgram) {

    shaderProgram->setUniform("view_m", getViewMatrix(), false);
    shaderProgram->setUniform("projection_m", getProjectionMatrix(), false);

    shaderProgram->setUniform("camPos", getPosition());
}

/*
Camera::Camera(float width, float height, float angle, float minDistance, float maxDistance) {

    this->width = width;
    this->height = height;
    this->angle = angle;
    this->minDistance = minDistance;
    this->maxDistance = maxDistance;
    this->target = this;
}
*/

/*
Camera::Camera(float width, float height, float angle, float minDistance, float maxDistance, Transform *target) {
    this->width = width;
    this->height = height;
    this->angle = angle;
    this->minDistance = minDistance;
    this->maxDistance = maxDistance;
    this->target = target;
}
*/


Camera::~Camera() {
    std::cout << "camera off" << std::endl;
}
