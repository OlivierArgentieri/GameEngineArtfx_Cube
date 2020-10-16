#pragma once
#include <GLFW/glfw3.h>

struct GE_Color
{
public:
	static const GE_Color black;
	GLclampf r;
	GLclampf g;
	GLclampf b;
	GLclampf a;

	GE_Color(float _r, float _g, float _b, float _a = 1);
	GE_Color(const GE_Color& _color);
	GE_Color();
};