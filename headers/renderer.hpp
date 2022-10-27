#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "shaders.hpp"
#include "textures.hpp"

#include "GLFW/glfw3.h"

#define VERTEX_ATTRIB_PTR_SIZE 8 * sizeof(float)

#define VERT_SHADER_SRC_FILE "shaders/vertex.glsl"
#define FRAG_SHADER_SRC_FILE "shaders/fragment.glsl"

#define DEFAULT_FOV 45.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100.0f

namespace Renderer {
	class RenderObject {
		public:
			RenderObject(float verts[], unsigned int indices[]);
			void render(GLFWwindow* win, glm::mat4 cameraTransform, glm::mat4 projectionTransform);
			void transform(glm::mat4 T);
		private:
			Shaders::Shader shader;
			unsigned int vertCount;
			unsigned int EBO;
			unsigned int VBO;
			unsigned int VAO;
	};

	class Renderer3D {
		public:
			Renderer3D(GLFWwindow* win);
			Renderer3D(GLFWwindow* win, std::vector<RenderObject> ROs);

			void setCamera(glm::vec3 pos);
			void setFOV(float deg);
			void spawnObject(RenderObject ro);
			void render();
		private:
			std::vector<RenderObject> renderObjects = std::vector<RenderObject>();
			GLFWwindow* window;
			glm::mat4 cameraTransform = glm::mat4(1.0f);
			glm::mat4 projectionTransform = glm::mat4(1.0f);
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
