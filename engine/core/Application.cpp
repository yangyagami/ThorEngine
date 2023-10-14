#include "Application.h"
#include "spdlog/spdlog.h"

namespace Thor {

	Application::Application(int argc, char *argv[]) : mWindow(), mKeyboard(&mWindow) {
		spdlog::info("Application created");	
	}
	
	Application::~Application() {
		spdlog::info("Application destroyed");	
	}
	
	bool Application::init() {
		return mWindow.init(1024, 768);	
	}

    void Application::setViewSize(const glm::vec2 &size) {
		mViewSize = size;
    }

    bool Application::closeRequested() {
		return mWindow.shouldClose();
	}
	
	void Application::process() {
		mWindow.swapBuffers();	
		mWindow.pollEvents();	
	}

	glm::vec2 Application::getViewSize() {
		return mViewSize;
	}

	Window &Application::getWindow() {
		return mWindow;	
	}

	Keyboard &Application::getKeyboard() {
		return mKeyboard;	
	}
}
