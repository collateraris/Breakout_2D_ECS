#include <gameWindow.h>

#include <gameContext.h>
#include <ConfigManager.h>

#include <iostream>

using namespace breakout;

Delegate g_keyButtonDelegate;
Delegate g_mouseClickDelegate;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GameWindow::~GameWindow()
{

}

Delegate& GameWindow::GetKeyButtonDelegate()
{
	return g_keyButtonDelegate;
}

Delegate& GameWindow::GetMouseClickDelegate()
{
	return g_mouseClickDelegate;
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

	//mousecallback
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	//scrollcallback
	glfwSetScrollCallback(window, scroll_callback);

	//framebuffer
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
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GameWindow::Terminate()
{
	glfwTerminate();
}

int GameWindow::GetWidth()
{
	return m_width;
}

int GameWindow::GetHeight()
{
	return m_height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	g_keyButtonDelegate.Execute(key, scancode, action, mode);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	g_mouseClickDelegate.Execute(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

}