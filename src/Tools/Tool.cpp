#include "Tool.hpp"
#include "Helper/File.hpp"
#include "Locator/Locate.hpp"
#include "OpenGL/ShaderLibrary.hpp"

size_t Tool::m_shaderLID;

void Tool::Initialize()
{
    m_shaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_cursor.vert", MyFile::rootDir + "/res/shaders/_toolPreview.frag");
    Locate::shaderLibrary().addSubscriberToList(m_shaderLID, UniformList::Camera);
}

void Tool::showPreview()
{
    Locate::shaderLibrary()[m_shaderLID].bind();
    m_previewGroup.drawWireframe();
}