#pragma once

#include "BoundingBoxIterator.hpp"

enum BboxGenerationMode {
    CENTER_SIZE,
    CENTER_RADIUS_EVENSIZE,
    CORNERS
};

class BoundingBox {
    friend class BoundingBoxIterator;

public:
    BoundingBox();
    BoundingBox(const glm::ivec3& v0, const glm::ivec3& v1, BboxGenerationMode mode);
    ~BoundingBox() = default;

    BoundingBoxIterator begin();
    BoundingBoxIterator end();

    bool isXValid(int x) const;
    bool isYValid(int y) const;
    bool isZValid(int z) const;
    bool isCubeInside(const glm::ivec3& pos) const;

    inline const glm::ivec3& minCorner() const { return m_minCorner; }
    inline const glm::ivec3& maxCorner() const { return m_maxCorner; }

    inline const glm::ivec3& size() const { return m_size; }
    inline const glm::ivec3& center() const { return m_center; }
    inline const glm::vec3&  centerFloat() const { return m_centerFloat; }

private:
    void computeInfos();

    int        clampX(int x);
    int        clampY(int y);
    int        clampZ(int z);
    glm::ivec3 clamp(const glm::ivec3& v);

private:
    glm::ivec3 m_minCorner;
    glm::ivec3 m_maxCorner;

    glm::ivec3 m_size;
    glm::ivec3 m_center;
    glm::vec3  m_centerFloat;
};