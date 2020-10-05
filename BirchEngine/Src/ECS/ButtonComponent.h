#pragma once
#include "Components.h" 
#include "SDL.h"
#include <string>

class ButtonComponent : public Component{

public:

	ButtonComponent() = default;

	ButtonComponent(std::string id, int xPos, int yPos, int srcX, int srcY, int sizeX, int sizeY) {

		setTex(id);
		Xpos = xPos;
		Ypos = yPos;
		SrcX = srcX;
		SrcY = srcY;
		SizeW = sizeX;
		SizeH = sizeY;
	}

	~ButtonComponent(){
		SDL_DestroyTexture(texture);
	}

	void setTex(std::string id) 
	{
		texture = Game::assets->GetTexture(id);
	}


	void update () override
	{

		srcR.x = SrcX;
		srcR.y = SrcY;
		srcR.w = SizeW;
		srcR.h = SizeH;

		destR.x = Xpos;
		destR.y = Ypos;
		destR.w = SizeW;
		destR.h = SizeH;

		if (Game::scene == 1) {
			SDL_DestroyTexture(texture);
		}

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcR, destR, spriteFlip);
	}


 private:

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;
	int Xpos, Ypos, SrcX, SrcY, SizeW, SizeH;


};