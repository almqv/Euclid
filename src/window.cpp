#include "window.hpp"
#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <cstdlib>
#include <stdio.h>

std::map<GLFWwindow*, Window*> Window::windowMap;

Window::Window(const char* title) {
	this->_title = title;
}

Window::Window(const char* title, unsigned int w, unsigned int h) : Window(title) {
	this->_width = w;
	this->_height = h;
}

Window::~Window() {
	glfwDestroyWindow(_win);
	windowMap.erase(_win);
}

void Window::spawn() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_FLOATING, GL_TRUE);

	_win = glfwCreateWindow(_width, _height, _title, NULL, NULL);
	if (_win == NULL) {
		printf("[ERROR] Failed to create a window.\n");
		glfwTerminate();
		exit(1);
	}

	// Register window in the std::map
	windowMap[_win] = this;

	glfwSetFramebufferSizeCallback(_win, framebufferSizeCallback);
	glfwMakeContextCurrent(_win);
}

void Window::updateSize(int w, int h) {
	_width = w;
	_height = h;
	glViewport(0, 0, w, h);
}

void Window::makeCurrent() {
	glfwMakeContextCurrent(_win);
}

void Window::swapBuffers() {
	glfwSwapBuffers(_win);
}

void Window::framebufferSizeCallback(GLFWwindow* win, int width, int height) {
	windowMap[win]->updateSize(width, height);
}
