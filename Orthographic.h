#pragma once
#include "Camera.h"
#include <cstdio>

class Orthographic :
    public Camera
{
public:
    glm::mat4 projection;

    Orthographic(glm::vec3 position, glm::vec3 up, glm::vec3 front, float left, float right, float bottom, float top, float zNear, float zFar) :Camera(position, up, front) {
        projection = glm::ortho(left,right,bottom,top, zNear, zFar);
    }

    glm::mat4 getProjection() {
        return projection;
    }

    glm::mat4 getView() {
        return view;
    }

    void orthorecalViewMatrix() {
        view = glm::lookAt(cameraPos, cameraFront, cameraUp);
    }

};
