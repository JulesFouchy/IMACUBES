#pragma once

#include <string>
#include "Material/Material.hpp"
#include "OpenGL/CubesGroup.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Uniform/UniformDescription.hpp"

class MaterialsForAGivenShader {
    friend class MaterialsManager;

public:
    MaterialsForAGivenShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, int shaderIndex);
    MaterialsForAGivenShader(const MaterialsForAGivenShader& other);
    MaterialsForAGivenShader(MaterialsForAGivenShader&& other) noexcept;
    ~MaterialsForAGivenShader();

    void draw();
    void draw_WithoutBindingShader();
    void addMaterial();

    void reloadShader();

    void ImGui_ListOfMaterials();

    Shader&       shader();
    inline size_t shaderLID() { return m_shaderLID; }

private:
    void sendUniforms();

    void parseShaderAndCreateUniformDescriptions(const std::string& fragmentFilepath);
    void updateMaterialsLayout();

private:
    size_t                           m_shaderLID;
    CubesGroup                       m_cubes;
    std::vector<UniformDescription*> m_structLayout;
    std::vector<Material>            m_materials;

    std::string m_name;
    int         m_shaderIndex;
};