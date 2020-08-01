#pragma once

namespace breakout
{
    enum class EEntityType : int
    {
        Awersome = 0,
		MAX,
    };

	class ECSBreakout
	{
	public:

		static void CreateComponent(EEntityType);
	};
}