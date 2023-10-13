#ifndef THOR_GLFW_WINDOW_H
#define THOR_GLFW_WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

namespace Thor {

class Window {
public:
	Window();
	~Window();
	bool init(int width, int height, const std::string &title = "ThorEngine");
	bool shouldClose();
	void swapBuffers();
	void pollEvents();
	GLFWwindow *getGLFWWindow();
	glm::vec2 getSize();
	int getKeyState(int key);
private:
	GLFWwindow *mGlfwWindow;
	std::string mWindowTitle;
};

}

#endif
