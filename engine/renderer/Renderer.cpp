#include "Renderer.h"
#include "spdlog/spdlog.h"

namespace Thor {
	Renderer::Renderer() {
	
	}
	
	Renderer::~Renderer() {
	
	}
	
	bool Renderer::init() {
		spdlog::info("Renderer init success");	
		return true;	
	}
	
	void Renderer::beginBatch() {
	
	}
	
	void Renderer::endBatch() {
	
	}
	
	void Renderer::drawRectangle(const Vec2 &pos, const Vec2 &size, const Vec4 &color) {
	
	}

}
