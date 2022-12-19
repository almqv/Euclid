#include "window.hpp"
#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <cstdlib>
#include <stdio.h>

Window::Window(const char* title) {
	this->_title = title;
}

Window::Window(const char* title, unsigned int w, unsigned int h) : Window(title) {
	this->_width = w;
	this->_height = h;
}

void Window::spawn() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_FLOATING, GL_TRUE);

	win = glfwCreateWindow(_width, _height, _title, NULL, NULL);
	if (win == NULL) {
		printf("[ERROR] Failed to create a window.\n");
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(win);
}

void Window::updateSize(int w, int h) {
	_width = w;
	_height = h;
	glViewport(0, 0, w, h);
}
