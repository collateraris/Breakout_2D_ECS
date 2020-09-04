#include <OGLML/InputCode.h>

#include <unordered_map>

#include <glfw3.h>

using namespace oglml;

EActionCode InputDecoder::GetActionCodeFromGLFW3(int action)
{
	static const std::unordered_map<int, EActionCode> codeMap =
	{
		{GLFW_RELEASE, EActionCode::RELEASE},
		{GLFW_PRESS, EActionCode::PRESS},
		{GLFW_REPEAT, EActionCode::REPEAT}
	};

	auto foundIt = codeMap.find(action);
	if (foundIt == codeMap.end())
		return EActionCode::UNKNOWN;
	return foundIt->second;
}

EKeyModeCode InputDecoder::GetKeyModeCodeFromGLFW3(int mode)
{
	static const std::unordered_map<int, EKeyModeCode> codeMap =
	{
		{GLFW_MOD_SHIFT, EKeyModeCode::MOD_SHIFT},
		{GLFW_MOD_CONTROL, EKeyModeCode::MOD_CONTROL},
		{GLFW_MOD_ALT, EKeyModeCode::MOD_ALT},
		{GLFW_MOD_SUPER, EKeyModeCode::MOD_SUPER},
		{GLFW_MOD_CAPS_LOCK, EKeyModeCode::MOD_CAPS_LOCK},
		{GLFW_MOD_NUM_LOCK, EKeyModeCode::MOD_NUM_LOCK},
	};

	auto foundIt = codeMap.find(mode);
	if (foundIt == codeMap.end())
		return EKeyModeCode::UNKNOWN;
	return foundIt->second;
}

EKeyButtonCode InputDecoder::GetKeyButtonCodeFromGLFW3(int key)
{
	static const std::unordered_map<int, EKeyButtonCode> codeMap =
	{
		{GLFW_KEY_A, EKeyButtonCode::KEY_A},
		{GLFW_KEY_B, EKeyButtonCode::KEY_B},
		{GLFW_KEY_C, EKeyButtonCode::KEY_C},
		{GLFW_KEY_D, EKeyButtonCode::KEY_D},
		{GLFW_KEY_E, EKeyButtonCode::KEY_E},
		{GLFW_KEY_F, EKeyButtonCode::KEY_F},
		{GLFW_KEY_G, EKeyButtonCode::KEY_G},
		{GLFW_KEY_H, EKeyButtonCode::KEY_H},
		{GLFW_KEY_I, EKeyButtonCode::KEY_I},
		{GLFW_KEY_J, EKeyButtonCode::KEY_J},
		{GLFW_KEY_K, EKeyButtonCode::KEY_K},
		{GLFW_KEY_L, EKeyButtonCode::KEY_L},
		{GLFW_KEY_M, EKeyButtonCode::KEY_M},
		{GLFW_KEY_N, EKeyButtonCode::KEY_N},
		{GLFW_KEY_O, EKeyButtonCode::KEY_O},
		{GLFW_KEY_P, EKeyButtonCode::KEY_P},
		{GLFW_KEY_Q, EKeyButtonCode::KEY_Q},
		{GLFW_KEY_R, EKeyButtonCode::KEY_R},
		{GLFW_KEY_S, EKeyButtonCode::KEY_S},
		{GLFW_KEY_T, EKeyButtonCode::KEY_T},
		{GLFW_KEY_U, EKeyButtonCode::KEY_U},
		{GLFW_KEY_V, EKeyButtonCode::KEY_V},
		{GLFW_KEY_W, EKeyButtonCode::KEY_W},
		{GLFW_KEY_X, EKeyButtonCode::KEY_X},
		{GLFW_KEY_Y, EKeyButtonCode::KEY_Y},
		{GLFW_KEY_Z, EKeyButtonCode::KEY_Z},
		{GLFW_KEY_SPACE, EKeyButtonCode::KEY_SPACE},
		{GLFW_KEY_ENTER, EKeyButtonCode::KEY_ENTER},
		{GLFW_KEY_ESCAPE, EKeyButtonCode::KEY_ESCAPE},
	};


	auto foundIt = codeMap.find(key);
	if (foundIt == codeMap.end())
		return EKeyButtonCode::UNKNOWN;
	return foundIt->second;
}

