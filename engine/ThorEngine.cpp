#include "ThorEngine.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "Renderer2D.h"
#include "Texture2D.h"

namespace Thor {
std::unique_ptr<Texture2D> texture;
	Engine::Engine(int argc, char *argv[]) : mApp(argc, argv), mEditor(nullptr) {
		spdlog::info("Engine created");
	}

	bool Engine::init() {
		if (mApp.init() == false) {
			spdlog::error("Cannot init application!");
			return false;
		}	
		mRenderer = Renderer2D::create();
		if (mRenderer->init() == false) {
			spdlog::error("Cannot init renderer!");
			return false;
		}
		auto glfwWindow = mApp.getWindow().getGLFWWindow();
		mEditor = std::make_unique<Editor>(glfwWindow, mRenderer);
		mEditor->init();
		spdlog::info("Engine init success.");

		texture = Texture2D::create("test.png");

		return true;
	}

	void Engine::update() {
		// logic stuff	
	}
	
	void Engine::render() {
		mRenderer->drawRectangle(glm::vec2(0.5f, 0.5f), glm::vec2(0.05f, 0.05f), glm::vec4(1.0f, 0.7f, 1.0f, 1.0f));
		mRenderer->drawRectangle(glm::vec2(0.2f, 0.2f), glm::vec2(0.05f, 0.05f), glm::vec4(0.2f, 0.7f, 1.0f, 1.0f));
		mRenderer->drawTriangle(glm::vec2(0.6f, 0.6f), glm::vec2(0.7f, 0.6f), glm::vec2(0.7f, 0.8f), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f));
		mRenderer->drawCircle(glm::vec2(0.0f, 0.0f), 0.3f, glm::vec4(1.0f, 0.5f, 1.0f, 1.0f), 36);
		mRenderer->drawCircle(glm::vec2(-0.4f, -0.4f), 0.3f, glm::vec4(1.0f, 0.5f, 0.7f, 1.0f), 36);
		mRenderer->drawTexture(texture, glm::vec2(0.0f, 0.0f));
	}

	int Engine::run() {
		spdlog::info("Engine running...");
		while (!mApp.closeRequested()) {
			update();
			mEditor->update();

			mRenderer->beginBatch();
			render();
			mRenderer->endBatch();

			mEditor->render();

			mApp.process();
		}
		return 0;
	}

	Engine::~Engine() {
		spdlog::info("Engine destroyed.");	
	}

}
