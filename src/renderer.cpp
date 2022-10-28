#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "renderer.hpp"
#include "shaders.hpp"

namespace Renderer {

	// Scene
	Scene::Scene(GLFWwindow* win) {
		window = win;	

		setFOV(DEFAULT_FOV);
	}

	Scene::Scene(GLFWwindow* win, std::vector<RenderObject> ROs) : Scene(win) {
		renderObjects = ROs;
	}

	void Scene::spawnObject(RenderObject ro) {
		renderObjects.push_back(ro);
	}

	void Scene::setFOV(float fov) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		projectionTransform = glm::perspective(glm::radians(fov), (float)width / (float)height, NEAR_PLANE, FAR_PLANE);
	}

	void Scene::setCamera(glm::vec3 pos) {
		cameraTransform = glm::translate(cameraTransform, pos); 
	}

	void Scene::render() {
		for ( RenderObject ro: renderObjects ) 
			ro.render(window, cameraTransform, projectionTransform);
	}

	// RenderObject
	RenderObject::RenderObject(std::vector<float> verts, std::vector<unsigned int> indices) 
		: shader(VERT_SHADER_SRC_FILE, FRAG_SHADER_SRC_FILE) {
		vertsVec = verts;
		indicesVec = indices;

		float vertsArray[vertsVec.size()];
		std::copy(vertsVec.begin(), vertsVec.end(), vertsArray);

		unsigned int indicesArray[indicesVec.size()];
		std::copy(indicesVec.begin(), indicesVec.end(), indicesArray);

		// Vertex Array Object
		glGenVertexArrays(1, &VAO); // gen the VAO
		glBindVertexArray(VAO); // bind it

		// Copy the verts into the buffer
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertsVec.size() * sizeof(vertsVec[0]), vertsArray, GL_DYNAMIC_DRAW); // for moving stuff

		// Copy the indices for the verts into another buffer
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesVec.size() * sizeof(indicesVec[0]), indicesArray, GL_STATIC_DRAW);

		// Shader stuff
		// Pos
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_PTR_SIZE, (void*)0);
		glEnableVertexAttribArray(0);

		// Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_PTR_SIZE, (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		// Texture
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_PTR_SIZE, (void*)(6*sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void RenderObject::preRenderHook() {}

	void RenderObject::render(GLFWwindow* win, glm::mat4 cameraTransform, glm::mat4 projectionTransform) {
		glm::mat4 posT = glm::mat4(1.0f);
		posT = glm::translate(posT, position);

		shader.setMat4("baseModel", posT);
		shader.setMat4("view", cameraTransform);
		shader.setMat4("projection", projectionTransform);

		shader.use();

		preRenderHook();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawArrays(GL_TRIANGLES, 0, indicesVec.size());
	}

	void RenderObject::transform(glm::mat4 T) {
		shader.setMat4("model", T);
	}

	// TexturedObject
	void TexturedObject::setTexture(const char* t_src) {
		texture.texture_src = t_src;
		texture.load();
	}

	void TexturedObject::preRenderHook() {
		printf("TexturedObject was here!\n");
		printf("Now has texture: %s", texture.texture_src);
		if (texture.loaded)
			texture.bind();
	}

	// Private stuff
	void TexturedObject::bind_texture(Textures::Texture2D new_texture) {
		texture = new_texture;
	}
}
