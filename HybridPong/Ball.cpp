#include "Ball.h"

Ball::Ball()
{

}
Ball::~Ball()
{

}
Vector2 Ball::getPosition()
{
	return mPosition;
}

void Ball::setPosition(Vector2 position)
{
	mPosition = position;
}
Vector2 Ball::getVelocity()
{
	return mVelocity;
}
void Ball::setVelocity(Vector2 velocity)
{
	mVelocity = velocity;
}