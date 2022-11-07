#pragma once

#include "renderer.hpp"
#include "GLFW/glfw3.h"

class Controller {
	Controller(GLFWwindow* win);
	Controller(GLFWwindow* win, Renderer::Camera cam);

	protected:
		Renderer::Camera cam;
};
