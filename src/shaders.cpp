#include <fstream>
#include <glad/glad.h>
#include <vector>
#include <string>
#include <iostream>

namespace Shader {
	std::string loadSourceFromFile(const char* file) {
		std::string content;
		std::ifstream fh(file, std::ios::in);

		if(!fh.is_open()) {
			printf("Unable to read file \"%s\"!", file);
			return "";
		}

		std::string line = "";
		while(!fh.eof()) {
			std::getline(fh, line);
			content.append(line + "\n");
		}

		fh.close();
		return content.c_str();
	}

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
		}

		return shader;
	}

	unsigned int compileFromFile(GLenum shadertype, const char* file) {
		std::string src = loadSourceFromFile(file);
		unsigned int shader = compile(shadertype, src.c_str());
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
		}

		// Delete the shaders when we are done
		for(unsigned int s : shaders)
			glDeleteShader(s);

		return shaderProg;
	}
}
