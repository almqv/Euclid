#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "window.hpp"
#include "renderer.hpp"

class Scene {
	public:
		float diffuseStrength = 0.1; // 0 - 1
		glm::vec3 diffuseColor = glm::vec3(0.0, 0.0, 0.0); // R G B
		float deltaTime = 0.0f; // Seconds

		Scene(Window* win);
		Scene(Window* win, std::vector<Renderer::RenderObject*> ROs);

		void setCamera(Renderer::Camera *cam);
		Renderer::Camera* getCamera() { return camera; }

		void spawnObject(Renderer::RenderObject *ro);
		void render();
	protected: // NOTE: dumb
		Renderer::Camera *camera;

	private:
		std::vector<Renderer::RenderObject*> renderObjects = std::vector<Renderer::RenderObject*>();
		Window* window;
		float lastFrame = 0.0f;
};
