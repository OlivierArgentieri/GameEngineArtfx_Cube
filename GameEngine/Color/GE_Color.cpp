#include "ge_color.hpp"

const GE_Color black = GE_Color(0, 0, 0);

GE_Color::GE_Color(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

GE_Color::GE_Color(const GE_Color& _color) : GE_Color(_color.r, _color.g, _color.b, _color.a)
{
}

GE_Color::GE_Color() : GE_Color(0,0,0,0)
{	
}