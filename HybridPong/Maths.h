// Vector2 struct just stores x/y coordinates
// (for now)
#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	float Vector2::getX();
	float Vector2::getY();
private:
	float mx;
	float my;
};
