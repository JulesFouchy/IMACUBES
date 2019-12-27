#include "CubesMapIterator.hpp"



glm::vec3& CubesMapIterator::operator*() {
	return glm::vec3(0);
}


void CubesMapIterator::operator++() {
	m_index++;
}


bool  CubesMapIterator::operator!=(const CubesMapIterator& it) {
	return m_index != it.m_index;
}