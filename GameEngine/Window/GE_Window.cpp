#include "ge_window.hpp"


void GE_Window::InitGlfw()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
	}
}

void GE_Window::InitWindowSettings()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // openGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GE_Window::InitMacSettings()
{
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
}

void GE_Window::CreateWindow(const char* _titleWindow)
{
	InitGlfw();
	window = glfwCreateWindow(width, height, _titleWindow, NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. try to edit OpenGL version in InitWindowSettings() above");
		glfwTerminate();
	}
}

GE_Window::GE_Window(float _width, float _height, const char* _title, const GE_Color _bgColor)
{
	width = _width;
	height = _height;
	name = _title;
	CreateWindow(_title);
	backgroundColor = GE_Color(_bgColor);
}

void GE_Window::InitWindow() const
{
	InitWindowSettings();

	InitMacSettings();
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // enable / disable cursor

	// Set the mouse at the center of the screen
	glfwSetCursorPos(window, width / 2, height / 2);

	// Dark blue background
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
}

void GE_Window::SwapBuffer() const
{
	glfwSwapBuffers(window);
}

void GE_Window::UpdateInputEvent() const
{
	glfwPollEvents();
}

void GE_Window::UpdateBackgroundColor(GE_Color _bgColor)
{
	backgroundColor = GE_Color(_bgColor);
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	
}

int GE_Window::GetKey(int _key) const
{
	return glfwGetKey(window, _key);
}

GLFWwindow* GE_Window::GetWindow() const
{
	return window;
}

void GE_Window::Destroy()
{
	glfwDestroyWindow(window);
}