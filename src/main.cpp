#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <vector>
#include <math.h>

#include "controller.hpp"
#include "renderer.hpp"
#include "window.hpp"

#define RUSTY_METAL_TEXTURE "assets/textures/rusty_metal.jpg"

std::vector<float> verts({
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,


	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,


	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,


	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,


	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,


	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
});
// Vert struc: x y z  r g b  tx ty  lnx lny lnz

std::vector<unsigned int> indices({
	0, 1, 3,
	1, 2, 3,
	5, 6, 7,
	7, 8, 9,
	9, 10, 11,
	11, 12, 13,
	0, 1, 3,
	3, 4, 5,
	5, 6, 7,
	7, 8, 9,
	9, 10, 11,
	11, 12, 13,
	0, 1, 3,
	3, 4, 5,
	5, 6, 7,
	7, 8, 9,
	9, 10, 11,
	11, 12, 13,
	0, 1, 3,
	3, 4, 5,
	5, 6, 7,
	7, 8, 9,
	9, 10, 11,
	11, 12, 13,
	0, 1, 3,
	3, 4, 5,
	5, 6, 7,
	7, 8, 9,
	9, 10, 11,
	11, 12, 13,
});


// Window for the game
void processInput(GLFWwindow *win) {
	int action = glfwGetKey(win, GLFW_KEY_ESCAPE);
	if (action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, true);
	}
}

int main() {
	// Spawn window
	Window win("Euclid Engine: Demo");

	win.spawn();

	if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
		printf("Failed to init GLAD.\n");
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Input
	glfwSetInputMode(win.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Disable cursor

	float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Create scene
	Renderer::Scene scene(&win);

	// Should have the default metal texture
	Renderer::TexturedObject ro(verts, indices);

	// Should be the same as ro but with a smiley
	Renderer::TexturedObject ro2(verts, indices);

	// Should not have a texture
	Renderer::RenderObject cringe(verts, indices);
	cringe.setPosition(glm::vec3(2.0, 1.0, 0.0));

	ro2.setTexture("assets/textures/meep.jpg"); // TODO: fix texture bug
	ro.setTexture(RUSTY_METAL_TEXTURE);

	scene.spawnObject(&ro);
	scene.spawnObject(&ro2);
	scene.spawnObject(&cringe);

	// Controller test
	Controller player(&win, glm::vec3(0.0f, 0.0f, 8.0f));
	scene.setCamera(&player);

	while (!win.shouldClose()) {
		// Handle input
		player.processInput(scene.deltaTime);
		processInput(win.getWindow());

		ro.translate(glm::vec3(0.0f, 0.0f, 0.001f));
		ro2.rotate(glm::vec3(1.01f, 1.0f, 1.0f));

		// Render new frame
		scene.render();

		// glfw
		win.swapBuffers();
		glfwPollEvents();
	}

	return 0;
}
