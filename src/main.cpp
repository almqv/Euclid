#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>

#include "shaders.cpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

static float verts[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
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

void preRenderCallback(GLFWwindow *win) {
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW); // for moving stuff
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// Compile a bunch of shaders etc
	unsigned int vertShader = Shader::compile(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragShader = Shader::compile(GL_FRAGMENT_SHADER, fragShaderSource);
	unsigned int shaders[2] = {vertShader, fragShader};

	// Create a shader program & link the shaders etc
	unsigned int shaderProg;
	shaderProg = Shader::createProgram( std::vector<unsigned int> (std::begin(shaders), std::end(shaders)) );

	// Copy verts into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// Set attrib pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Use the shader program whenever we want to render
	glUseProgram(shaderProg);
	glDeleteShader(vertShader);
	glDeleteShader(vertShader);  

}

void renderCallback(GLFWwindow *win) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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

	preRenderCallback(win);

	while (!glfwWindowShouldClose(win)) {
		// Handle input
		processInput(win);

		// rendering
		verts[1] += 0.0001f;
		printf("f=%f\n", verts[1]);
		renderCallback(win);

		// glfw
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
