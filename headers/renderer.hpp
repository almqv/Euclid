#pragma once

#include <glm/fwd.hpp>
#include "shaders.hpp"
#include "textures.hpp"

#define VERTEX_ATTRIB_PTR_SIZE 8 * sizeof(float)

#define VERT_SHADER_SRC_FILE "shaders/vertex.glsl"
#define FRAG_SHADER_SRC_FILE "shaders/fragment.glsl"

#define RUSTY_METAL_TEXTURE "assets/textures/rusty_metal.jpg"

namespace Renderer {
	class Obj2D {
		public:
			Obj2D(unsigned int indices[], unsigned int icount, float verts[], unsigned int vcount);
			Shaders::Shader shader;
			Textures::Texture2D texture;

			void transform(glm::mat4 T);
			void bind_texture(Textures::Texture2D texture);
			void render();
		private:
			unsigned int EBO;
			unsigned int VBO;
			unsigned int VAO;
	};
}
