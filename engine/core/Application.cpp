#include "Application.h"
#include "spdlog/spdlog.h"

namespace Thor {

	Application::Application(int argc, char *argv[]) : mWindow() {
	
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

}
