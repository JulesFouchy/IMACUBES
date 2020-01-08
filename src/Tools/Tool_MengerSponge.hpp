#pragma once

#include "Tool_Shape_Radial.hpp"

class Tool_MengerSponge : public Tool_Shape_Radial {
public:
	Tool_MengerSponge();
	~Tool_MengerSponge() = default;

	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;

private:
	void mengerSponge(const BoundingBox& bbox, std::function<void(const glm::ivec3 & pos)> whatToDoWithPos);
	void ImGui_Menu() override;

	bool menger(const glm::ivec3& pos);
};