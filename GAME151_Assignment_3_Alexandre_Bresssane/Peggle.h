#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_scancode.h>
#include "GameManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Texture.h"
#include "Window.h"
#include "VMath.h"
#include "MMath.h"


//Definitions for shooting ball
#define A4_BALL_IMAGE "Stellball.png"
#define A4_BALL_MASS 1.6f
#define A4_BALL_POS Vec3(16.0f, 15.0f, 0.0f)
#define A4_BALL_RADIUS 0.9f
#define A4_BALL_REST 1.0f
// definitions for peggle balls
#define A4_PEG_IMAGE "Balls.png"
#define A4_PEG_MASS 9.0f 
#define A4_PEG_REST 1.0f
#define A4_PEG_RADIUS 0.33f
//definitions of game window
#define A4_TIME_SCALE 1.0f
#define A4_WINDOW_MIN_X 0.0f
#define A4_WINDOW_MAX_X 32.0f
#define A4_WINDOW_MIN_Y 0.0f
#define A4_WINDOW_MAX_Y 18.0f
#define A4_WINDOW_TITLE "Assignment 4 - Peggle Game - CONTROLS: LEFT - RIGHT (ANGLE), UP DOWN (FOR POWER) and SPACE (Shoot)"

//Peggle is part of Scene class
class Peggle : public Scene
{
public:
	
	GameObject* ball;
	Texture* ballTexture;
	std::vector<GameObject*> pegs;
	Texture* pegTexture;
	Body* ballBody;

	//declaring all bools
	bool isColliding;
	bool gravityFlag = false;
	bool restart = true;
	bool shotPlaced = false;
	bool controlActivity = true;
	bool A4_PEG_ACTIVITY = true;
	//declaring all ints
	int score;
	int ballCount = 9;
	int pegCount_0 = 8;
	int pegCount_1 = 12;
	int pegCount_2 = 16;
	//declaring all floats
	float angle = 270.0f;
	float power = 100.0f;

	//declaring all vectors
	Vec3 A4_PEG_POS1 = Vec3(12.0f, 7.0f, 0.0f);
	Vec3 A4_PEG_POS2 = Vec3(8.0f, 5.0f, 0.0f);
	Vec3 A4_PEG_POS3 = Vec3(6.0f, 3.0f, 0.0f);
	//declaring SDL_Point
	SDL_Point debugDrawPoints[1000];


	Peggle(GameManager* game) : Scene(game) {}

	//Begin Peggle 
	void Begin()
	{
		std::cout << "This is peggle. You have: " << ballCount + 1 << " balls.  Score: " << score << std::endl;
		score = 0;
		
		Window* window = game->GetWindow();
		window->title = A4_WINDOW_TITLE;

		
		game->GetClock()->timeScale = A4_TIME_SCALE;

		SetCameraBounds(A4_WINDOW_MIN_X, A4_WINDOW_MAX_X, A4_WINDOW_MIN_Y, A4_WINDOW_MAX_Y);
		
		// create ball object
		ballBody = new Body(A4_BALL_MASS, A4_BALL_POS, A4_BALL_RADIUS, A4_BALL_REST);
		ballTexture = new Texture(A4_BALL_IMAGE, window->renderer);
		ball = new GameObject(game->GetScene(), ballBody, ballTexture);
		world.AddBody(ballBody);
		ball->GetBody()->Velocity = Vec3(0.0f, -1.0f, 0.0f);

		//create the first row of balls on peggle
		while (pegCount_0 > 0)
		{
			pegTexture = new Texture(A4_PEG_IMAGE, window->renderer);
			{
				Body* pegBody = new Body(A4_PEG_MASS, A4_PEG_POS1, A4_PEG_RADIUS, A4_PEG_REST, A4_PEG_ACTIVITY);
				world.AddBody(pegBody);
				pegs.push_back(new GameObject(this, pegBody, pegTexture));
			}
			A4_PEG_POS1 += Vec3(1.5f, 0.0f, 0.0f);
			pegCount_0--;
		}
		//create the second row of balls on peggle
		while (pegCount_1 > 0)
		{
			pegTexture = new Texture(A4_PEG_IMAGE, window->renderer);
			{
				Body* pegBody = new Body(A4_PEG_MASS, A4_PEG_POS2, A4_PEG_RADIUS, A4_PEG_REST, A4_PEG_ACTIVITY);
				world.AddBody(pegBody);
				pegs.push_back(new GameObject(this, pegBody, pegTexture));
			}
			A4_PEG_POS2 += Vec3(1.5f, 0.0f, 0.0f);
			pegCount_1--;
		}
		//create the third row of balls on peggle
		while (pegCount_2 > 0)
		{
			pegTexture = new Texture(A4_PEG_IMAGE, window->renderer);
			{
				Body* pegBody = new Body(A4_PEG_MASS, A4_PEG_POS3, A4_PEG_RADIUS, A4_PEG_REST, A4_PEG_ACTIVITY);
				world.AddBody(pegBody);
				pegs.push_back(new GameObject(this, pegBody, pegTexture));
			}
			A4_PEG_POS3 += Vec3(1.5f, 0.0f, 0.0f);
			pegCount_2--;
		}
	}

