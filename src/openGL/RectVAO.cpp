#include "rectVAO.hpp"

#include "Locator/Locate.hpp"
#include "Renderer/Renderer.hpp"

#include "Debugging/Log.hpp"

RectVAO::RectVAO(float aspectRatio, CoordinateSystem coordSystem)
{
	initialize(aspectRatio, coordSystem);
}

void RectVAO::initialize(float aspectRatio, CoordinateSystem coordSystem) {
	initialize(-0.5 * aspectRatio, 0.5 * aspectRatio, -0.5, 0.5, aspectRatio, coordSystem);
}

void RectVAO::initialize(float minX, float maxX, float minY, float maxY, float aspectRatio, CoordinateSystem coordSystem)
{
	// Vertex Array
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	// Vertex buffer

	float texCoordMinX;
	float texCoordMaxX;
	float texCoordMinY;
	float texCoordMaxY;
	switch (coordSystem) {
	case ZERO_TO_ONE__ZERO_TO_ONE:
		texCoordMinX = 0.0f;
		texCoordMaxX = 1.0f;
		texCoordMinY = 0.0f;
		texCoordMaxY = 1.0f;
		break;
	case MINUS_RATIO_TO_RATIO__MINUS_ONE_TO_ONE:
		texCoordMinX = -aspectRatio;
		texCoordMaxX =  aspectRatio;
		texCoordMinY = -1.0f;
		texCoordMaxY =  1.0f;
		break;
	default:
		spdlog::warn("[RectVAO::initialize] Unkown coordinate system !");
	}

	float vertices[] = {
			//Position                   TexCoord
	  minX, minY,   texCoordMinX, texCoordMinY,
	  minX, maxY,   texCoordMinX, texCoordMaxY,
	  maxX, maxY,   texCoordMaxX, texCoordMaxY,
	  maxX, minY,   texCoordMaxX, texCoordMinY,
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);

	// Vertex attributes
		// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float)));

	// Index buffer
	unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2
	};
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

RectVAO::~RectVAO() {
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteVertexArrays(1, &m_vertexArray);
}

void RectVAO::binddrawunbind() {
	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}