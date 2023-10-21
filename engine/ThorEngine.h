#ifndef THOR_ENGINE_H
#define THOR_ENGINE_H

#include <memory>

#include "sol/sol.hpp"
#include "Application.h"
#include "Renderer2D.h"
#include "Editor.h"
#include "GlobalContext.h"
#include "SceneManager.h"

namespace Thor {
	class Engine {
	private:
		std::unique_ptr<Renderer2D> mRenderer;
		Application mApp;
		std::unique_ptr<Editor> mEditor;
		SceneManager mSceneManager;
		sol::state mLuaState;
	private:
		void initLuaState();
	private:
		void update();
		void render();
	public:
		Engine(int argc, char *argv[]);
		~Engine();
		bool init();
		int run();
	};
}

#endif
