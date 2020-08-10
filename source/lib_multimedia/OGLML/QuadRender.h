#pragma once

namespace oglml
{
	class QuadRender
	{
	public:

		static QuadRender& Get();

		void Draw();

		void DrawArraysInstanced(unsigned int instancedNumber);

		void BindVAO();

	private:

		QuadRender();
		~QuadRender();
		QuadRender(QuadRender&) = delete;
		QuadRender(QuadRender&&) = delete;
		void operator=(QuadRender&) = delete;
		void operator=(QuadRender&&) = delete;

		unsigned int VBO;
		unsigned int quadVAO;
	};
}