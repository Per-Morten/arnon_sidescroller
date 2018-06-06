#include "shaderProgram.h"
#include "shaderObject.h"
#include "arnlog/arnlog.h"

#include <iostream>

#include "glCore45.h"

// When only a vertex shader is provided, this is used as a default fragment shader
static const char* default_fragment_source = R"(
#version 450 core
layout(location=0) out vec4 color;
void main() { color = vec4(1.f); }
)";

ShaderProgram::ShaderProgram(const ShaderObject& vertexShader)
{
    createFromVertexOnly(vertexShader);
}

ShaderProgram::ShaderProgram(const ShaderObject& vertexShader, const ShaderObject& fragmentShader)
{
    create(vertexShader, fragmentShader);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept : m_name(other.m_name)
{
    other.m_name = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    // Check and delete existing program (if it exists)
    if (this == &other) return *this;
    gl::DeleteProgram(m_name);

    // Steal state
    m_name = other.m_name;
    other.m_name = 0;

    return *this;
}

ShaderProgram::~ShaderProgram()
{
    gl::DeleteProgram(m_name);
}

void ShaderProgram::bind() const 
{
    if (!isValid())
    {
        logWarn("Attempt to bind empty Shader Program!");
    }

    gl::UseProgram(m_name);
}

void ShaderProgram::unbind() const
{
    gl::UseProgram(0);
}

void ShaderProgram::create(const ShaderObject& vertexShader, const ShaderObject& fragmentShader)
{
    link(vertexShader, fragmentShader);
}

void ShaderProgram::createFromVertexOnly(const ShaderObject& vertexShader)
{
    // When only supplying a vertex shader, then create a default fragment shader to use
    static ShaderObject defaultFragmentShader(default_fragment_source, EShaderType::FragmentShader);
    create(vertexShader, defaultFragmentShader);
}

bool ShaderProgram::isValid() const
{
    return m_name != 0;
}

bool ShaderProgram::link(const ShaderObject& vertexShader, const ShaderObject& fragmentShader) {
    // Clean up old if you are re-creating a new program
    if (isValid()) gl::DeleteProgram(m_name);

    m_name = gl::CreateProgram();

    // Attach the shaders and link
    gl::AttachShader(m_name, vertexShader.m_name);
    gl::AttachShader(m_name, fragmentShader.m_name);

    gl::LinkProgram(m_name);

    // If the linking failed, clean up and return
    if (!validate())
    {
        gl::DeleteProgram(m_name);
        return false;
    }

    return true;
}

bool ShaderProgram::validate()
{
    // Check for success
    int success;
    gl::GetProgramiv(m_name, gl::LINK_STATUS, &success);

    if (!success)
    {
        // Get length and prepare a string
        int logLength;
        gl::GetProgramiv(m_name, gl::INFO_LOG_LENGTH, &logLength);
        std::string logString(logLength, ' ');

        gl::GetProgramInfoLog(m_name, logLength, nullptr, logString.data());

        logErr("Program Link Error:\n{}", logString);

        return false;
    }

    return true;
}
