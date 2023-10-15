#include <algorithm>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "Camera2D.h"
#include "Editor.h"
#include "Object.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "OpenglTexture2D.h"
#include "GlobalContext.h"
#include "Camera2DComponent.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Thor {
    Editor::Editor() : mIO(nullptr), mSceneTexture(nullptr), mDefaultScene(), mSelectedObj(nullptr) {
    	// Setup Dear ImGui context
    	IMGUI_CHECKVERSION();
    	ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO(); (void)io;
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		mIO = &io;
		std::fill(mBackgroundColor.begin(), mBackgroundColor.end(), 0);
	}
	
	Editor::~Editor() {
    	// Cleanup
    	ImGui_ImplOpenGL3_Shutdown();
    	ImGui_ImplGlfw_Shutdown();
    	ImGui::DestroyContext();	
	}
	
	bool Editor::init() {
		auto &instance = GlobalContext::instance;
		auto glfwWindow = instance->app.getWindow().getGLFWWindow();
		auto &app = instance->app;
		auto &renderer = instance->renderer2D;
		auto &sceneManager = instance->sceneManager;
		auto &registry = instance->registry;
    	// Setup Dear ImGui style
    	ImGui::StyleColorsDark();
    	//ImGui::StyleColorsLight();

    	// Setup Platform/Renderer backends
    	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    	ImGui_ImplOpenGL3_Init("#version 460");

		glm::vec2 viewSize = app.getViewSize();
		mSceneTexture = Texture2D::create(nullptr, viewSize.x, viewSize.y, 3);
		renderer->setRenderToTexture(mSceneTexture);

		auto defaultCamera = new Camera2D();
		defaultCamera->init();
		auto testObj = new Object();
		registry.emplace<SpriteComponent>(testObj->entity, "test.png");
		registry.emplace<TransformComponent>(testObj->entity, glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
		testObj->init();
		mDefaultScene.addObject(defaultCamera);
		mDefaultScene.addObject(testObj);
		
		sceneManager.switchScene(&mDefaultScene);
		return true;
	}
	
	void Editor::update() {
		auto &instance = GlobalContext::instance;
		auto &renderer = instance->renderer2D;
		auto textureSize = mSceneTexture->getSize();
		auto &app = instance->app;
		if (app.getViewSize().x != textureSize.x && app.getViewSize().y != textureSize.y) { 
			mSceneTexture.reset();
			mSceneTexture = Texture2D::create(nullptr, app.getViewSize().x, app.getViewSize().y, 3);
			renderer->setRenderToTexture(mSceneTexture);
		}
		renderer->setClearColor(glm::vec4(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2], mBackgroundColor[3]));
	}
	
	void Editor::render() {
		auto &instance = GlobalContext::instance;
		auto &renderer = instance->renderer2D;
		//Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
     	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		ImGui::PopStyleVar(2);
		drawWindow("Dockspace", [&](){
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));

			drawWindow("Objects", [&](){
				ImGui::Button("new object");
				ImGui::SeparatorText("");
				auto currentSceneObjects = mDefaultScene.getObjects();
				static std::string selected = "";
				for (auto &&[name, obj] : currentSceneObjects) {
					bool isSelected = false;
					if (selected == name) isSelected = true;
					if (ImGui::Selectable(name.c_str(), isSelected)) {
						selected = name;
						mSelectedObj = obj;
						ImGui::SetItemDefaultFocus();
					}
				}
			});

			drawWindow("Files", [](){});
	
			drawWindow("Scene", [&](){
				// we access the ImGui window size
				const float windowWidth = ImGui::GetContentRegionAvail().x;
				const float windowHeight = ImGui::GetContentRegionAvail().y;

				// we get the screen position of the window
				ImVec2 pos = ImGui::GetCursorScreenPos();
				auto &openglTexture2D = *(dynamic_cast<OpenglTexture2D*>(mSceneTexture.get()));
				ImGui::GetWindowDrawList()->AddImage(
					(void *)(intptr_t)openglTexture2D.getID(), 
					ImVec2(pos.x, pos.y), 
					ImVec2(pos.x + windowWidth, pos.y + windowHeight), 
					ImVec2(0, 1), 
					ImVec2(1, 0)
        		);

				mGizmo2D.render();
			});

			drawWindow("Components", [&](){
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
				if (mSelectedObj != nullptr) {
					drawCamera2DComponent(mSelectedObj);
					drawTransformComponent(mSelectedObj);
				}
			});
		
			drawWindow("DebugInfo", [&](){
				ImGui::Text("batchtimes = %d", renderer->getBatchTimes());
			});
		}, window_flags);

        // Rendering
        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	}

	void Editor::drawWindow(const std::string &windowName, std::function<void()> callback, ImGuiWindowFlags flags) {
		ImGui::Begin(windowName.c_str(), nullptr, flags);
		callback();
		ImGui::End();
    }

    void Editor::drawCamera2DComponent(Object *object) {
		auto &registry = GlobalContext::instance->registry;
		auto view = registry.view<Camera2DComponent>();
		for (auto entity : view) {
			if (entity == object->entity) {
				auto &cameraComponent = view.get<Camera2DComponent>(object->entity);
				ImGui::Begin("Camera2D");
				ImGui::InputFloat2("position", glm::value_ptr(cameraComponent.position));
				ImGui::InputFloat("rotation", &cameraComponent.rotation);
				ImGui::End();
			}
		}
    }

	void Editor::drawTransformComponent(Object *object) {
		auto &registry = GlobalContext::instance->registry;
		auto view = registry.view<TransformComponent>();
		for (auto entity : view) {
			if (entity == object->entity) {
				auto &transformComponent = view.get<TransformComponent>(object->entity);
				ImGui::Begin("Transform");
				ImGui::InputFloat2("position", glm::value_ptr(transformComponent.position));
				ImGui::InputFloat2("scale", glm::value_ptr(transformComponent.scale));
				ImGui::End();
			}
		}
	}

}

