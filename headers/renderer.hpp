#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "shaders.hpp"
#include "GLFW/glfw3.h"

#include "textures.hpp"
#include "window.hpp"


#define VERTEX_ATTRIB_PTR_SIZE 8 * sizeof(float)

#define VERT_SHADER_SRC_FILE "shaders/vertex.glsl"
#define FRAG_SHADER_SRC_FILE "shaders/fragment.glsl"

#define DEFAULT_FOV 60.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100.0f

namespace Renderer {
	class Entity {
		public:
			Entity();
			Entity(glm::vec3 pos);
			Entity(glm::vec3 pos, glm::vec3 angle);

			void transform(glm::mat4 T);
			void scale(glm::vec3 vscale);

			void setPosition(glm::vec3 pos);
			void translate(glm::vec3 dpos);

			void setRotation(glm::vec3 angle);
			void rotate(glm::vec3 dangle);

		protected:
			void updatePositionTransform();
			void updateRotationTransform();

			glm::mat4 positionTransform = glm::mat4(1.0f);
			glm::mat4 rotationTransform = glm::mat4(1.0f);
			glm::mat4 modelTransform = glm::mat4(1.0f);
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 angle = glm::vec3(0.0f, 0.0f, 0.0f);
	};

	class Camera : public Entity {
		public:
			glm::mat4 view = glm::mat4(1.0f);
			float FOV;

			Camera(Window* win);
			Camera(Window* win, glm::vec3 pos);
			Camera(Window* win, glm::vec3 pos, glm::vec3 angle);

			glm::mat4 getProjection();
		protected:
			Window* window;
			glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

			void updateCameraTransforms();
		private:
			glm::mat4 projection = glm::mat4(1.0f);
	};


	class RenderEntity : public Entity {
		public:
			RenderEntity(std::vector<float> verts, std::vector<unsigned int> indices);
			void render(Camera cam);
			void preRenderHook();
		private:
			Shaders::Shader shader;
			unsigned int EBO;
			unsigned int VBO;
			unsigned int VAO;
			std::vector<float> vertsVec;
			std::vector<unsigned int> indicesVec;
	};

	class TexturedEntity : public RenderEntity {
		public:
			using RenderEntity::RenderEntity;
			void setTexture(const char* t_src);
			void preRenderHook();
		private:
			Textures::Texture2D texture;
			void bind_texture(Textures::Texture2D texture);
	};

	class Scene {
		public:
			float deltaTime = 0.0f; // Seconds
			float diffuseStrength = 0.1;
			glm::vec3 diffuseColor = glm::vec3(0.0, 0.0, 0.0);

			Scene(Window* win);
			Scene(Window* win, std::vector<RenderEntity*> ROs);

			void setCamera(Camera *cam);
			void spawnEntity(RenderEntity *ro);
			void render();
		protected: // NOTE: dumb
			Camera *camera;

		private:
			std::vector<RenderEntity*> renderEntitys = std::vector<RenderEntity*>();
			Window* window;
			float lastFrame = 0.0f;
	};
}
