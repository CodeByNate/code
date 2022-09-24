#pragma once
#include "Maths.h"

class Paddle
{
public:
	Paddle();
	~Paddle();
	Vector2 getPosition();
	void setPosition(Vector2 position);
	int getDirection();
	void setDirection(int direction);
private:
	Vector2 mPosition;
	int mDirection;
};

//One thing I've noticed about music, is that music
//has a way of calming the mind.  Music is the souls' 
//pure expression.
//But music isn't about the noise, the sound.  Music
//isn't about the harmony or the melody.  It's about
//becoming as quiet as possible, between moments of
//intense volume, hearing the resonance, and 
//adjusting accordingly.

//The quieter you become the more you are able to hear.
//The quieter you become the more you are able to hear.
//The quieter you become the more you are able to hear.
//The quieter you become the more you are able to hear.
//The quieter you become the more you are able to hear.