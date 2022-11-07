#pragma once

#include "glm/fwd.hpp"
#include "renderer.hpp"
#include "GLFW/glfw3.h"

#define CAM_MAX_ANGLE 89.99f

class Controller : public Renderer::Camera {
	public:
		using Renderer::Camera::Camera;

		float sensitivity = 0.04f;

		void processInput(float deltaTime);

	private:
		float pitch, yaw;
		double lastX, lastY;
		bool firstMouseInput = true;

		void processMouseInput(float deltaTime);
};
