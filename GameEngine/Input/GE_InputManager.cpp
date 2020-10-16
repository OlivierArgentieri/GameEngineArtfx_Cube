#include "GE_InputManager.hpp"

#include "../Window/GE_Window.hpp"


int GE_InputManager::_windowHeight = 0;
int GE_InputManager::_windowWidth = 0;
GE_Window* GE_InputManager::window = nullptr;

// init mouse delegates
std::vector<std::function<void(double, double)>> GE_InputManager::leftMouseButtonPressDelegates = std::vector<std::function<void(double, double)>>();
std::vector<std::function<void(double, double)>> GE_InputManager::leftMouseButtonReleaseDelegates = std::vector<std::function<void(double, double)>>();

std::vector<std::function<void(double, double)>> GE_InputManager::leftMouseButtonPressCenteredDelegates = std::vector<std::function<void(double, double)>>();
std::vector<std::function<void(double, double)>> GE_InputManager::leftMouseButtonReleaseCenteredDelegates = std::vector<std::function<void(double, double)>>();
//-

// init Game delegates
std::vector<std::function<void()>> GE_InputManager::OnExitGameDelegates = std::vector<std::function<void()>>();
//-

void GE_InputManager::IsValid()
{
	assert(window);		// Make sure initialize GE_InputManager
}

void GE_InputManager::Initialize(GE_Window& _window)
{
	window = &_window; // again, convert ref to pointer to avoid window default constructor
	glfwGetWindowSize(_window.GetWindow(), &_windowWidth, &_windowHeight);
	
	RegisterMouseAction(MouseButtonCallback);
}

void GE_InputManager::RegisterMouseAction(GLFWmousebuttonfun _callBack)
{
	IsValid();
	glfwSetMouseButtonCallback(window->GetWindow(), _callBack);
}

void GE_InputManager::InputLoop()
{
	// listen for an eventual event
	glfwPollEvents();

	TriggerOnExitGame();
}

#pragma region MouseActions
void GE_InputManager::TriggerLeftMousePressAction()
{
	IsValid();
	
	double _x;
	double _y;
	glfwGetCursorPos(window->GetWindow(), &_x, &_y);

	// free position
	for (auto _callback : leftMouseButtonPressDelegates)
		_callback(_x, _y);

	// centered position
	for (auto _callback : leftMouseButtonPressCenteredDelegates)
		_callback(_x - _windowWidth / 2, _y - _windowHeight / 2);
}

void GE_InputManager::TriggerLeftMouseReleaseAction()
{
	IsValid();
	
	double _x;
	double _y;
	glfwGetCursorPos(window->GetWindow(), &_x, &_y);

	// free position
	for (auto _callback : leftMouseButtonReleaseDelegates)
		_callback(_x, _y);

	// centered position
	for (auto _callback : leftMouseButtonReleaseCenteredDelegates)
		_callback(_x - _windowWidth /2, _y - _windowHeight /2);
}

void GE_InputManager::RegisterLeftMouseActionButtonRelease(std::function<void(double, double)> _callback)
{
	leftMouseButtonReleaseDelegates.push_back(_callback);
}

void GE_InputManager::RegisterLeftMouseActionButtonPress(std::function<void(double, double)> _callback)
{
	leftMouseButtonPressDelegates.push_back(_callback);
}

void GE_InputManager::RegisterLeftMouseActionButtonReleaseCentered(std::function<void(double, double)> _callback)
{
	leftMouseButtonReleaseCenteredDelegates.push_back(_callback);
}

void GE_InputManager::RegisterLeftMouseActionButtonPressCentered(std::function<void(double, double)> _callback)
{
	leftMouseButtonPressCenteredDelegates.push_back(_callback);
}

void GE_InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		TriggerLeftMousePressAction();
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		TriggerLeftMouseReleaseAction();

	}
}
#pragma endregion

#pragma region GameActions
void GE_InputManager::TriggerOnExitGame()
{
	IsValid();
	
	if (glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window->GetWindow())) return;

	for (auto _callback : OnExitGameDelegates)
		_callback();
}

void GE_InputManager::RegisterOnExitGame(std::function<void()> _callback)
{
	OnExitGameDelegates.push_back(_callback);
}
#pragma endregion 