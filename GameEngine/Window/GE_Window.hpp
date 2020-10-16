#pragma once
#include <string>
#include <glfw3.h>

#include <../Color/ge_color.hpp>

class GE_Window
{
private:
	float width;
	float height;

	std::string name;
	GE_Color backgroundColor;

	//main window
	GLFWwindow *window;

	static void InitGlfw();
	static void InitWindowSettings();
	static void InitMacSettings();
	void CreateWindow(const char* _titleWindow);


public:
	GE_Window(float _width = 1024, float _height = 760, const char* _title = "DEFAULT_WINDOW", const GE_Color _bgColor = GE_Color::black);
	void InitWindow() const;
	void SwapBuffer() const;
	void UpdateInputEvent() const;
	void UpdateBackgroundColor(GE_Color _bgColor);

	int GetKey(int _key) const;
	
	GLFWwindow* GetWindow() const;
	void Destroy();
};
