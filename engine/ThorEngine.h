#ifndef THOR_ENGINE_H
#define THOR_ENGINE_H

#include <memory>

#include "sol/sol.hpp"
#include "Renderer2D.h"
#include "GlobalContext.h"
#include "SceneManager.h"
#include "OS.h"

namespace Thor {
	class Engine {
	private:
        OS *mOS;
		std::unique_ptr<Renderer2D> mRenderer2D;
		SceneManager mSceneManager;
		sol::state mLuaState;
	private:
		void initLuaState();
	private:
		void update();
		void render();
	public:
		Engine(OS *os, int argc, char *argv[]);
		~Engine();
		bool init();
		void run();
	};
}

#endif
