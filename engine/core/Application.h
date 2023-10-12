#ifndef THOR_APPLICATION_H
#define THOR_APPLICATION_H

#include "Window.h"
#include "Vec.hpp"

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
	Vec2 getViewSize();
};

}

#endif
