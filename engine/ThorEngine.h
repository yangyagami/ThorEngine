#ifndef THOR_ENGINE_H
#define THOR_ENGINE_H

#include <memory>

#include "Application.h"
#include "Renderer2D.h"
#include "Editor.h"

namespace Thor {
	class Engine {
	private:
		std::unique_ptr<Renderer2D> mRenderer;
		Application mApp;
		std::unique_ptr<Editor> mEditor;
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