	void HandleEvent(const SDL_Event& e)
	{

	}

	bool Update(const float deltaTime)
	{
		while (ballCount > 0)
		{
			if (restart == true)
			{
				controlActivity = true;
				shotPlaced = false;
				gravityFlag = false;
				ball->GetBody()->Acceleration = VECTOR_ZERO;
				ball->GetBody()->Velocity = VECTOR_ZERO;
				ball->GetBody()->Position = A4_BALL_POS;
				restart = false;
			}
			else
			{
				while (ball->GetBody()->Position.y > -2.0f)
				{
					
					for (GameObject* peg : pegs)
					{
						Body* pegBody = peg->GetBody();
						Vec3 normalBtoA;
						if (TestCollision(ballBody, pegBody, &normalBtoA))
						{
							ResolveCollision(ballBody, pegBody, normalBtoA);
						}
					}

					ballBody->Velocity += deltaTime * ballBody->Acceleration;
					ballBody->Position += deltaTime * ballBody->Velocity;
					ballBody->Acceleration = VECTOR_ZERO;
					for (GameObject* peg : pegs)
					{
						Body* pegBody = peg->GetBody();

						pegBody->Velocity += deltaTime * pegBody->Acceleration;
						pegBody->Position += deltaTime * pegBody->Velocity;
						pegBody->Acceleration = VECTOR_ZERO;
					}

					

					shotPlaced = false;
					

					SDL_Surface* surf = SDL_CreateRGBSurface(0, game->GetWindow()->width, game->GetWindow()->height, 32, 0, 0, 0, 0);
					const Uint8 *state = SDL_GetKeyboardState(NULL);
					while (shotPlaced == false && controlActivity == true)
					{

						Matrix4 rot = MMath::rotate(angle, Vec3(0, 0, 1));
						Vec3 dir = Vec3(power, 0.0f, 0.0f);
						Vec3 endPoint = Vec3((ball->GetBody()->Position) + (rot * dir * 5));
						float fraction = 0.0f;
						for (int i = 0; i < 1000; i++, fraction += 0.001f)
						{
							Vec3 point = ball->GetBody()->Position + rot * dir * fraction;
							Vec3 renderPosition1 = projectionMatrix * point;
							debugDrawPoints[i].x = renderPosition1.x;
							debugDrawPoints[i].y = renderPosition1.y;
						}
						
						if (state[SDL_SCANCODE_LEFT])
						{
							angle--;
							
							std::cout << "Selected Angle: " << angle << std::endl;
							if (angle < 180.0f)
								angle = 180.0f;
						}

						if (state[SDL_SCANCODE_RIGHT])
						{
							angle++;
							std::cout << "Selected Angle: " << angle << std::endl;
							if (angle > 360.0f)
								angle = 360.0f;
						}

						if (state[SDL_SCANCODE_UP])
						{

							power += 50.0f;
							std::cout << "Shot strenght: " << power << std::endl;
							if (power > 1000.0f)
								power = 1000.0f;
						}

						if (state[SDL_SCANCODE_DOWN])
						{

							power -= 50.0f;
							std::cout << "Shot strenght: " << power << std::endl;
							if (power <= 0.0f)
								power = 0.0f;
						}

						if (state[SDL_SCANCODE_SPACE])
						{
							Shoot();
							gravityFlag = true;
						}
						shotPlaced = true;
					}
					
					if (gravityFlag == true)
					{
						ball->GetBody()->Acceleration.y -= 9.8f;
					}
					return false;
				}
				ballCount--;
				restart = true;
				std::cout << "Balls Left: " << ballCount + 1 << "  New Score: " << score << std::endl;
			}
		}
	}

