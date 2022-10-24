#include <stdio.h>
#include "../headers/textures.hpp"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../extern/stb/stb_image.h"

namespace Textures {
	Texture2D::Texture2D(const char* t_src) {
		texture_src = t_src;

		// Bind this texture
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		// Repeat/bounded etc
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		// Mipmap "blending"
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load texture source etc
		load();
	}

	void Texture2D::load() {
		printf("[%i] \"%s\" - ", id, texture_src);
		unsigned char* data = stbi_load(texture_src, &width, &height, &nrChannels, 0);
		
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			printf("Loaded!\n");
		} else {
			printf("[ERROR] Failed to load texture \"%s\"\n", texture_src);
		}

		stbi_image_free(data);
	}

	void Texture2D::bind() {
		glBindTexture(GL_TEXTURE_2D, id);
	}
}
