#include <gameWindow.h>

#include <gameContext.h>
#include <ConfigManager.h>

#include <array>
#include <iostream>

using namespace breakout;

MulticastDelegate<oglml::EKeyButtonCode, oglml::EActionCode, oglml::EKeyModeCode> g_keyButtonDelegate;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GameWindow::~GameWindow()
{

}

MulticastDelegate<oglml::EKeyButtonCode, oglml::EActionCode, oglml::EKeyModeCode>& GameWindow::GetKeyButtonDelegate()
{
	return g_keyButtonDelegate;
}

void GameWindow::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	
	XPath windowConfig = GameContext::Get().GetConfigManager().GetRoot().GetPath("window");

	std::string title = windowConfig.GetAttribute<std::string>("title");
	m_width = windowConfig.GetAttribute<int>("width");
	m_height = windowConfig.GetAttribute<int>("height");
	
	GLFWwindow* window = glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	//keycallback
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return;
	}

	//Viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	m_window = window;
}

bool GameWindow::IsOpen() const
{
	return glfwWindowShouldClose(m_window);
}

void GameWindow::PollEvents() const
{
	glfwPollEvents();
}

void GameWindow::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void GameWindow::ClearColorBuffer()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GameWindow::Terminate()
{
	glfwTerminate();
}

void GameWindow::Update()
{
	PollEvents();
	SwapBuffers();
	ClearColorBuffer();

	CalculateDeltaTime();
};

int GameWindow::GetWidth()
{
	return m_width;
}

int GameWindow::GetHeight()
{
	return m_height;
}

float GameWindow::GetDeltaTime()
{
	return m_deltaTime;
}

void GameWindow::CalculateDeltaTime()
{
	static std::array<float, 2> deltaTimeStory = { 0.f , 0.f };
	static bool currentDeltaTime = false;

	deltaTimeStory[currentDeltaTime] = GetCurrentTime();
	m_deltaTime = deltaTimeStory[currentDeltaTime] - deltaTimeStory[!currentDeltaTime];
	currentDeltaTime = !currentDeltaTime;
}

float GameWindow::GetCurrentTime()
{
	return glfwGetTime();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	oglml::EKeyButtonCode keyCode = oglml::InputDecoder::GetKeyButtonCodeFromGLFW3(key);
	oglml::EActionCode actionCode = oglml::InputDecoder::GetActionCodeFromGLFW3(action);
	oglml::EKeyModeCode modeCode = oglml::InputDecoder::GetKeyModeCodeFromGLFW3(mode);

	g_keyButtonDelegate.Broadcast(keyCode, actionCode, modeCode);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

