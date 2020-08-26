#pragma once 

#include <functional>

namespace oglml
{
	class Shader;

	class PostProcessor
	{
	public:

		PostProcessor();

		~PostProcessor();

		void Init();

		void SetShader(Shader& shader);

		void SetShaderParams(std::function<void(unsigned int)>&);

		void SetFrameBufferSize(int w, int h);

		void BeginRenderInFrameBuffer();
		void EndRenderInFrameBuffer();

		void Draw();

	private:

		void GenBuffers();
		void GenFramebufferTexture();
		void InitStorage();

		unsigned int m_framebufferTextureId = 0;
		unsigned int m_shaderId = 0;
		unsigned int m_MSFBO, m_FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
		unsigned int m_RBO; // RBO is used for multisampled color buffer

		unsigned int m_Width = -1, m_Height = -1;
	};
}