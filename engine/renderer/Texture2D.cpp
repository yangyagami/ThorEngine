#include "OpenglTexture2D.h"
#include "Texture2D.h"

namespace Thor {
	std::unique_ptr<Texture2D> Texture2D::create() {
		return std::make_unique<OpenglTexture2D>();
	}

	std::unique_ptr<Texture2D> Texture2D::create(std::string path) {
		return std::make_unique<OpenglTexture2D>(path);
	}

	std::unique_ptr<Texture2D> Thor::Texture2D::create(unsigned char *data, int width, int height, int channels) {
    	return std::make_unique<OpenglTexture2D>(data, width, height, channels); 
	}
}


