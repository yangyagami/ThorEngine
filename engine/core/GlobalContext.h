#ifndef THOR_GLOBAL_CONTEXT_H
#define THOR_GLOBAL_CONTEXT_H

#include <memory>

#include "OS.h"
#include "entt/entt.hpp"
#include "sol/sol.hpp"
#include "Renderer2D.h"
#include "SceneManager.h"

namespace Thor {

    struct GlobalContext {
    public:
    	std::unique_ptr<Renderer2D> &renderer2D;
    	SceneManager &sceneManager;
    	sol::state &luaState;
        entt::registry &registry;
        OS *os;
        double frameDelta;
    
    	static std::unique_ptr<GlobalContext> singleton;
    
    	GlobalContext(
            OS *os,
            std::unique_ptr<Renderer2D> &renderer2D, 
            SceneManager &sceneManager, 
            sol::state &state, 
            entt::registry &registry
        ); 
    	~GlobalContext(); 
    };

}

#endif
