#pragma once

#include <System.h>
#include <Delegate.h>
#include <OGLML/InputCode.h>

namespace breakout
{
	class InputManager
	{
    public:

		static InputManager& Get();

		MulticastDelegate<oglml::EKeyButtonCode, oglml::EKeyModeCode>& OnKeyRelease();

		MulticastDelegate<oglml::EKeyButtonCode, oglml::EKeyModeCode>& OnKeyPress();

		void KeyEnterListener(oglml::EKeyButtonCode, oglml::EActionCode, oglml::EKeyModeCode);

	private:

		InputManager();
		~InputManager();
		InputManager(InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		void operator=(InputManager&) = delete;
		void operator=(InputManager&&) = delete;

		MulticastDelegate<oglml::EKeyButtonCode, oglml::EKeyModeCode> m_OnKeyReleaseDelegate;
		MulticastDelegate<oglml::EKeyButtonCode, oglml::EKeyModeCode> m_OnKeyPressDelegate;
	};
}