#pragma once
#include <glm/glm.hpp>

class CubesMapIterator {
public:
	CubesMapIterator();
	~CubesMapIterator()=default;
	

	glm::vec3& operator*();
	void operator++();
	bool operator!=(const CubesMapIterator& it);


private:
	int m_index;

};