#include "GlobalContext.h"
#include <memory>

namespace Thor {

	std::unique_ptr<GlobalContext> GlobalContext::singleton = nullptr;

	GlobalContext::GlobalContext(std::unique_ptr<Renderer2D> &renderer2D, SceneManager &sceneManager, sol::state &state) : renderer2D(renderer2D), sceneManager(sceneManager), luaState(state) {
	}

	GlobalContext::~GlobalContext() {
	}

}

