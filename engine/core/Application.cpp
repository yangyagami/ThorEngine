#include "Application.h"
#include "spdlog/spdlog.h"

namespace Thor {

	Application::Application(int argc, char *argv[]) : mWindow() {
		spdlog::info("Application created");	
	}
	
	Application::~Application() {
		spdlog::info("Application destroyed");	
	}
	
	bool Application::init() {
		return mWindow.init();	
	}

	bool Application::closeRequested() {
		return mWindow.shouldClose();
	}
	
	void Application::process() {
		mWindow.swapBuffers();	
		mWindow.pollEvents();	
	}

	glm::vec2 Application::getViewSize() {
		return mWindow.getSize();
	}

	Window &Application::getWindow() {
		return mWindow;	
	}

}
