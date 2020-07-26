#include <gameWindow.h>

#include <iostream>

using namespace breakout;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GameWindow::~GameWindow()
{

}

void GameWindow::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "Breakout", nullptr, nullptr);
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

void GameWindow::Terminate()
{
	glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	GLFWwindow* w = window;
	w = nullptr;
	int sum = key + scancode + action + mode;
	sum++;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	GLFWwindow* w = window;
	w = nullptr;
	double pos = xpos + ypos;
	pos++;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	GLFWwindow* w = window;
	w = nullptr;
	double offset = xoffset + yoffset;
	offset++;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLFWwindow* w = window;
	w = nullptr;
	int sum = width + height;
	sum++;
}