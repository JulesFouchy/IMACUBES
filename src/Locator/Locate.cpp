#include "Locate.hpp"
#include "App.hpp"
#include "Camera/Camera.hpp"
#include "CubesMap/CubesMap.hpp"
#include "History/History.hpp"
#include "History/HistoryTypes.hpp"
#include "Light/LightsManager.hpp"
#include "Material/MaterialsManager.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"
#include "Renderer/Renderer.hpp"

MaterialsManager& Locate::materialsManager()
{
    return App::Get().m_cubesMap.materialsManager();
}

History& Locate::history(HistoryType type)
{
    return App::Get().m_histories.getHistory(type);
}

CubesMap& Locate::cubesMap()
{
    return App::Get().m_cubesMap;
}

ShaderLibrary& Locate::shaderLibrary()
{
    return App::Get().m_shaderLibrary;
}

Renderer& Locate::renderer()
{
    return App::Get().m_renderer;
}

LightsManager& Locate::lightsManager()
{
    return App::Get().m_lightsManager;
}

Camera& Locate::camera()
{
    return App::Get().m_camera;
}