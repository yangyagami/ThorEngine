#ifndef THOR_GLOBAL_CONTEXT_H
#define THOR_GLOBAL_CONTEXT_H

#include <memory>

#include "sol/sol.hpp"
#include "Renderer2D.h"
#include "SceneManager.h"

namespace Thor {

struct GlobalContext {
public:
	std::unique_ptr<Renderer2D> &renderer2D;
	SceneManager &sceneManager;
	sol::state &luaState;

	static std::unique_ptr<GlobalContext> singleton;

	GlobalContext(std::unique_ptr<Renderer2D> &renderer2D, SceneManager &sceneManager, sol::state &state); 
	~GlobalContext(); 
};

}

#endif
