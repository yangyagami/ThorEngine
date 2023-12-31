#ifndef THOR_TEXTURE_2D_H
#define THOR_TEXTURE_2D_H

#include <memory>
#include <string>

#include "glm/glm.hpp"

namespace Thor {

class Texture2D {
public:
	static std::unique_ptr<Texture2D> create();
	static std::unique_ptr<Texture2D> create(std::string path);
	static std::unique_ptr<Texture2D> create(unsigned char *data, int width, int height, int channels);
public:
	virtual glm::vec2 getSize() = 0;
};

}

#endif
