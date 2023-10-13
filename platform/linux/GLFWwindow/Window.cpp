#include "Window.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"

namespace Thor {
	Window::Window() : mGlfwWindow(nullptr) {
		
	}
	
	bool Window::init(int width, int height, const std::string &title) {
		mWindowTitle = title;
		if (!glfwInit()) {
			spdlog::error("Init glfw failed!");
			return false;
		}

		mGlfwWindow = glfwCreateWindow(width, height, mWindowTitle.c_str(), nullptr, nullptr);
		if (!mGlfwWindow) {
			glfwTerminate();
			spdlog::error("Create glfw window failed!");
			return false;
		}

		glfwMakeContextCurrent(mGlfwWindow);
		gladLoadGL();
		glViewport(0, 0, width, height);
		glfwSetErrorCallback([](int error, const char *description){
			spdlog::error("Error: {}", description);	
		});
		glfwSetWindowSizeCallback(mGlfwWindow, [](GLFWwindow *window, int width, int height){
			glfwSetWindowSize(window, width, height);
			glViewport(0, 0, width, height);
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


	glm::vec2 Window::getSize() {
		int width, height;
		glfwGetWindowSize(mGlfwWindow, &width, &height);
		return glm::vec2(width, height);	
	}

	Window::~Window() {
		spdlog::info("Glfw window Destroyed.");
		glfwTerminate();	
	}

	GLFWwindow *Window::getGLFWWindow() {
		return mGlfwWindow;
	}

	int Window::getKeyState(int key) {
		return glfwGetKey(mGlfwWindow, key);	
	}
}
