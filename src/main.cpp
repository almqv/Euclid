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
	"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
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

struct RenderObj {
	unsigned int VBO;
	unsigned int VAO;
	unsigned int shaderProg;
};

RenderObj preRenderCallback() {
	// Compile a bunch of shaders etc
	unsigned int vertShader = Shader::compile(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragShader = Shader::compile(GL_FRAGMENT_SHADER, fragShaderSource);
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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW); // for moving stuff
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// Copy verts into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// Set attrib pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return RenderObj {VBO, VAO, shaderProg};
}

void renderCallback(RenderObj ro) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(ro.shaderProg);
	glBindVertexArray(ro.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
