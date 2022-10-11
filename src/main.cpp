#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <math.h>

#include "shaders.cpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define VERT_SHADER_SRC_FILE "shaders/vertex.glsl"
#define FRAG_SHADER_SRC_FILE "shaders/fragment.glsl"

float verts[] = {
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f, 
	-0.5f, -0.5f, 0.0f,  
	-0.5f,  0.5f, 0.0f
};
unsigned int indices[] = {  
	0, 1, 3, 
	1, 2, 3	
};  

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
	unsigned int VBO;
	unsigned int VAO;
	unsigned int shaderProg;
};

RenderObj preRenderCallback() {
	// Compile a bunch of shaders etc
	unsigned int vertShader = Shader::compileFromFile(GL_VERTEX_SHADER, VERT_SHADER_SRC_FILE);
	unsigned int fragShader = Shader::compileFromFile(GL_FRAGMENT_SHADER, FRAG_SHADER_SRC_FILE);
	unsigned int shaders[2] = {vertShader, fragShader};

	// Create a shader program & link the shaders etc
	unsigned int shaderProg;
	shaderProg = Shader::createProgram( std::vector<unsigned int> (std::begin(shaders), std::end(shaders)) );

	// Vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // gen the VAO
	glBindVertexArray(VAO); // bind it

	// Copy verts into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW); // for moving stuff
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// Set attrib pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return RenderObj {EBO, VBO, VAO, shaderProg};
}

void renderCallback(RenderObj ro) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	float time = glfwGetTime();
	float gVal = (sin(time) / 1.5f) + 0.5f;
	int vertColLocation = glGetUniformLocation(ro.shaderProg, "inputColor");

	glUseProgram(ro.shaderProg);
	glUniform4f(vertColLocation, gVal, gVal, gVal, 1.0f);

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

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

	RenderObj ro = preRenderCallback();

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
