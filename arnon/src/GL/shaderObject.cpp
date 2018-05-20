#include "shaderObject.h"
#include "debug/arnlog.h"

#include <iostream>
#include <sstream>

#include "glCore45.h"

ShaderObject::ShaderObject(const std::string& shaderSourceCode, EShaderType type)
{
    loadFromString(shaderSourceCode, type);
}

ShaderObject::ShaderObject(std::ifstream& shaderSourceFile, EShaderType type)
{
    loadFromFile(shaderSourceFile, type);
}

ShaderObject::ShaderObject(ShaderObject&& other) noexcept : m_name(other.m_name)
{
    other.m_name = 0;
}

ShaderObject& ShaderObject::operator=(ShaderObject&& other) noexcept
{
    if (&other == this) return *this;

    // Delete current GlObject
    gl::DeleteShader(m_name);

    // Steal the other's and reset it
    m_name = other.m_name;
    other.m_name = 0;

    return *this;
}

ShaderObject::~ShaderObject()
{
    gl::DeleteShader(m_name);
}

void ShaderObject::loadFromFile(std::ifstream& file, EShaderType type)
{
    // Read file into sstream
    std::stringstream fileReader;
    fileReader << file.rdbuf();

    // Construct string from stream and compile it
    std::string fileContents{fileReader.str()};
    compile(fileContents.data(), type);
}

void ShaderObject::loadFromString(const std::string& sourceCode, EShaderType type)
{
    compile(sourceCode.c_str(), type);
}

bool ShaderObject::isValid() const
{
    return m_name != 0;
}

bool ShaderObject::compile(const char* shaderSource, EShaderType type) {
    // Clean up existing if it's re-assigning
    if (isValid()) gl::DeleteShader(m_name);

    // Create, assign source code and compile
    m_name = gl::CreateShader(static_cast<GLenum>(type));
    gl::ShaderSource(m_name, 1, &shaderSource, nullptr);
    gl::CompileShader(m_name);

    // If it was invalid then clean up and return
    if (!validate())
    {
        gl::DeleteShader(m_name);
        return false;
    }

    return true;
}

bool ShaderObject::validate()
{
    int success;
    gl::GetShaderiv(m_name, gl::COMPILE_STATUS, &success);

    if (!success)
    {
        // Get length of log and prepare a string to hold it
        int logLength;
        gl::GetShaderiv(m_name, gl::INFO_LOG_LENGTH, &logLength);
        std::string logString(logLength, ' ');

        // Get the log contents and log it
        gl::GetShaderInfoLog(m_name, logLength, nullptr, logString.data());

        logErr("Shader Compile Error:\n{}", logString);

        return false;
    }

    return true;
}
