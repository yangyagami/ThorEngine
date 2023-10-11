#include "OpenglRenderer2D.h"
#include "Vec.hpp"

namespace Thor {

	std::unique_ptr<Renderer2D> Renderer2D::create() {
		return std::make_unique<OpenglRenderer2D>();
	}

}

