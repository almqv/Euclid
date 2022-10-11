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
	};
}
