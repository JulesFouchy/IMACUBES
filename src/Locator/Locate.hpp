#pragma once

class MaterialsManager;
class History;
enum class HistoryType;
class CubesMap;
class ShaderLibrary;
class UniformUpdateList;
class Renderer;

class Locate {
public:
	static MaterialsManager& materialsManager();
	static History& history(HistoryType type);
	static CubesMap& cubesMap();
	static ShaderLibrary& shaderLibrary();
	static UniformUpdateList& cameraUniforms();
	static UniformUpdateList& lightUniforms();
	static Renderer& renderer();
};