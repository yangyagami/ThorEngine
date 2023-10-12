#include "OpenglTexture2D.h"

namespace Thor {
	std::unique_ptr<Texture2D> Texture2D::create() {
		return std::make_unique<OpenglTexture2D>();
	}

	std::unique_ptr<Texture2D> Texture2D::create(std::string path) {
		return std::make_unique<OpenglTexture2D>(path);
	}
}
