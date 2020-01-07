#include "Tool_MengerSponge.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

#include <imgui/imgui.h>

void Tool_MengerSponge::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	computeBoundingBox();
	mengerSponge(m_bbox, whatToDoWithPos);
	//for (const glm::ivec3& pos : m_bbox) {
	//	if (menger(pos-m_bbox.minCorner()))
	//		whatToDoWithPos(pos);
	//}
}

bool Tool_MengerSponge::menger(const glm::ivec3& pos) {
	/*int x = 0;
	int y = 0;
	int z = 0;
	int X = m_radiuses.x * 2 + 1;
	int Y = m_radiuses.y * 2 + 1;
	int Z = m_radiuses.y * 2 + 1;
	int nbIter = MyMaths::LogInt(X, 3);
	for (int n = 0; n < nbIter; ++n) {
		int xID = (pos.x - x) * 3 / (X - x);
		int yID = (pos.y - y) * 3 / (Y - y);
		int zID = (pos.z - z) * 3 / (Z - z);
		if ((xID == 1 && yID == 1) || (xID == 1 && zID == 1) || (zID == 1 && yID == 1))
			return false;
		else {
			int dlX = (X - x) / 3;
			x += xID * dlX;
			X -= (2 - xID) * dlX;
			int dlY = (Y - y) / 3;
			y += yID * dlY;
			Y -= (2 - yID) * dlY;
			int dlZ = (Z - z) / 3;
			z += zID * dlZ;
			Z -= (2 - zID) * dlZ;
		}
	}*/
	return true;
}


void Tool_MengerSponge::mengerSponge(const BoundingBox& bbox, std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	Log::log((glm::vec3)bbox.size());
	if (bbox.size() == glm::ivec3(1)) {
		whatToDoWithPos(bbox.minCorner());
	}
	else {
		glm::ivec3 dlToCorner0 = bbox.size() / 3 - glm::ivec3(1) + (bbox.size() % 3)/2 * glm::ivec3(1);
		glm::ivec3 dlToCorner1 = bbox.size() / 3 - glm::ivec3(1) + bbox.size() % 3 % 2 * glm::ivec3(1);
		glm::ivec3 dlToCorner2 = bbox.size() / 3 - glm::ivec3(1) + (bbox.size() % 3)/2 * glm::ivec3(1);
		// bot face
		glm::ivec3 corner = bbox.minCorner();
		mengerSponge(BoundingBox(corner, corner + dlToCorner0, CORNERS), whatToDoWithPos);
		corner = bbox.minCorner() + dlToCorner0.x;
		mengerSponge(BoundingBox(corner, corner + dlToCorner1, CORNERS), whatToDoWithPos);
		corner = bbox.minCorner() + dlToCorner1.x;
		mengerSponge(BoundingBox(corner, corner + dlToCorner2, CORNERS), whatToDoWithPos);
	}
}

void Tool_MengerSponge::ImGui_Menu() {
	Tool_Shape_Radial::ImGui_Menu();
	static int perfectRadiuseID = 1;
	if (ImGui::BeginPopupContextItem("Set perfect radius"))
	{
		/*const char* listbox_items[] = { "4", "13", "40" };
		if (ImGui::ListBox("Set radius", &perfectRadiuseID, listbox_items, 3)) {
			switch (perfectRadiuseID)
			{
			case 0:
				m_radiuses = glm::ivec3(4);
				break;
			case 1:
				m_radiuses = glm::ivec3(13);
				break;
			case 2:
				m_radiuses = glm::ivec3(40);
				break;
			default:
				break;
			}
		}*/
		ImGui::EndPopup();
	}
}