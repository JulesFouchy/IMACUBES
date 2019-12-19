#pragma once

#include <glm/glm.hpp>

#include "OpenGL/CubesGroup_WithoutMaterialIndices.hpp"

class Cursor {
public:
	Cursor(int x, int y, int z);
	~Cursor() = default;

	void draw();

	inline const glm::ivec3& getPosition() const { return m_position; }
	void setPosition(const glm::ivec3& newPos);

private:
	glm::ivec3 m_position;
	CubesGroup_WithoutMaterialIndices m_selectedCubes;
};