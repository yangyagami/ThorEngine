#include "Gizmo2D.h"
#include "GlobalContext.h"
#include "imgui.h"
#include "spdlog/spdlog.h"

namespace Thor {

	void Gizmo2D::update() {
	
	}
	
	void Gizmo2D::render() {
	    ImVec2 mousePos = ImGui::GetMousePos();
		ImVec2 screenPos = ImGui::GetCursorScreenPos();
    	ImDrawList *draw_list = ImGui::GetWindowDrawList();
		ImVec2 pos(mPos.x + screenPos.x, mPos.y + screenPos.y);
		ImVec2 size(30.0f, 30.0f);
		ImVec2 anchor(0.5f, 0.5f);

		spdlog::set_level(spdlog::level::debug); // Set global log level to debug
		if (mousePos.x > pos.x && mousePos.x < pos.x + size.x && mousePos.y > pos.y && mousePos.y < pos.y + size.y) {
			if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
				spdlog::debug("selected");
			}
		}
		
		draw_list->AddRectFilled(ImVec2(pos.x - size.x * anchor.x, pos.y - size.y * anchor.y), ImVec2(mPos.x + pos.x + size.x * anchor.x, mPos.y + pos.y + size.y * anchor.y), ImColor(0, 180, 23));
	}

	void Gizmo2D::setPos(const glm::vec2 &pos) {
		mPos = pos;	
	}

}
