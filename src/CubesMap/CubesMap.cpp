#include "CubesMap.hpp"

CubesMap::CubesMap(size_t width, size_t height, size_t depth)
	: m_width(width), m_height(height), m_depth(depth), m_cubesLocations(m_width * m_height * m_depth, MaterialLocation(-1, -1))
{

}

size_t CubesMap::index1Dfrom3D(glm::ivec3 id3D) {
	return id3D.x + id3D.y * m_width + id3D.y * m_width * m_height;
}