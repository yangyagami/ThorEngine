#include <string>
#include <GLFW/glfw3.h>

#include "Vec.hpp"

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
	Vec2 getSize();
private:
	int mWidth;
	int mHeight;
	GLFWwindow *mGlfwWindow;
	std::string mWindowTitle;
};

}
