#include "GlobalContext.h"

namespace Thor {

	std::unique_ptr<GlobalContext> GlobalContext::instance = nullptr;

	GlobalContext::GlobalContext(std::unique_ptr<Renderer2D> &renderer2D) : renderer2D(renderer2D) {
		spdlog::info("GlobalContext Created");
	}

	GlobalContext::~GlobalContext() {
		spdlog::info("GlobalContext destroyed");
	}

}

