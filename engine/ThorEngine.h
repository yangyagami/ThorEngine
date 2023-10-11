#ifndef THOR_ENGINE_H
#define THOR_ENGINE_H

#include <memory>

#include "Application.h"
#include "Renderer2D.h"

namespace Thor {
	class Engine {
	private:
		std::unique_ptr<Renderer2D> mRenderer;
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
