#include "Tool_MengerSponge.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

Tool_MengerSponge::Tool_MengerSponge()
{
	m_radiuses = glm::ivec3(13);
}

void Tool_MengerSponge::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	computeBoundingBox();
	for (const glm::ivec3& pos : m_bbox) {
		if (menger(pos-m_bbox.minCorner()))
			whatToDoWithPos(pos);
	}
}

bool Tool_MengerSponge::menger(const glm::ivec3& pos) {
	int x = 0;
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
	}
	return true;
}