#pragma once

#include <glad/glad.h>

enum CoordinateSystem {
    ZERO_TO_ONE__ZERO_TO_ONE,
    MINUS_RATIO_TO_RATIO__MINUS_ONE_TO_ONE
};

class RectVAO {
public:
    RectVAO(float minXScreenSpace, float maxXScreenSpace, float minYScreenSpace, float maxYScreenSpace);
    ~RectVAO();

    void binddrawunbind();

private:
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    GLuint m_vertexArray;
};