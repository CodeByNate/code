// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
{
	mPaddle.setDirection(0);
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//
	StartGame();

	return true;
}
void Game::StartGame()
{
	mPaddle.setPosition(Vector2(10.0f, 768.0 / 2.0f));
	mBall.setPosition(Vector2(1024.0f / 2.0f, 768.0f / 2.0f));
	mBall.setVelocity(Vector2(-200.0f, 235.0f));
}
void Game::RunLoop()
{

	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	// Update paddle direction based on W/S keys
	//mPaddleDir = 0;
	mPaddle.setDirection(0);
	if (state[SDL_SCANCODE_W])
	{
		//mPaddleDir -= 1;
		mPaddle.setDirection(-1);
	}else if (state[SDL_SCANCODE_S])
	{
		//mPaddleDir += 1;
		mPaddle.setDirection(1);
	}
	else
	{
		mPaddle.setDirection(0);
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float dt = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (dt > 0.05f)
	{
		dt = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	// Update paddle position based on direction
	if (mPaddle.getDirection() != 0)
	{
		//mPaddlePos.y += mPaddleDir * 300.0f * dt;
		mPaddle.setPosition(Vector2(mPaddle.getPosition().getX(), mPaddle.getPosition().getY() + 300.0f * dt));
		// Make sure paddle doesn't move off screen!
		if (mPaddle.getPosition().getY() < (paddleH / 2.0f + thickness))
		{
			mPaddle.setPosition(Vector2(paddleH / 2.0f + thickness, mPaddle.getPosition().getY()));
		}
		else if (mPaddle.getPosition().getY() > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddle.setPosition(Vector2(768.0f - paddleH / 2.0f - thickness, mPaddle.getPosition().getY()));
		}
	}
	
	// Update ball position based on ball velocity
	mBall.setPosition(Vector2(mBall.getVelocity().getX() * dt, mBall.getPosition().getY() * dt));
	
	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddle.getPosition().getY() - mBall.getPosition().getY();
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBall.getPosition().getX() <= 25.0f && mBall.getPosition().getX() >= 20.0f &&
		// The ball is moving to the left
		mBall.getVelocity().getX() < 0.0f) 
	{
		//mBall.getVelocity().getX() *= -1.0f;
		mBall.setVelocity(Vector2(mBall.getVelocity().getX() * -1.0f, mBall.getVelocity().getY()));
	}
	// Did the ball go off the screen? (if so, end game)
	else if(mBall.getPosition().getX() <= 0.0f)
	 //else if (mBallPos.x <= 0.0f)
	{
		//mIsRunning = false;
		StartGame();
	}
	// Did the ball collide with the right wall?
	else if (mBall.getPosition().getX() >= (1024.0f - thickness) 
		&& mBall.getVelocity().getX()> 0.0f)
	{
		mBall.setVelocity(Vector2(mBall.getVelocity().getX() * -1.0f, mBall.getPosition().getY()));
	}
	
	// Did the ball collide with the top wall?
	if (mBall.getPosition().getY() <= thickness && mBall.getVelocity().getY() < 0.0f)
	{
		mBall.setVelocity(Vector2(mBall.getVelocity().getX(), mBall.getVelocity().getY() * -1));
	}
	// Did the ball collide with the bottom wall?
	else if (mBall.getPosition().getY() >= (768 - thickness) &&
		mBall.getVelocity().getY() > 0.0f)
	{
		mBall.setVelocity(Vector2(mBall.getVelocity().getX(), mBall.getVelocity().getY() * -1));
	}
}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	//Draw player wall top
	// 
	SDL_Rect playerWallTopOfGoal{
		0,
		0,
		thickness,
		(1024 / 2) - 15
	};
	SDL_Rect playerWallBottomOfGoal{
		0,
		(1024 / 2) + 15,
		thickness,
		1024 / 2 - 15
	};
	SDL_RenderFillRect(mRenderer, &playerWallTopOfGoal);
	SDL_RenderFillRect(mRenderer, &playerWallBottomOfGoal);
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	
	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddle.getPosition().getX()),
		static_cast<int>(mPaddle.getPosition().getY() - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	
	// Draw ball
	SDL_Rect ball{	
		static_cast<int>(mBall.getPosition().getX() - thickness / 2),
		static_cast<int>(mBall.getPosition().getY() - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
