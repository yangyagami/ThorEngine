#include "Window.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"

namespace Thor {
	Window::Window() : Window(800, 600, "ThorEngine") {
	
	}
	
	Window::Window(std::string title) : Window(800, 600, title) {
	
	}
	
	Window::Window(int width, int height, std::string title) : mGlfwWindow(nullptr), mWidth(width), mHeight(height), mWindowTitle(title) {
		
	}
	
	bool Window::init() {
		if (!glfwInit()) {
			spdlog::error("Init glfw failed!");
			return false;
		}

		mGlfwWindow = glfwCreateWindow(mWidth, mHeight, mWindowTitle.c_str(), nullptr, nullptr);
		if (!mGlfwWindow) {
			glfwTerminate();
			spdlog::error("Create glfw window failed!");
			return false;
		}

		glfwMakeContextCurrent(mGlfwWindow);
		gladLoadGL();
		glfwSetErrorCallback([](int error, const char *description){
			spdlog::error("Error: {}", description);	
		});

		spdlog::info("Create glfw window success.");
		
		return true;
	}
	
	bool Window::shouldClose() {
		return glfwWindowShouldClose(mGlfwWindow);	
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(mGlfwWindow);	
	}

	void Window::pollEvents() {
		glfwPollEvents();	
	}


	Window::~Window() {
		spdlog::info("Glfw window Destroyed.");
		glfwTerminate();	
	}

}
