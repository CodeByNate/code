#pragma once
#include "Maths.h"

class Ball
{
public:
	Ball();
	~Ball();
	Vector2 getPosition();
	void setPosition(Vector2 position);
	Vector2 getVelocity();
	void setVelocity(Vector2);
private:
	Vector2 mPosition;
	Vector2 mVelocity;
};