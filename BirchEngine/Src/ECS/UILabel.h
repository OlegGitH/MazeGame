#pragma once

#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont);
	}
	~UILabel()
	{
	}

	void SetLabelText(const std::string text, const std::string font)
	{	
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void update() override{
		if (Game::scene == 1) {
			SDL_DestroyTexture(labelTexture);
		}
	}

	void draw() override
	{
		//SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
		SDL_RenderCopy(Game::renderer, this->labelTexture, nullptr, &this->position);
		SDL_DestroyTexture(this->labelTexture);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};