#pragma once

#include <Widget.h>

#include <functional>

namespace oglml
{
	class Text;
}

namespace breakout
{
	class TextWidget : public Widget
	{
	public:

		TextWidget();
		virtual ~TextWidget();

		virtual void Draw() override;

		oglml::Text& GetText();

		void SetUpdateFunc(const std::function<void(oglml::Text*)>&);

	private:

		oglml::Text* m_text = nullptr;

		std::function<void(oglml::Text*)> m_updateFunc = [&](oglml::Text*) {};
	};
}