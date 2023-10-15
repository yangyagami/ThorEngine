#ifndef THOR_GIZMO_2D_H
#define THOR_GIZMO_2D_H

#include "Object.hpp"

namespace Thor {

class Gizmo2D {
private:
	glm::vec2 mPos;
public:
	Gizmo2D() = default;
	void setPos(const glm::vec2 &pos);
	void update();
	void render();
};

}

#endif
