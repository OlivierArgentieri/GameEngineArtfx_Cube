#include "Utils.hpp"

float Utils::Clamp(float _min, float _max, float _value)
{
	if (_value > _max)
		return _max;

	if (_value < _min)
		return _min;

	return _value;
}
