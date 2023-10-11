#ifndef THOR_ENGINE_H
#define THOR_ENGINE_H

#include "Application.h"
#include "Renderer.h"

namespace Thor {
	class Engine {
	private:
		Renderer mRenderer;
		Application mApp;
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
