#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

class Shader {
public:
    Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath, bool compileShader = true, const std::vector<std::string>& lookForInFS = {}, const std::vector<std::string>& replaceWithInFS = {}, const std::vector<std::string>& lookForInVS = {}, const std::vector<std::string>& replaceWithInVS = {});
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept;
    ~Shader();

    void bind() const;
    void compile(const std::vector<std::string>& lookForInFS = {}, const std::vector<std::string>& replaceWithInFS = {}, const std::vector<std::string>& lookForInVS = {}, const std::vector<std::string>& replaceWithInVS = {});
    void compile(const std::string& lookForInFS, const std::string& replaceWithInFS, const std::string& lookForInVS = "", const std::string& replaceWithInVS = "");

    inline bool createdSuccessfully() const { return m_bCreatedSuccessfully; }

    inline int                getID() const { return m_shaderId; }
    inline const std::string& getFragmentFilepath() const { return m_fragmentShaderFilepath; }

    void setUniform1i(const std::string& uniformName, int v);
    void setUniform1f(const std::string& uniformName, float v);
    void setUniform2f(const std::string& uniformName, const glm::vec2& v);
    void setUniform3f(const std::string& uniformName, const glm::vec3& v);
    void setUniform4f(const std::string& uniformName, const glm::vec4& v);
    void setUniformMat4f(const std::string& uniformName, const glm::mat4& mat);

private:
    int          getUniformLocation(std::string uniformName);
    std::string  parseFile(const std::string& filepath, const std::vector<std::string>& lookFor = {}, const std::vector<std::string>& replaceWith = {});
    unsigned int compileShader(unsigned int type, const std::string& source);

private:
    int                                  m_shaderId;
    int                                  m_vsID;
    int                                  m_fsID;
    std::string                          m_vertexShaderFilepath;
    std::string                          m_fragmentShaderFilepath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    bool                                 m_bCreatedSuccessfully;
};