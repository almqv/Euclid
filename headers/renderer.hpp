#pragma once

#include <glm/fwd.hpp>
#include <vector>
#include "shaders.hpp"
#include "textures.hpp"

#include "GLFW/glfw3.h"

#define VERTEX_ATTRIB_PTR_SIZE 8 * sizeof(float)

#define VERT_SHADER_SRC_FILE "shaders/vertex.glsl"
#define FRAG_SHADER_SRC_FILE "shaders/fragment.glsl"

#define RUSTY_METAL_TEXTURE "assets/textures/rusty_metal.jpg"

namespace Renderer {
	class RenderObject {};

	class Renderer3D {
		public:
			Renderer3D();
			Renderer3D(std::vector<RenderObject> ROs);

			void setCamera(glm::vec3 pos);
			void setFOV(float deg);
			void render(GLFWwindow* win);
		private:
			std::vector<RenderObject> RenderObjects;
	};

	class Obj2D {
		public:
			Shaders::Shader shader;
			Textures::Texture2D texture;

			Obj2D(unsigned int indices[], unsigned int icount, float verts[], unsigned int vcount);

			void setTexture(const char* t_src);
			void transform(glm::mat4 T);
			void render(GLFWwindow* win);
		private:
			void bind_texture(Textures::Texture2D texture);
			unsigned int EBO;
			unsigned int VBO;
			unsigned int VAO;
	};
}
