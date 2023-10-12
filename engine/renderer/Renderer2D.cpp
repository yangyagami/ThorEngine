#include "OpenglRenderer2D.h"
#include "glm/glm.hpp"

namespace Thor {

	std::unique_ptr<Renderer2D> Renderer2D::create() {
		return std::make_unique<OpenglRenderer2D>();
	}

}

