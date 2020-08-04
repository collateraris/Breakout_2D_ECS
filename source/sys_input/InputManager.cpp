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

MulticastDelegate<oglml::EKeyButtonCode, oglml::EKeyModeCode>& InputManager::OnKeyRelease()
{
	return m_OnKeyReleaseDelegate;
}

MulticastDelegate<oglml::EKeyButtonCode, oglml::EKeyModeCode>& InputManager::OnKeyPress()
{
	return m_OnKeyPressDelegate;
}

void InputManager::KeyEnterListener(oglml::EKeyButtonCode key, oglml::EActionCode action, oglml::EKeyModeCode mode)
{
	if (action == oglml::EActionCode::RELEASE)
		m_OnKeyReleaseDelegate.Broadcast(key, mode);
	else
		m_OnKeyPressDelegate.Broadcast(key, mode);
}