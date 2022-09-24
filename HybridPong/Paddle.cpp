#include "Paddle.h"
Paddle::Paddle()
{
	mPosition = Vector2(0, 0);
	mDirection = 0;
}
Paddle::~Paddle()
{

}
Vector2 Paddle::getPosition()
{
	return mPosition;
}
void Paddle::setPosition(Vector2 position)
{
	mPosition = position;
}
int Paddle::getDirection()
{
	return mDirection;
}
void Paddle::setDirection(int direction)
{
	mDirection = direction;
}