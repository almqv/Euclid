#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "GLFW/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/fwd.hpp"
#include "renderer.hpp"
#include "shaders.hpp"

namespace Renderer {
	// Object
	Object::Object() {}

	Object::Object(glm::vec3 pos) : Object() {
		setPosition(pos);
	}

	Object::Object(glm::vec3 pos, glm::vec3 angle) : Object(pos) {
		setRotation(angle);
	}

	void Object::transform(glm::mat4 T) {
		modelTransform = T;
	}

	glm::mat4 Object::getPositionTransform() { return positionTransform; }

	void Object::updatePositionTransform() {
		glm::mat4 T = glm::mat4(1.0f);
		positionTransform = glm::translate(T, position);
	}

	void Object::setPosition(glm::vec3 pos) {
		position = pos;
		updatePositionTransform();
	}

	void Object::translate(glm::vec3 dpos) {
		position += dpos;
		updatePositionTransform();
	}

	glm::mat4 Object::getRotationTransform() { return rotationTransform; }

	void Object::updateRotationTransform() {
		float x_Ang, y_Ang, z_Ang;
		x_Ang = angle[0];
		y_Ang = angle[1];
		z_Ang = angle[2];

		glm::mat4 T = glm::mat4(1.0f);
		T = glm::rotate(T, glm::radians(x_Ang), glm::vec3(1.0f, 0.0f, 0.0f));
		T = glm::rotate(T, glm::radians(y_Ang), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::rotate(T, glm::radians(z_Ang), glm::vec3(0.0f, 0.0f, 1.0f));

		rotationTransform = T;
		// std::cout << "Name: " << name << " | ";
		// std::cout << glm::to_string(T) << std::endl;
	}

	void Object::setRotation(glm::vec3 ang) {
		angle = ang;
		updateRotationTransform();
	}

	void Object::rotate(glm::vec3 dangle) {
		angle += dangle;
		updateRotationTransform();
	}

	// Scene
	Scene::Scene(GLFWwindow* win) : camera(win) {
		window = win;	

		camera.setFOV(DEFAULT_FOV);
	}

	Scene::Scene(GLFWwindow* win, std::vector<RenderObject> ROs) : Scene(win) {
		renderObjects = ROs;
	}

	void Scene::spawnObject(RenderObject ro) {
		renderObjects.push_back(ro);
	}

	void Scene::setCamera(Camera cam) {
		camera = cam;
	}

	void Scene::render() {
		for ( RenderObject ro: renderObjects ) 
			ro.render(window, camera);
	}

	// Camera
	Camera::Camera(GLFWwindow* win) {
		window = win;
	}

	Camera::Camera(GLFWwindow* win, glm::vec3 pos) : Camera(win) {
		setPosition(pos);
	}

	Camera::Camera(GLFWwindow* win, glm::vec3 pos, glm::vec3 angle) : Camera(win, pos) {
		setRotation(angle);
	}

	void Camera::setFOV(float fov) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		projection = glm::perspective(glm::radians(fov), (float)width / (float)height, NEAR_PLANE, FAR_PLANE);
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

	// TODO: Make prerender instead of render
	void RenderObject::render(GLFWwindow* win, Camera cam) {
		shader.setMat4("modelPosition", getPositionTransform());
		shader.setMat4("modelRotation", getRotationTransform());

		shader.setMat4("camPos", cam.getPositionTransform());
		shader.setMat4("camRot", cam.getRotationTransform());
		shader.setMat4("camProjection", cam.projection);

		std::cout << "Name: " << name << " | ";
		std::cout << glm::to_string(getPositionTransform()) << std::endl;

		shader.use();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawArrays(GL_TRIANGLES, 0, indicesVec.size());
	}

	void RenderObject::setPosition(glm::vec3 pos) {
		Object::setPosition(pos);
		shader.setMat4("modelPosition", getPositionTransform());
	}

	void RenderObject::setRotation(glm::vec3 angle) {
		Object::setRotation(angle);
		shader.setMat4("modelRotation", getRotationTransform());
	}

	void RenderObject::transform(glm::mat4 T) {
		Object::transform(T);
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
