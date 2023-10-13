#ifndef THOR_GLOBAL_CONTEXT_H
#define THOR_GLOBAL_CONTEXT_H

#include <memory>

#include "entt/entt.hpp"
#include "Renderer2D.h"
#include "Application.h"

namespace Thor {

struct GlobalContext {
	static std::unique_ptr<GlobalContext> instance;
	std::unique_ptr<Renderer2D> &renderer2D;
	entt::registry &registry;
	Application &app;

	GlobalContext(std::unique_ptr<Renderer2D> &renderer2D, entt::registry &registry, Application &app); 
	~GlobalContext(); 
};

}

#endif
