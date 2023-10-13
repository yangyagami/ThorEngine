#ifndef THOR_EDITOR_H
#define THOR_EDITOR_H

#include <memory>
#include <array>

#include "imgui_impl_glfw.h"
#include "Renderer2D.h"

namespace Thor {
class Editor {
private:
	ImGuiIO *mIO;
	std::unique_ptr<Renderer2D> &mRenderer2D;
	GLFWwindow *mWindow;
	std::array<float, 4> mBackgroundColor;
public:
	Editor(GLFWwindow *glfwWindow, std::unique_ptr<Renderer2D> &renderer2D);
	~Editor();
	bool init();
	void update();
	void render();
};
}

#endif
