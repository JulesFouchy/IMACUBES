#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "CursorPositioner.hpp"
#include "OpenGL/CubesGroup_WithoutMaterialIndices.hpp"

class Cursor {
    friend class CursorPositioner_OnHoveredCube;
    friend class CursorPositioner_AtAFixedDistance;

public:
    Cursor();
    ~Cursor() = default;

    void        draw();
    inline void computePosition() { m_cursorPositioner->computePosition(); }
    inline void onWheelScroll(float dl) { m_cursorPositioner->onWheelScroll(dl); }

    void switchCursorPositioner();

    inline const glm::ivec3& getPosition() const { return m_position; }
    inline const glm::ivec3& getCubeJustBeforePosition() const { return m_cubeJustBeforePosition; }
    inline const glm::ivec3& getNormal() const { return m_normalOfHoveredFace; }
    void                     setPosition(const glm::ivec3& newPos);
    void                     setCubeJustBeforePosition(const glm::ivec3& newPos);
    void                     translate(const glm::ivec3& dl);

private:
    template<typename T>
    inline void setCursorPositioner()
    {
        m_cursorPositioner     = std::make_unique<T>(this);
        m_bOnHoveredIsSelected = !m_bOnHoveredIsSelected;
    }

private:
    glm::ivec3                        m_position;
    glm::ivec3                        m_cubeJustBeforePosition;
    glm::ivec3                        m_normalOfHoveredFace;
    CubesGroup_WithoutMaterialIndices m_selectedCubes;

    std::unique_ptr<CursorPositioner> m_cursorPositioner;
    bool                              m_bOnHoveredIsSelected;
};