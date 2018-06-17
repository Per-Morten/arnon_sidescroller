/// ArnonSidescroller 2018
/// Jun 17th 2018 - Add tesselation shaders

/*
 * A shader object is the object file resulting
 * from compiling a shader. It can be attached
 * to ShaderPrograms to create usable programs.
 */

#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include <cstdint>
#include <fstream>
#include <filesystem>
#include <string>

// Defines the type of a shader, all enum values taken from glCore45.h
enum class EShaderType : uint16_t
{
    FragmentShader = 0x8B30,
    VertexShader   = 0x8B31,
    TessEvalShader = 0x8E87,
    TessCtrlShader = 0x8E88
};

class ShaderObject final
{
private:
    // The OpenGL Name
    uint32_t m_name = 0;

public:
    ShaderObject() = default;

    ShaderObject(const std::string& shaderSourceCode, EShaderType type);

    ShaderObject(std::ifstream& shaderSourceFile, EShaderType type);

    ShaderObject(const std::filesystem::path& filepath, EShaderType type);

    ShaderObject(ShaderObject&& other)noexcept;

    ShaderObject& operator=(ShaderObject&& other) noexcept;

    ~ShaderObject();

    // ShaderProgram is a sensible friend since it needs to acces m_name to attach
    friend class ShaderProgram;

    // Load the shader source from a file
    void loadFromFile(std::ifstream& file, EShaderType type);

    // Load the shader source from a string
    void loadFromString(const std::string& sourceCode, EShaderType type);

    // Return true if the ShaderObject refers to a valid OpenGL object
    bool isValid() const;

private:
    // Compile the given shader source code
    bool compile(const char* shaderSource, EShaderType type);

    // Validate the compiled shader to ensure nothing went wrong
    bool validate();
};


#endif // SHADEROBJECT_H
