#ifndef THOR_CAMERA_2D_H
#define THOR_CAMERA_2D_H

#include "glm/glm.hpp"

namespace Thor {

struct Camera2D {
	glm::vec2 position;
	glm::vec2 viewSize;
	float rotation;

	Camera2D() = default;
	Camera2D(const glm::vec2 &pos, const glm::vec2 &size, float rotation) : position(pos), viewSize(size), rotation(rotation) {
	}
};

}

#endif
