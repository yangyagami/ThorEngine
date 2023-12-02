#include "GlobalContext.h"
#include <memory>

namespace Thor {

	std::unique_ptr<GlobalContext> GlobalContext::singleton = nullptr;

	GlobalContext::GlobalContext(
        OS *os,
        std::unique_ptr<Renderer2D> &renderer2D, 
        SceneManager &sceneManager, 
        sol::state &state, entt::registry &registry) : 
        renderer2D(renderer2D),
        sceneManager(sceneManager),
        luaState(state),
        registry(registry),
        os(os) {
    }

	GlobalContext::~GlobalContext() {
	}

}

