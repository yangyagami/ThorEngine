#ifndef THOR_KEYBOARD_H
#define THOR_KEYBOARD_H

#include <map>

#include "Window.h"

namespace Thor {
class Keyboard {
private:
	std::map<int, int> mKeyStatus;
	Window *mWindow;
public:
	Keyboard(Window *window);
public:
	bool isKeyPressed(int key);
	bool isKeyReleased(int key);
	bool isKeyJustPressed(int key);
	bool isKeyJustReleased(int key);
};
}

#endif 
