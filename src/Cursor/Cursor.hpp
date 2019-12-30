#pragma once

#include <glm/glm.hpp>

#include "OpenGL/CubesGroup_WithoutMaterialIndices.hpp"

class Cursor {
public:
	Cursor() = default;
	~Cursor() = default;

	void draw();

	inline const glm::ivec3& getPosition() const { return m_position; }
	inline const glm::ivec3& getCubeJustBeforePosition() const { return m_cubeJustBeforePosition; }
	void setPosition(const glm::ivec3& newPos);
	void setCubeJustBeforePosition(const glm::ivec3& newPos);
	void translate(const glm::ivec3& dl);

private:
	glm::ivec3 m_position;
	glm::ivec3 m_cubeJustBeforePosition;
	CubesGroup_WithoutMaterialIndices m_selectedCubes;
};