#include <algorithm>

#include "Editor.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace Thor {
    Editor::Editor(GLFWwindow *glfwWindow, std::unique_ptr<Renderer2D> &renderer2D) : mIO(nullptr), mRenderer2D(renderer2D), mWindow(glfwWindow), mSceneTexture(nullptr) {
    	// Setup Dear ImGui context
    	IMGUI_CHECKVERSION();
    	ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO(); (void)io;
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		mIO = &io;
		std::fill(mBackgroundColor.begin(), mBackgroundColor.end(), 0);

		mSceneTexture = Texture2D::create(nullptr, 800, 600, 4);
	}
	
	Editor::~Editor() {
    	// Cleanup
    	ImGui_ImplOpenGL3_Shutdown();
    	ImGui_ImplGlfw_Shutdown();
    	ImGui::DestroyContext();	
	}
	
	bool Editor::init() {
    	// Setup Dear ImGui style
    	ImGui::StyleColorsDark();
    	//ImGui::StyleColorsLight();

    	// Setup Platform/Renderer backends
    	ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    	ImGui_ImplOpenGL3_Init("#version 460");

		return true;
	}
	
	void Editor::update() {
		mRenderer2D->setClearColor(glm::vec4(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2], mBackgroundColor[3]));
	}
	
	void Editor::render() {
		// Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
		bool show_demo_window = true;

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

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

			drawWindow("Objects", [](){
				ImGui::Button("new object");
				ImGui::SeparatorText("");
				const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
				static int item_current_idx = 0;
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					const bool is_selected = (item_current_idx == n);
					if (ImGui::Selectable(items[n], is_selected))
						item_current_idx = n;

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
			});

			drawWindow("Files", [](){});
	
			drawWindow("Scene", [](){

			});

			drawWindow("Components", [](){});
		
			drawWindow("DebugInfo", [&](){
				ImGui::Text("batchtimes = %d", mRenderer2D->getBatchTimes());
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

}

