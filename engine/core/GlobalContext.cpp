#include "GlobalContext.h"

namespace Thor {

	std::unique_ptr<GlobalContext> GlobalContext::instance = nullptr;

	GlobalContext::GlobalContext(std::unique_ptr<Renderer2D> &renderer2D, entt::registry &registry, Application &app, SceneManager &sceneManager, sol::state &state) : renderer2D(renderer2D), registry(registry), app(app), sceneManager(sceneManager), luaState(state) {
	}

	GlobalContext::~GlobalContext() {
	}

}

