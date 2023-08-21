//
// Created by Dell on 2021/12/12.
//

#ifndef EXP_CAMERA_H
#define EXP_CAMERA_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float ROLL=0.0f;

class camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float Roll;


    camera(glm::vec3 position=glm::vec3(0.0f,0.0f,0.0f),glm::vec3 up=glm::vec3(0.0f,1.0f,0.0f),
                   float yaw = YAW,float pitch = PITCH,float roll=ROLL);
    camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void ProcessRoll(float zoffset);



private:
    void updateCameraVectors();
};


#endif //EXP_CAMERA_H
