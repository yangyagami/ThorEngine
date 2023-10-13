#include "Editor.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Thor {

	Editor::Editor(GLFWwindow *glfwWindow, std::unique_ptr<Renderer2D> &renderer2D) : mIO(nullptr), mRenderer2D(renderer2D), mWindow(glfwWindow) {
    	// Setup Dear ImGui context
    	IMGUI_CHECKVERSION();
    	ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO(); (void)io;
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		mIO = &io;
	}
	
	Editor::~Editor() {
	
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

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            ImGui::Begin("Status");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("batchtimes = %d", mRenderer2D->getBatchTimes());
			ImGui::ColorEdit4("BackgroundColor", &mBackgroundColor[0]);

            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }


        // Rendering
        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}

