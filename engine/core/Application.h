#ifndef THOR_APPLICATION_H
#define THOR_APPLICATION_H

#include "Window.h"

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
};

}

#endif
