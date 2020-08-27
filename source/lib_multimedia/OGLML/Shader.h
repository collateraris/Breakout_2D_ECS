#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <string>

namespace oglml
{
	class Shader
	{
	public:
		Shader() = default;
		~Shader() = default;

		bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);

		static void Use(unsigned int programID);
		static void SetMatrix4f(unsigned int programID, const std::string& uniform, glm::mat4& matrix);
		static void SetVector3f(unsigned int programID, const std::string& uniform, glm::vec3& vector);
		static void SetInt(unsigned int programID, const std::string& uniform, int value);
		static void SetFloat(unsigned int programID, const std::string& uniform, float value);
		static void SetVector2fv(unsigned int programID, const std::string& uniform, int size, float* beginArr);
		static void SetIntv(unsigned int programID, const std::string& uniform, int size, int* beginArr);
		static void SetFloatv(unsigned int programID, const std::string& uniform, int size, float* beginArr);

		unsigned int GetProgramID();

	private:

		bool Compile(const std::string& vertexCode, const std::string& fragmentCode);

		unsigned int m_programID = 0;
	};
}