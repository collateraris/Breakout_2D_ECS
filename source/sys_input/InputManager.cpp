#include <InputManager.h>

using namespace breakout;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

InputManager& InputManager::Get()
{
	static InputManager inputManager;
	return inputManager;
}

MulticastDelegate<oglml::EKeyButtonCode, oglml::EKeyModeCode>& InputManager::OnKeyReleased()
{
	return m_OnKeyReleasedDelegate;
}

MulticastDelegate<oglml::EKeyButtonCode, oglml::EKeyModeCode>& InputManager::OnKeyPressed()
{
	return m_OnKeyPressedDelegate;
}

void InputManager::KeyEnterListener(oglml::EKeyButtonCode key, oglml::EActionCode action, oglml::EKeyModeCode mode)
{
	if (action == oglml::EActionCode::RELEASE)
		m_OnKeyReleasedDelegate.Broadcast(key, mode);
	else
		m_OnKeyPressedDelegate.Broadcast(key, mode);
}