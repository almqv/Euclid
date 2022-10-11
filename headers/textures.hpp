#ifndef TEXTURES_HPP
#define TEXTURES_HPP

namespace Textures {
	class Texture2D {
		public:
			unsigned int id;
			Texture2D(const char* t_src);
			void load();
			void use();
		private:
			const char* texture_src;
			int width, height, nrChannels;
	};
}

#endif
