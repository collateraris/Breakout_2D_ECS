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

		void DrawFullQuad();

	private:

		QuadRender();
		~QuadRender();
		QuadRender(QuadRender&) = delete;
		QuadRender(QuadRender&&) = delete;
		void operator=(QuadRender&) = delete;
		void operator=(QuadRender&&) = delete;

		unsigned int VBO;
		unsigned int VBOfull = 0;
		unsigned int quadVAOv1;
		unsigned int quadVAOfull;
	};

}