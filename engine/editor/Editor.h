#ifndef THOR_EDITOR_H
#define THOR_EDITOR_H

#include <memory>
#include <array>
#include <functional>

#include "imgui_impl_glfw.h"
#include "Renderer2D.h"
#include "Scene.h"

namespace Thor {
class Editor {
private:
	ImGuiIO *mIO;
	std::array<float, 4> mBackgroundColor;
	std::unique_ptr<Texture2D> mSceneTexture;
public:
	void drawWindow(const std::string &windowName, std::function<void()> callback, ImGuiWindowFlags flags = 0);
public:
	Editor();
	~Editor();
	bool init();
	void update();
	void render();
};
}

#endif
