#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include <string>

class LogoComponent : public Component {
private:
	SDL_Texture* texture;
	SDL_Rect destRect;

	int sizeX, sizeY, posX, posY;

public:

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	LogoComponent(std::string id, int sizeX, int sizeY, int posX, int posY ) {
		setTex(id);
		
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->posX = posX;
		this->posY = posY;

	}

	~LogoComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void update() override
	{
		destRect.h = sizeY;
		destRect.w = sizeX;
		destRect.x = posX;
		destRect.y = posY;

		if (Game::scene == 1) {
			SDL_DestroyTexture(texture);
		}

	}

	void draw() override
	{
		//TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
		TextureManager::Draw(texture, destRect);
		//SDL_RenderCopy(renderer, playerTex, NULL, NULL);
	}

};