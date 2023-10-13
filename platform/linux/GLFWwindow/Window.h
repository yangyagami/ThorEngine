#include <string>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

namespace Thor {

class Window {
public:
	Window();
	Window(std::string title);
	Window(int width, int height, std::string title);
	~Window();
	bool init();
	bool shouldClose();
	void swapBuffers();
	void pollEvents();
	glm::vec2 getSize();
	GLFWwindow *getGLFWWindow();
private:
	GLFWwindow *mGlfwWindow;
	int mWidth;
	int mHeight;
	std::string mWindowTitle;
};

}
