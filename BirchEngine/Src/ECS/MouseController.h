#pragma once


#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "ButtonComponent.h"


class MouseController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	ButtonComponent* button;
	SDL_Rect destR, exitR;
	int x, y;


	void init()
	{
		button = &entity->getComponent<ButtonComponent>();

		destR.x = 540;
		destR.y = 360;
		destR.w = 270;
		destR.h = 400;

		exitR.x = 550;
		exitR.y = 565;
		exitR.w = 400;
		exitR.h = 270;
	}

	void update() override
	{
		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (Game::event.button.button == SDL_BUTTON_LEFT) {
				x = Game::event.button.x;
				y = Game::event.button.y;

				if (x >= destR.x && x <= destR.x + destR.w &&
					y >= destR.y && y <= destR.y + destR.h)
				{
					Game::scene = true;
				}
				if (x >= exitR.x && x <= exitR.x + exitR.w &&
					y >= exitR.y && y <= exitR.y + exitR.h)
				{
					Game::isRunning = false;
				}
			}

		}
	}
};