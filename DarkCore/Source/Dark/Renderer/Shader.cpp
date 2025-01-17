#include "Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace Dark
{
    Shader::Shader() {}

    Shader::Shader(const std::string& vShader, const std::string& fShader)
    {
        const char* vShaderSource = vShader.c_str();
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // fragment shader
        const char* fShaderSource = fShader.c_str();
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // link shaders
        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, vertexShader);
        glAttachShader(m_shaderProgram, fragmentShader);
        glLinkProgram(m_shaderProgram);
        // check for linking errors
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::Use() const
    {
        glUseProgram(m_shaderProgram);
    }

    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    }
    void Shader::setIntArray(const std::string& name, int* values, int count) const
    {
        glUniform1iv(glGetUniformLocation(m_shaderProgram, name.c_str()), count, values);
    }
    // ------------------------------------------------------------------------
    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}
