#include <OGLML/Shader.h>

#include <glew.h>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace oglml;

bool Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return false;
    }

    return Compile(vertexCode, fragmentCode);
}

void Shader::Use(unsigned int programID)
{
     glUseProgram(programID);
}

void Shader::SetMatrix4f(unsigned int programID, const std::string& uniform, glm::mat4& matrix)
{
    GLuint Loc = glGetUniformLocation(programID, uniform.c_str());
    glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVector3f(unsigned int programID, const std::string& uniform, glm::vec3& vector)
{
    glUniform3f(glGetUniformLocation(programID, uniform.c_str()), vector.x, vector.y, vector.z);
}

void Shader::SetInt(unsigned int programID, const std::string& uniform, int value)
{
    glUniform1i(glGetUniformLocation(programID, uniform.c_str()), value);
}

bool Shader::Compile(const std::string& vertexCode, const std::string& fragmentCode)
{
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment, geometry;
	GLint success;
	GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    };

    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertex);
    glAttachShader(m_programID, fragment);

    glLinkProgram(m_programID);

    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

unsigned int Shader::GetProgramID()
{
    return m_programID;
}
