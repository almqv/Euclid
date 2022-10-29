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

#define DEFAULT_FOV 60.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100.0f

namespace Renderer {
	class Object {
		public:
			const char* name = "Object";
			Object();
			Object(glm::vec3 pos);
			Object(glm::vec3 pos, glm::vec3 angle);

			glm::mat4 getPositionTransform();
			void setPosition(glm::vec3 pos);
			void translate(glm::vec3 dpos);

			glm::mat4 getRotationTransform();
			void setRotation(glm::vec3 angle);
			void rotate(glm::vec3 dangle);

			void transform(glm::mat4 T);
			void updatePositionTransform();
			void updateRotationTransform();

		private:
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 angle = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::mat4 positionTransform = glm::mat4(1.0f);
			glm::mat4 rotationTransform = glm::mat4(1.0f);
			glm::mat4 modelTransform = glm::mat4(1.0f);
	};

	class Camera : public Object {
		public:
			const char* name = "Camera";
			Camera(GLFWwindow* win);
			Camera(GLFWwindow* win, glm::vec3 pos);
			Camera(GLFWwindow* win, glm::vec3 pos, glm::vec3 angle);

			void setFOV(float deg);
			glm::mat4 projection = glm::mat4(1.0f);
		private:
			GLFWwindow* window;
	};


	class RenderObject : public Object {
		public:
			const char* name = "RenderObject";
			RenderObject(std::vector<float> verts, std::vector<unsigned int> indices);
			void render(GLFWwindow* win, Camera cam);
			void preRenderHook();
			void transform(glm::mat4 T);

			void setPosition(glm::vec3 pos);
			void setRotation(glm::vec3 angle);
		private:
			Shaders::Shader shader;
			unsigned int EBO;
			unsigned int VBO;
			unsigned int VAO;
			std::vector<float> vertsVec;
			std::vector<unsigned int> indicesVec;
	};

	class Scene {
		public:
			Camera camera;

			Scene(GLFWwindow* win);
			Scene(GLFWwindow* win, std::vector<RenderObject> ROs);

			void setCamera(Camera cam);
			void spawnObject(RenderObject ro);
			void render();
		private:
			std::vector<RenderObject> renderObjects = std::vector<RenderObject>();
			GLFWwindow* window;
	};

	class TexturedObject : public RenderObject {
		public:
			const char* name = "TexturedObject";
			using RenderObject::RenderObject;
			void setTexture(const char* t_src);
			void preRenderHook();
		private:
			Textures::Texture2D texture;
			void bind_texture(Textures::Texture2D texture);
	};
}
