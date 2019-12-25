#pragma once

#include "SaveBuffer.hpp"

class SaveBufferMultisampled : public SaveBuffer {
public:
	SaveBufferMultisampled(int width, int height, int nbSamples);
	~SaveBufferMultisampled();

private:
	void createAttachments(int width, int height, int nbSamples);
	unsigned char* getPixelsPtr() override;

private:
	GLuint m_BLITframeBufferId;
	GLuint m_BLITcolorRenderBufferID;
};