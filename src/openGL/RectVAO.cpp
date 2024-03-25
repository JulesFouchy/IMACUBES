#include "rectVAO.hpp"
#include "Debugging/Log.hpp"
#include "Debugging/gl-exception.h"
#include "Locator/Locate.hpp"
#include "Renderer/Renderer.hpp"

RectVAO::RectVAO(float minXScreenSpace, float maxXScreenSpace, float minYScreenSpace, float maxYScreenSpace)
{
    // Vertex Array
    GLCall(glGenVertexArrays(1, &m_vertexArray));
    GLCall(glBindVertexArray(m_vertexArray));

    // Vertex buffer
    float texCoordMinX = 0.0f;
    float texCoordMaxX = 1.0f;
    float texCoordMinY = 0.0f;
    float texCoordMaxY = 1.0f;

    float vertices[] = {
        // Position                       TexCoord
        minXScreenSpace,
        minYScreenSpace,
        texCoordMinX,
        texCoordMinY,
        minXScreenSpace,
        maxYScreenSpace,
        texCoordMinX,
        texCoordMaxY,
        maxXScreenSpace,
        maxYScreenSpace,
        texCoordMaxX,
        texCoordMaxY,
        maxXScreenSpace,
        minYScreenSpace,
        texCoordMaxX,
        texCoordMinY,
    };

    GLCall(glGenBuffers(1, &m_vertexBuffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), vertices, GL_STATIC_DRAW));

    // Vertex attributes
    // Position
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
    // Texture coordinates
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float))));

    // Index buffer
    unsigned int indices[] = {
        0, 2, 1,
        0, 3, 2
    };
    GLCall(glGenBuffers(1, &m_indexBuffer));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    // Unbind
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
}
RectVAO::~RectVAO()
{
    GLCall(glDeleteBuffers(1, &m_vertexBuffer));
    GLCall(glDeleteBuffers(1, &m_indexBuffer));
    GLCall(glDeleteVertexArrays(1, &m_vertexArray));
}

void RectVAO::binddrawunbind()
{
    GLCall(glBindVertexArray(m_vertexArray));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer));
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    GLCall(glBindVertexArray(0));
}