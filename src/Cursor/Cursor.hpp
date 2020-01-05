#pragma once

#include <glm/glm.hpp>

#include "OpenGL/CubesGroup_WithoutMaterialIndices.hpp"

#include "CursorPositioner.hpp"
#include <memory>

class Cursor {
public:
	Cursor();
	~Cursor() = default;

	void draw();
	inline void computePosition() { m_cursorPositioner->computePosition(); }
	inline void onWheelScroll(float dl) { m_cursorPositioner->onWheelScroll(dl); }

	inline const glm::ivec3& getPosition() const { return m_position; }
	inline const glm::ivec3& getCubeJustBeforePosition() const { return m_cubeJustBeforePosition; }
	void setPosition(const glm::ivec3& newPos);
	void setCubeJustBeforePosition(const glm::ivec3& newPos);
	void translate(const glm::ivec3& dl);

private:
	template <typename T>
	inline void setCursorPositioner() { m_cursorPositioner = std::make_unique<T>(this); }

private:
	glm::ivec3 m_position;
	glm::ivec3 m_cubeJustBeforePosition;
	CubesGroup_WithoutMaterialIndices m_selectedCubes;

	std::unique_ptr<CursorPositioner> m_cursorPositioner;
};