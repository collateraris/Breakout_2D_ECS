#pragma once

namespace oglml
{
	class DynamicQuadRender
	{
	public:

		static DynamicQuadRender& Get();

		void Draw();

		void BindVAO();
		void BindBuffer();

	private:

		DynamicQuadRender();
		~DynamicQuadRender();
		DynamicQuadRender(DynamicQuadRender&) = delete;
		DynamicQuadRender(DynamicQuadRender&&) = delete;
		void operator=(DynamicQuadRender&) = delete;
		void operator=(DynamicQuadRender&&) = delete;

		unsigned int VBO;
		unsigned int VAO;
	};

}