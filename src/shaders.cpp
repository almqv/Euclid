#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "../headers/shaders.hpp"

namespace Shaders {
	std::string loadSourceFromFile(const char* fp) {
		std::string src;
		std::ifstream fh;

		fh.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			fh.open(fp);
			std::stringstream sstr;
			sstr << fh.rdbuf();
			fh.close();

			src = sstr.str();
			return src;
		} catch (std::ifstream::failure err) {
			printf("[ERROR] Unable to read file \"%s\\n", fp);
			exit(1);
		}
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
			printf("[%s] Shader Compilation Error:\n%s\n", shaderSource, infolog);
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

	Shader::Shader(const char* vertPath, const char* fragPath) {
		unsigned int vertShader = compileFromFile(GL_VERTEX_SHADER, vertPath);
		unsigned int fragShader = compileFromFile(GL_FRAGMENT_SHADER, fragPath);
		unsigned int shaders[2] = {vertShader, fragShader};

		// Shader program ID
		id = Shaders::createProgram( std::vector<unsigned int> (std::begin(shaders), std::end(shaders)) );
	}

	void Shader::use() { glUseProgram(id); }

	void Shader::setInt(const std::string &name, int val) const {
		glUniform1i(glGetUniformLocation(id, name.c_str()), val);
	}

	void Shader::setFloat(const std::string &name, float val) const {
		glUniform1f(glGetUniformLocation(id, name.c_str()), val);
	}

	void Shader::setBool(const std::string &name, bool val) const {
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)val)	;
	}
}
