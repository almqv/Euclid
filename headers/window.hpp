#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <map>

// Default window dimensions
#define D_WINDOW_TITLE "Euclid Engine"

#define D_WINDOW_WIDTH 640
#define D_WINDOW_HEIGHT 480

class Window {
	public:
		Window(const char* title);
		Window(const char* title, unsigned int w, unsigned int h);

		~Window();

		void spawn();

		unsigned int getWidth()  { return _width; }  // getters and dumb and
		unsigned int getHeight() { return _height; } // cpp should have readonly fields...
		GLFWwindow* getWindow()  { return _win; }

		void updateSize(int w, int h);
		void makeCurrent();
		void swapBuffers();
		bool shouldClose();
	private:
		GLFWwindow* _win;
		static std::map<GLFWwindow*, Window*> windowMap;

		const char* _title = D_WINDOW_TITLE;
		unsigned int _width = D_WINDOW_WIDTH;
		unsigned int _height = D_WINDOW_HEIGHT;

		void setWidth(unsigned int w)  { _width = w; }
		void setHeight(unsigned int h) { _height = h; }

		static void framebufferSizeCallback(GLFWwindow* win, int width, int height);
};
