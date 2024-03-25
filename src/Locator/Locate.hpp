#pragma once

class MaterialsManager;
class History;
enum class HistoryType;
class CubesMap;
class ShaderLibrary;
class Renderer;
class LightsManager;
class Camera;

class Locate {
public:
    static MaterialsManager& materialsManager();
    static History&          history(HistoryType type);
    static CubesMap&         cubesMap();
    static ShaderLibrary&    shaderLibrary();
    static Renderer&         renderer();
    static LightsManager&    lightsManager();
    static Camera&           camera();
};