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
public:
	Window &getWindow();
public:
	Application(int argc, char *argv[]);
	~Application();
	Keyboard &getKeyboard();
	bool init();
	void process();
	bool closeRequested();
	glm::vec2 getViewSize();
};

}

#endif
