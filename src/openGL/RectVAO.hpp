#pragma once

#include <glad/glad.h>

enum CoordinateSystem {
	ZERO_TO_ONE__ZERO_TO_ONE,
	MINUS_RATIO_TO_RATIO__MINUS_ONE_TO_ONE
};

class RectVAO {
public:
	RectVAO() = default;
	RectVAO(float aspectRatio, CoordinateSystem coordSystem);
	void initialize(float minX, float maxX, float minY, float maxY, float aspectRatio, CoordinateSystem coordSystem);
	void initialize(float aspectRatio, CoordinateSystem coordSystem);
	~RectVAO();

	void binddrawunbind();

private:
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	GLuint m_vertexArray;
};