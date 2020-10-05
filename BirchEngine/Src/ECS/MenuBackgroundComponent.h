#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include <string>

class MenuBackgroundComponent : public Component {
private:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	

public:

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	MenuBackgroundComponent(std::string id) {
		setTex(id);
	}

	~MenuBackgroundComponent(){
		SDL_DestroyTexture(texture);
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void update() override
	{
		if (Game::scene == 1) {
			SDL_DestroyTexture(texture);
		}
	}

	void draw() override
	{
		//TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
		TextureManager::Draw(texture);
		//SDL_RenderCopy(renderer, playerTex, NULL, NULL);
	}

};