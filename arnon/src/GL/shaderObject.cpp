#include "shaderObject.h"

#include "glCore45.h"

ShaderObject::ShaderObject(const std::string& shaderSourceCode, EShaderType type)
{
    loadFromString(shaderSourceCode, type);
}

ShaderObject::ShaderObject(std::ifstream& shaderSourceFile, EShaderType type)
{
    loadFromFile(shaderSourceFile, type);
}

void ShaderObject::loadFromFile(std::ifstream& file, EShaderType type)
{
    
}

void ShaderObject::loadFromString(const std::string& sourceCode, EShaderType type)
{

}

const bool ShaderObject::isValid() const
{
    return m_name != 0;
}

bool ShaderObject::compile()
{
    return false;
}

bool ShaderObject::validate()
{
    return false;
}
