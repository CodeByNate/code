#include "Maths.h"

Vector2::Vector2()
{
	mx = 0.0f;
	my = 0.0f;
}
Vector2::Vector2(float x, float y)
{
	mx = x;
	my = y;
}
float Vector2::getX()
{
	return mx;
}
float Vector2::getY()
{
	return my;
}