#ifndef THOR_APPLICATION_H
#define THOR_APPLICATION_H

#include "Window.h"
#include "glm/glm.hpp"
#include "Keyboard.h"

namespace Thor {

class Application {
private:
	Window mWindow;
	Keyboard mKeyboard;
	glm::vec2 mViewSize;
public:
	Window &getWindow();
public:
	Application(int argc, char *argv[]);
	~Application();
	Keyboard &getKeyboard();
	bool init();
	void setViewSize(const glm::vec2 &size);
	void process();
	bool closeRequested();
	glm::vec2 getViewSize();
};

}

#endif
