#include "controller.hpp"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "renderer.hpp"
#include <cmath>
#include <cstdio>

void Controller::processMouseInput(float deltaTime) {
	double x, y;
	glfwGetCursorPos(window->win, &x, &y); 	

	if (firstMouseInput) {
		lastX = x;
		lastY = y;
		firstMouseInput = false;
	}	

	float xOffset = x - lastX; 
	float yOffset = y - lastY;
	lastX = x;
	lastY = y;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	// Clamp camera values
	pitch = glm::clamp(pitch, -CAM_MAX_ANGLE, CAM_MAX_ANGLE);
	// yaw = glm::clamp(yaw, -CAM_MAX_ANGLE, CAM_MAX_ANGLE);
	yaw = std::fmod(yaw, 360.0f);

	// Update the front vector
	glm::vec3 dir;
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(-pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(dir);

	updateCameraTransforms();

	printf("%f %f %f (pitch: %f yaw: %f)\n", position.x, position.y, position.z, pitch, yaw);
}  

void Controller::processInput(float deltaTime) {
	processMouseInput(deltaTime);

	float cameraSpeed = deltaTime * 2.5f; 

	if (glfwGetKey(window->win, GLFW_KEY_W) == GLFW_PRESS) {
		translate(cameraSpeed * front);
	}
	if (glfwGetKey(window->win, GLFW_KEY_S) == GLFW_PRESS) {
		translate(-cameraSpeed * front);
	}
	if (glfwGetKey(window->win, GLFW_KEY_A) == GLFW_PRESS) {
		translate(-glm::normalize(glm::cross(front, up)) * cameraSpeed);
	}
	if (glfwGetKey(window->win, GLFW_KEY_D) == GLFW_PRESS) {
		translate(glm::normalize(glm::cross(front, up)) * cameraSpeed);
	}
	if (glfwGetKey(window->win, GLFW_KEY_SPACE) == GLFW_PRESS) {
		translate(cameraSpeed * up);
	}
	if (glfwGetKey(window->win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		translate(cameraSpeed * -up);
	}
}
