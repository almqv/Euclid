#pragma once

#include "glm/fwd.hpp"
#include <glad/glad.h>
#include <string>
#include <vector>

namespace Shaders {
	std::string loadSourceFromFile(const char* file);

	unsigned int compile(GLenum shadertype, const char* shaderSource);
	unsigned int compileFromFile(GLenum shadertype, const char* file); 
	unsigned int createProgram(std::vector<unsigned int> shaders);

	class Shader {
		public:
			unsigned int id;
			Shader(const char* vertPath, const char* fragPath);

			void use();
			void setBool(const std::string &name, bool val) const;
			void setInt(const std::string &name, int val) const;
			void setFloat(const std::string &name, float val) const;
			void setMat4(const std::string &name, glm::mat4 val) const;
			void setVec3(const std::string &name, glm::vec3 val) const;

		private:
			unsigned int uniLocation(const std::string &name) const;
	};
}
