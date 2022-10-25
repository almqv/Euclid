#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.hpp"
#include "shaders.hpp"

namespace Renderer {

	Renderer3D::Renderer3D() {
		// TODO: Make more OOP
	}

	Renderer3D::Renderer3D(std::vector<RenderObject> ROs) : Renderer3D() {
		RenderObjects = ROs;
	}

	void Obj2D::transform(glm::mat4 T) {
		shader.setMat4("model", T);
	}

	void Obj2D::setTexture(const char* t_src) {
		texture.texture_src = t_src;
		texture.load();
	}

	void Obj2D::render(GLFWwindow* win) {
		int width, height;

		// Camera 
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f)); // Camera position
		shader.setMat4("view", view);

		glfwGetWindowSize(win, &width, &height);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		// Use the shader etc
		shader.use();

		if (texture.loaded)
			texture.bind();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	Obj2D::Obj2D(unsigned int indices[], unsigned int icount, float verts[], unsigned int vcount) 
		: shader(VERT_SHADER_SRC_FILE, FRAG_SHADER_SRC_FILE) {

		// Vertex buffer object
		glGenBuffers(1, &VBO);

		// Vertex Array Object
		glGenVertexArrays(1, &VAO); // gen the VAO
		glBindVertexArray(VAO); // bind it

		// Copy verts into buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vcount, verts, GL_DYNAMIC_DRAW); // for moving stuff
		//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount, indices, GL_STATIC_DRAW);

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

	// Private stuff
	void Obj2D::bind_texture(Textures::Texture2D new_texture) {
		texture = new_texture;
	}
}
