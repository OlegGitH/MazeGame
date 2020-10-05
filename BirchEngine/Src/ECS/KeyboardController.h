#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		sprite = &entity->getComponent<SpriteComponent>();
		transform = &entity->getComponent<TransformComponent>();
	}
	void update() override
	{
			
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym) 
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("Up");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Left");
				//sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Right");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Down");
				break;
			default:
				break;
			}

		}
		if(Game::event.type == SDL_KEYUP)
		{ 
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				//sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		}
	}
};