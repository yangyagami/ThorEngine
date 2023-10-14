#ifndef THOR_ENGINE_H
#define THOR_ENGINE_H

#include <memory>

#include "Application.h"
#include "Renderer2D.h"
#include "Editor.h"
#include "Scene.h"
#include "GlobalContext.h"
#include "entt/entt.hpp"

namespace Thor {
	class Engine {
	private:
		std::unique_ptr<Renderer2D> mRenderer;
		Application mApp;
		std::unique_ptr<Editor> mEditor;
		Scene *mCurrentScene;
		entt::registry mRegistry;
	private:
		void update();
		void render();
	public:
		Engine(int argc, char *argv[]);
		~Engine();
		bool init();
		void switchScene(Scene *scene);
		int run();
	};
}

#endif
