#include "Gizmo2D.h"
#include "GlobalContext.h"
#include "imgui.h"

namespace Thor {

	void Gizmo2D::update() {
	
	}
	
	void Gizmo2D::render() {
		ImVec2 pos = ImGui::GetCursorScreenPos();
    	ImDrawList *draw_list = ImGui::GetWindowDrawList();
		draw_list->AddRectFilled(ImVec2(mPos.x + pos.x, mPos.y + pos.y), ImVec2(mPos.x + pos.x + 40.0f, mPos.y + pos.y + 10.0f), ImColor(170, 100, 123));
		draw_list->AddRectFilled(ImVec2(mPos.x + pos.x, mPos.y + pos.y), ImVec2(mPos.x + pos.x + 10.0f, mPos.y + pos.y + 40.0f), ImColor(100, 170, 123));
	}

	void Gizmo2D::setPos(const glm::vec2 &pos) {
		mPos = pos;	
	}

}
