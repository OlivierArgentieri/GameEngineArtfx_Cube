#include "GE_Time.hpp"

#include <glfw3.h>

double GE_Time::currentTime = 0;
double GE_Time::oldTime = 0;
float GE_Time::deltaTime = 0;

float GE_Time::GetDeltaTime()
{
	return deltaTime;
}

void GE_Time::BeginFrame()
{
	oldTime = glfwGetTime();
}

void GE_Time::EndFrame()
{
	currentTime = glfwGetTime();

	deltaTime = float(currentTime - oldTime);
	oldTime = currentTime;
}