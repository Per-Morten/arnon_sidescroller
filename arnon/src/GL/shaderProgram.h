/// ArnonSidescroller

/*
 * A shader program consists of various
 * shader objects that are linked together
 * to work as part of the OpenGL pipeline.
 */

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <cstdint>

class ShaderObject;

class ShaderProgram final
{
private:
    // The Program GL Name
    uint32_t m_name = 0;

public:
    ShaderProgram() = default;

    explicit ShaderProgram(const ShaderObject& vertexShader);

    ShaderProgram(const ShaderObject& vertexShader, const ShaderObject& fragmentShader);

    ShaderProgram(ShaderProgram&& other) noexcept;

    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    ~ShaderProgram();

    // Enables the program as the active OpenGL Shader
    void bind() const;

    // Disables the program as the active OpenGL Shader
    void unbind() const;

    // Create and link the program from a vertex and fragment shader
    void create(const ShaderObject& vertexShader, const ShaderObject& fragmentShader);

    // Create and link the program from a vertex shader, using the default fragment shader
    void createFromVertexOnly(const ShaderObject& vertexShader);

    // Check if the current program refers to a valid OpenGL object
    bool isValid() const;

private:
    // Link the program with the provided shaders
    bool link(const ShaderObject& vertexShader, const ShaderObject& fragmentShader);

    // Validate that linking worked out
    bool validate();

};

#endif // SHADERPROGRAM_H
