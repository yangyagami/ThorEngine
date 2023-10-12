#ifndef THOR_APPLICATION_H
#define THOR_APPLICATION_H

#include "Window.h"
#include "glm/glm.hpp"

namespace Thor {

class Application {
private:
	Window mWindow;
public:
	Application(int argc, char *argv[]);
	~Application();
	bool init();
	void process();
	bool closeRequested();
	glm::vec2 getViewSize();
};

}

#endif
