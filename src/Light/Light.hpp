#pragma once

#include <glm/glm.hpp>
#include <string>
#include "OpenGL/Uniform/Uniform.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"

class Light {
    friend class LightsManager;

public:
    Light(const std::string& name = "Ambiant Light", const glm::vec3& color = glm::vec3(1.0f), float intensity = 0.54f, float intensityDragSpeed = 0.01f);
    ~Light() = default;

    virtual void              setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList);
    virtual void              ImGui_Sliders();
    inline const std::string& getName() const { return m_name; }
    inline std::string*       getNamePtr() { return &m_name; }

private:
    std::string m_name;

    Uniform<glm::vec3> m_color;
    Uniform<float>     m_intensity;

    float m_intensityDragSpeed;
};