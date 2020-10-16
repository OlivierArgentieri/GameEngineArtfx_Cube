#pragma once
#include "../Component/Custom/RotateCube/GE_RotateCube.hpp"
#include <functional>
#include <glfw3.h>
#include <map>
#include <detail/type_vec1.hpp>
#include <ext/vector_float2.hpp>

class GE_Window;

class GE_InputManager
{
private:
	static int _windowWidth, _windowHeight;

	static GE_Window* window;

	//void(*GetMousePosCallback) (double, double);
	std::function<void(double, double)>GetMousePosCallback;
	GE_InputManager() = delete;

	static void IsValid();

	#pragma region MouseDelegates
	static std::vector<std::function<void(double, double)>> leftMouseButtonReleaseDelegates;
	static std::vector<std::function<void(double, double)>> leftMouseButtonPressDelegates;

	static std::vector<std::function<void(double, double)>> leftMouseButtonReleaseCenteredDelegates;
	static std::vector<std::function<void(double, double)>> leftMouseButtonPressCenteredDelegates;
	#pragma endregion 
	
	#pragma region KeyboardDelegates
	static std::vector<std::function<void()>> OnExitGameDelegates;
	#pragma endregion
	
public:
	static void Initialize(GE_Window& _window);
	static void RegisterMouseAction(GLFWmousebuttonfun _callBack);

	static void InputLoop();
	
	#pragma region MouseActions
	// main mouse callback
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	/// <summary>
	/// Get OnRelease action and mouse position 
	/// </summary>
	/// <param name="_callback">Callback to get x/y position </param>
	static void RegisterLeftMouseActionButtonRelease(std::function<void(double, double)> _callback);

	/// <summary>
	/// Get OnPress action and mouse position 
	/// </summary>
	/// <param name="_callback">Callback to get x/y position </param>
	static void RegisterLeftMouseActionButtonPress(std::function<void(double, double)> _callback);



	/// <summary>
	/// Get OnRelease action and mouse position centered on the screen
	/// </summary>
	/// <param name="_callback">Callback to get x/y position </param>
	static void RegisterLeftMouseActionButtonReleaseCentered(std::function<void(double, double)> _callback);

	/// <summary>
	/// Get OnPress action and mouse position centered on the screen
	/// </summary>
	/// <param name="_callback">Callback to get x/y position </param>
	static void RegisterLeftMouseActionButtonPressCentered(std::function<void(double, double)> _callback);

	static void TriggerLeftMouseReleaseAction();
	static void TriggerLeftMousePressAction();
	#pragma endregion

	#pragma region GameActions
	static void TriggerOnExitGame();
	static void RegisterOnExitGame(std::function<void()> _callback);
	#pragma endregion 
	
};