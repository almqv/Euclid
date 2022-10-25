#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.hpp"
#include "shaders.hpp"

namespace Renderer {
	void Obj2D::transform(glm::mat4 T) {
		shader.setMat4("transform", T);
	}

	void Obj2D::render() {
		shader.use();
		texture.bind();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	Obj2D::Obj2D(unsigned int indices[], unsigned int icount, float verts[], unsigned int vcount) 
		: shader(VERT_SHADER_SRC_FILE, FRAG_SHADER_SRC_FILE), texture(RUSTY_METAL_TEXTURE) {

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

}
