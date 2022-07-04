//
// Created by alex1 on 13.06.2022.
//
#include <Transform.h>
#include <ShaderProgram.h>
#ifndef SHADERENTWICKLUNG_CAMERA_H
#define SHADERENTWICKLUNG_CAMERA_H

#include <Transform.h>
#include <ShaderProgram.h>

#include "memory"


class Camera : public Transform {

public:

    Camera(){};

    Camera(float width, float height, float angle, float minDistance, float maxDistance) :
        width(width), height(height), angle(angle), minDistance(minDistance), maxDistance(maxDistance) {};

    //Camera(float width, float height, float angle, float minDistance, float maxDistance, Transform *target);

    Camera(float width, float height, float angle, float minDistance, float maxDistance, std::shared_ptr<Transform> target) :
        width(width), height(height), angle(angle), minDistance(minDistance), maxDistance(maxDistance), target(target) {};

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void bind(ShaderProgram* shaderProgram);
    virtual ~Camera();





private:
    float width, height,angle, minDistance, maxDistance;
    //Transform *target;

    std::shared_ptr<Transform> target;




};

#endif //SHADERENTWICKLUNG_CAMERA_H
