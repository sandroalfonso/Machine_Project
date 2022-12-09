#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/string_cast.hpp>

class Camera
{
public:
	//Initialize Camera Views
	glm::vec3 cameraPos;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;

	//View Matrix
	glm::mat4 view;

	Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front) {
		cameraPos = position;
		cameraUp = up;
		cameraFront = front;
		view = glm::lookAt(cameraPos, cameraFront, cameraUp);
	}

	//Create Getters
	glm::vec3 getCameraPos() {
		return cameraPos;
	}

	glm::vec3 getCameraUp() {
		return cameraUp;
	}

	void setCameraPos(glm::vec3 pos) {
		cameraPos = pos;
	}

	glm::vec3 getCameraFront() {
		return cameraFront;
	}

	glm::mat4 getView() {
		return view;
	}

};
