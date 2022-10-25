#pragma once

namespace Textures {
	class Texture2D {
		public:
			unsigned int id;
			const char* texture_src;
			bool loaded = false;

			Texture2D();
			Texture2D(const char* t_src);
			void load();
			void bind();
		private:
			int width, height, nrChannels;
	};
}

