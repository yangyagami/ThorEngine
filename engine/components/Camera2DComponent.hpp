#ifndef THOR_CAMERA_2D_COMPONENT_H
#define THOR_CAMERA_2D_COMPONENT_H

#include "glm/glm.hpp"

namespace Thor {

struct Camera2DComponent {
	glm::vec2 position;
	float rotation;

	Camera2DComponent() = default;
	Camera2DComponent(const glm::vec2 &pos, float rotation) : position(pos), rotation(rotation) {
	}
};

}

#endif
