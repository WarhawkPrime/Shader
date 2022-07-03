//
// Created by Warhawk on 15/06/2022.
//

#include "Camera.h"

bool Camera::bind(ShaderProgram& sp)
{
    this->setMat4("view_m", this->m_viewmatrix, sp);

    this->setMat4("projection_m", this->m_projectionmatrix, sp);

    this->setVec3("camPos", getPosition(), sp);

    return true;
}

void Camera::updateCameraVectors()
{
    //calculate new view vector
    glm::vec3 front;
    front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
    front.y = sin(glm::radians(PITCH));
    front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));

    v_viewVector = glm::normalize(front);

    std::cout << "Viewvector X: " << v_viewVector.x << std::endl;
    std::cout << "Viewvector Y: " << v_viewVector.y << std::endl;
    std::cout << "Viewvector Z: " << v_viewVector.z << std::endl;


    //regulate up and right vector
    v_right = glm::normalize(glm::cross(v_viewVector, v_upVector));
    v_upVector = glm::normalize(glm::cross(v_right, v_viewVector));
}

void Camera::handleMouseInput(float xoffset, float yoffset, GLboolean constrainPitch = true) {

    // Multiply with sensitivity
    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;

    // Add calculated offset to camera pitch and yaw
    yaw += xoffset;
    pitch += yoffset;

    /*
    // Set constraints so the camera can't move more than 180 degrees total in the vertical direction
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    */

    // Update Front, Right and Up vectors
    updateCameraVectors();
}


void Camera::handleKeyboardInput(CamDir dir, float delta_time)
{
    float v = SPEED * delta_time;

    if (dir == UP) {
        setPosition( getPosition() + (v_viewVector * v) );
        //Position += mView * v;
    }
    else if (dir == DOWN) {
        setPosition(getPosition() - (v_viewVector * v));
        //Position -= mView * v;
    }
    else if (dir == LEFT) {
        setPosition(getPosition() - glm::normalize(glm::cross(v_viewVector, v_upVector)) * v);
        //mPosition -= glm::normalize(glm::cross(mView, mUp)) * v;
    }
    else if (dir == RIGHT) {
        setPosition(getPosition() + glm::normalize(glm::cross(v_viewVector, v_upVector)) * v);
        //mPosition += glm::normalize(glm::cross(mView, mUp)) * v;
    }
}

