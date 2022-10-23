#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <math.h>

#include "../headers/shaders.hpp"
#include "../headers/textures.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define VERT_SHADER_SRC_FILE "shaders/vertex.glsl"
#define FRAG_SHADER_SRC_FILE "shaders/fragment.glsl"

#define RUSTY_METAL_TEXTURE "assets/textures/rusty_metal.jpg"

void framebuffer_size_callback(GLFWwindow* win, int w, int h) {
	glViewport(0, 0, w, h);
}

void processInput(GLFWwindow *win) {
	int action = glfwGetKey(win, GLFW_KEY_ESCAPE);
	if (action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, true);
	}
}

struct RenderObj {
	unsigned int EBO;
	Shaders::Shader shader;
	Textures::Texture2D texture;
};

RenderObj preRenderCallback(unsigned int indices[], unsigned int indices_count, float verts[], unsigned int verts_count) {
	// Vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // gen the VAO
	glBindVertexArray(VAO); // bind it

	// Copy verts into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts_count, verts, GL_DYNAMIC_DRAW); // for moving stuff
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count, indices, GL_STATIC_DRAW);

	// Set attrib pointers
	#define VERTEX_ATTRIB_PTR_SIZE 8 * sizeof(float)

	// Pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_PTR_SIZE, (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_PTR_SIZE, (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_PTR_SIZE, (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);


	Shaders::Shader shader(VERT_SHADER_SRC_FILE, FRAG_SHADER_SRC_FILE);
	Textures::Texture2D texture(RUSTY_METAL_TEXTURE);

	return RenderObj {EBO, shader, texture};
}

void renderCallback(RenderObj ro) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	float time = glfwGetTime();
	float gVal = (sin(time) / 1.5f) + 0.5f;


	ro.shader.use();
	ro.shader.setFloat("r", gVal);
	ro.shader.setFloat("g", gVal);
	ro.shader.setFloat("b", gVal);

	ro.texture.use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro.EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hohmann", NULL, NULL);
	if (win == NULL) {
		printf("Failed to create a window.\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(win);

	if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
		printf("Failed to init GLAD.\n");
		return 1;
	}

	float verts[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, -1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f
	};
	// Vert struc: x y z  r g b  tx ty

	unsigned int indices[] = {  
		0, 1, 3, 
		1, 2, 3	
	};  

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

	float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	RenderObj ro = preRenderCallback(indices, sizeof(indices), verts, sizeof(verts));

	while (!glfwWindowShouldClose(win)) {
		// Handle input
		processInput(win);

		// rendering
		renderCallback(ro);

		// glfw
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
