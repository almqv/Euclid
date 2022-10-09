#include <fstream>
#include <glad/glad.h>
#include <vector>

namespace Shader {
	unsigned int compile(GLenum shadertype, const char* shaderSource) {
		unsigned int shader;
		shader = glCreateShader(shadertype);
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		int success;
		char infolog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infolog);
			printf("Shader Compilation Error:\n%s\n", infolog);
		} else {
			printf("Compiled shader %u!\n", shadertype);
		}

		return shader;
	}

	unsigned int createProgram(std::vector<unsigned int> shaders) {
		unsigned int shaderProg;
		shaderProg = glCreateProgram();

		// Link the shaders
		for(unsigned int s : shaders) 
			glAttachShader(shaderProg, s);

		glLinkProgram(shaderProg);

		// Check for errors
		int success;
		char infolog[512];
		glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProg, 512, NULL, infolog);
			printf("Shader Program Linking Error:\n%s\n", infolog);
		} else {
			printf("Linked shaders & created program: %u\n", shaderProg);
		}

		return shaderProg;
	}
}