	void Render()
	{
		//Render all objects on screen
		for (GameObject* peg : pegs)
		{
			peg->Render(projectionMatrix);
		}
		ball->Render(projectionMatrix);


		Uint8 rOld, gOld, bOld, aOld;
		SDL_GetRenderDrawColor(game->GetWindow()->renderer, &rOld, &gOld, &bOld, &aOld);

		
		SDL_SetRenderDrawColor(game->GetWindow()->renderer, 0xff, 0, 0, 0xff);
		SDL_RenderDrawPoints(game->GetWindow()->renderer, debugDrawPoints, 1000);
		SDL_SetRenderDrawColor(game->GetWindow()->renderer, rOld, gOld, bOld, aOld);

	}
	void End()
	{
		
		if (ballTexture)
		{
			delete ballTexture;
			ballTexture = NULL;
		}
		if (pegTexture)
		{
			delete pegTexture;
			pegTexture = NULL;
		}
	}

	bool TestCollision(const Body* a, const Body* b, Vec3* outNormalBtoA)
	{
		//Check if a collision occurs
		Vec3 btoA = a->Position - b->Position;

		
		float distance = sqrt((btoA.x * btoA.x) + (btoA.y * btoA.y) + (btoA.z * btoA.z));

		
		if (distance <= (a->Radius + b->Radius))
		{
			
			if (outNormalBtoA)
			{
				*outNormalBtoA = btoA / distance;
				isColliding = true;
				score += 5;
				std::cout << "BALL HIT!! New Score: " << score << std::endl;
			}
			return true;

		}
		isColliding = false;
		return false;
	}

	void ResolveCollision(Body* a, Body* b, const Vec3& normalBtoA) const
	{

		if (b->Activity == true)
		{
			float restitution = 0.5f * (a->Restitution + b->Restitution);

			float initialVelocityA = ((a->Velocity.x * normalBtoA.x) + (a->Velocity.y * normalBtoA.y) + (a->Velocity.z * normalBtoA.z));
			float initialVelocityB = ((b->Velocity.x * normalBtoA.x) + (b->Velocity.y * normalBtoA.y) + (b->Velocity.z * normalBtoA.z));

			float finalVelocityA = ((((a->Mass - (restitution*b->Mass)) * initialVelocityA) + ((1 + restitution) * b->Mass * initialVelocityB)) / (a->Mass + b->Mass));
			float finalVelocityB = ((((b->Mass - (restitution*a->Mass)) * initialVelocityB) + ((1 + restitution) * a->Mass * initialVelocityA)) / (a->Mass + b->Mass));

			float deltaVelocityA = finalVelocityA - initialVelocityA;
			float deltaVelocityB = finalVelocityB - initialVelocityB;

			a->Velocity += deltaVelocityA * normalBtoA;
			b->Velocity += deltaVelocityB * normalBtoA;
			b->Activity = false;
		}
	}
	void Shoot()
	{
		//shoot the ball
		controlActivity = false;
		Matrix4 rot = MMath::rotate(angle, Vec3(0, 0, 1));
		Vec3 dir = Vec3(power, 0.0f, 0.0f);
		ball->GetBody()->ApplyForceToCentre(rot * dir);
	}

	
};

