#include "Tool_MengerSponge.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

#include <imgui/imgui.h>

Tool_MengerSponge::Tool_MengerSponge() {
	m_sizes = glm::ivec3(9);
}

void Tool_MengerSponge::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	computeBoundingBox();
	//spdlog::warn("----------");
	//Log::log((glm::vec3)m_bbox.size());
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
	//Log::separationLine();
	//Log::log((glm::vec3)bbox.size());
	if (bbox.size().x < 3 && bbox.size().y < 3 && bbox.size().z < 3) {
		whatToDoWithPos(bbox.minCorner());
	}
	else {
		glm::ivec3 dlToCorner = bbox.size() / 3;
		glm::ivec3 checkForTwo = glm::ivec3(dlToCorner.x == 2 ? 0 : 1,
			dlToCorner.y == 2 ? 0 : 1,
			dlToCorner.z == 2 ? 0 : 1);
		if (checkForTwo.x * checkForTwo.y * checkForTwo.z != 0) {
			dlToCorner -= glm::ivec3(1) * checkForTwo;
			//glm::ivec3 dlToCorner0 = bbox.size() / 3 - glm::ivec3(1);// + (bbox.size() % 3)/2 * glm::ivec3(1);
			//glm::ivec3 dlToCorner1 = bbox.size() / 3 - glm::ivec3(1);// + bbox.size() % 3 % 2 * glm::ivec3(1);
			//glm::ivec3 dlToCorner2 = bbox.size() / 3 - glm::ivec3(1);// + (bbox.size() % 3)/2 * glm::ivec3(1);
			//Log::log((glm::vec3)dlToCorner0);
			//Log::log((glm::vec3)dlToCorner1);
			//Log::log((glm::vec3)dlToCorner2);
			//Log::log((glm::vec3)dlToCorner);
			// bot face
			glm::ivec3 corner = bbox.minCorner();
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += dlToCorner.x + 1;
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += dlToCorner.x + 1;
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);

			corner = bbox.minCorner() + glm::ivec3(0, 0, dlToCorner.z + 1);
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += 2 * (dlToCorner.x + 1);
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);

			corner = bbox.minCorner() + glm::ivec3(0, 0, 2 * (dlToCorner.z + 1));
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += dlToCorner.x + 1;
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += dlToCorner.x + 1;
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);

			// middle

			corner = bbox.minCorner() + glm::ivec3(0, 1 * (dlToCorner.y + 1), 0);
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += 2 * (dlToCorner.x + 1);
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);

			corner = bbox.minCorner() + glm::ivec3(0, 1 * (dlToCorner.y + 1), 0) + glm::ivec3(0, 0, 2 * (dlToCorner.z + 1));
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += 2 * (dlToCorner.x + 1);
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);

			// top face
			corner = bbox.minCorner() + glm::ivec3(0, 2 * (dlToCorner.y + 1), 0);
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += dlToCorner.x + 1;
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += dlToCorner.x + 1;
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);

			corner = bbox.minCorner() + glm::ivec3(0, 2 * (dlToCorner.y + 1), 0) + glm::ivec3(0, 0, dlToCorner.z + 1);
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += 2 * (dlToCorner.x + 1);
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);

			corner = bbox.minCorner() + glm::ivec3(0, 2 * (dlToCorner.y + 1), 0) + glm::ivec3(0, 0, 2 * (dlToCorner.z + 1));
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += dlToCorner.x + 1;
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
			corner.x += dlToCorner.x + 1;
			mengerSponge(BoundingBox(corner, corner + dlToCorner, CORNERS), whatToDoWithPos);
		}
	}
}

void Tool_MengerSponge::ImGui_Menu() {
	Tool_Shape_Radial::ImGui_Menu();
	static int perfectSizeID = 1;
	if (ImGui::BeginPopupContextItem("Set perfect radius"))
	{
		const char* listbox_items[] = { "9", "27", "81" };
		if (ImGui::ListBox("Set size", &perfectSizeID, listbox_items, 3)) {
			switch (perfectSizeID)
			{
			case 0:
				m_sizes = glm::ivec3(9);
				break;
			case 1:
				m_sizes = glm::ivec3(27);
				break;
			case 2:
				m_sizes = glm::ivec3(81);
				break;
			default:
				break;
			}
		}
		ImGui::EndPopup();
	}
}