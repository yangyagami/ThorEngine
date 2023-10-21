#ifndef THOR_EDITOR_H
#define THOR_EDITOR_H

#include <memory>
#include <array>
#include <functional>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_impl_glfw.h"
#include "Renderer2D.h"
#include "Camera2D.h"

namespace Thor {
class Editor {
private:
	ImGuiIO *mIO;
	std::array<float, 4> mBackgroundColor;
	std::unique_ptr<Texture2D> mSceneTexture;
	Object *mSelectedObj;
public:
	void drawWindow(const std::string &windowName, std::function<void()> callback, ImGuiWindowFlags flags = 0);
	void drawCamera2DComponent(Object *object);
	void drawTransformComponent(Object *object);
public:
	Editor();
	~Editor();
	bool init();
	void update();
	void render();
};
}

#endif
