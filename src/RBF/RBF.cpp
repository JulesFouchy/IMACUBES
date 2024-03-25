#include "RBF.hpp"
#include "CubesMap/CubesMap.hpp"
#include "Locator/Locate.hpp"

template<>
void RBF<glm::ivec3>::initVectors()
{
    CubesMap& cubesMap = Locate::cubesMap();
    size_t    size     = cubesMap.width() * cubesMap.height() * cubesMap.depth();
    m_values.resize(size);
    m_bWasValueComputed.resize(size, false);
}

size_t RBF<glm::ivec3>::id(const glm::ivec3& v)
{
    CubesMap& cubesMap = Locate::cubesMap();
    return v.x + cubesMap.width() / 2 + (v.y + cubesMap.height() / 2) * cubesMap.width() + (v.z + cubesMap.depth() / 2) * cubesMap.width() * cubesMap.height();
}

template<>
void RBF<glm::ivec2>::initVectors()
{
    CubesMap& cubesMap = Locate::cubesMap();
    size_t    size     = cubesMap.width() * cubesMap.depth();
    m_values.resize(size);
    m_bWasValueComputed.resize(size, false);
}

size_t RBF<glm::ivec2>::id(const glm::ivec2& v)
{
    CubesMap& cubesMap = Locate::cubesMap();
    return v.x + cubesMap.width() / 2 + (v.y + cubesMap.depth() / 2) * Locate::cubesMap().width();
}