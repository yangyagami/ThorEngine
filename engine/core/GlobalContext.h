#ifndef THOR_GLOBAL_CONTEXT_H
#define THOR_GLOBAL_CONTEXT_H

#include <memory>

#include "Renderer2D.h"
#include "spdlog/spdlog.h"

namespace Thor {

struct GlobalContext {
	static std::unique_ptr<GlobalContext> instance;
	std::unique_ptr<Renderer2D> &renderer2D;

	GlobalContext(std::unique_ptr<Renderer2D> &renderer2D); 
	~GlobalContext(); 
};

}

#endif
