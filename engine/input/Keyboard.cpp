#include "Keyboard.h"

namespace Thor {

	Keyboard::Keyboard(Window *window) : mWindow(window) {
	
	}

	bool Keyboard::isKeyPressed(int key) {
		int state = mWindow->getKeyState(key);

		mKeyStatus[key] = state;
		
		return (state == GLFW_PRESS);
	}
	
	bool Keyboard::isKeyReleased(int key) {
		int state = mWindow->getKeyState(key);

		mKeyStatus[key] = state;

		return (state == GLFW_RELEASE);
	}
	
	bool Keyboard::isKeyJustPressed(int key) {
		bool ret = false;

		int state = mWindow->getKeyState(key);

		if (state == GLFW_PRESS && mKeyStatus[key] == GLFW_RELEASE) ret = true;

		mKeyStatus[key] = state;

		return ret;
	}
	
	bool Keyboard::isKeyJustReleased(int key) {
		bool ret = false;

		int state = mWindow->getKeyState(key);

		if (state == GLFW_RELEASE && mKeyStatus[key] == GLFW_PRESS) ret = true;

		mKeyStatus[key] = state;

		return ret;
	}

}
