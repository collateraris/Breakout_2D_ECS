#include <OGLML/PostProcessor.h>

#include <OGLML/Shader.h>
#include <OGLML/Texture2D.h>
#include <OGLML/QuadRender.h>

#include <glew.h>
#include <iostream>
#include <string>
#include <cassert>

using namespace oglml;

PostProcessor::PostProcessor()
{

}

PostProcessor::~PostProcessor()
{
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteFramebuffers(1, &m_MSFBO);
}

void PostProcessor::Init(int w, int h)
{
	SetFrameBufferSize(w, h);

	assert(m_Width != -1);
	assert(m_Height != -1);

	GenBuffers();
	GenFramebufferTexture();
	InitStorage();
}

void PostProcessor::SetShader(Shader& shader)
{
	m_shaderId = shader.GetProgramID();
}

void PostProcessor::SetShaderParams(std::function<void(unsigned int)>& setParamsFun)
{
	setParamsFun(m_shaderId);
}

void PostProcessor::SetFrameBufferSize(int w, int h)
{
	m_Width = w;
	m_Height = h;
}

void PostProcessor::BeginRenderInFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_MSFBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessor::EndRenderInFramebuffer()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_MSFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
	glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // binds both READ and WRITE framebuffer to default framebuffer
}

void PostProcessor::Draw(float dtMilliseconds)
{
	static const std::string uniformSceneStr = "uScene";
	static const std::string uniformTimeStr = "uTime";
	Shader::Use(m_shaderId);
	Shader::SetInt(m_shaderId, uniformSceneStr.c_str(), 0);
	Shader::SetFloat(m_shaderId, uniformTimeStr.c_str(), dtMilliseconds);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_framebufferTextureId);

	QuadRender::Get().DrawFullQuad();
}

void PostProcessor::GenBuffers()
{
	glGenFramebuffers(1, &m_MSFBO);
	glGenFramebuffers(1, &m_FBO);
	glGenRenderbuffers(1, &m_RBO);
}

void PostProcessor::GenFramebufferTexture()
{
	Texture2DInfo par;
	par.width = m_Width;
	par.height = m_Height;
	par.format = GL_RGB;
	par.internalFormat = GL_RGB;
	par.pixels = nullptr;
	par.wrap_s = GL_REPEAT;
	par.wrap_t = GL_REPEAT;
	par.min_filter = GL_LINEAR;
	par.max_filter = GL_LINEAR;
	par.type = GL_UNSIGNED_BYTE;

	Texture2D tex;
	tex.Generate(par);
	m_framebufferTextureId = tex.GetTextureID();
}

void PostProcessor::InitStorage()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_MSFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, m_Width, m_Height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_RBO); // attach MS render buffer object to framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_framebufferTextureId, 0); // attach texture to framebuffer as its color attachment
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::POSTPROCESSOR: Failed to initialize FBO" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}