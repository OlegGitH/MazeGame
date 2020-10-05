#pragma once
#include "Game.h"

class TextureManager{

	public:
		static SDL_Texture* LoadTexture(const char* fileName);
		static void Draw(SDL_Texture* tex, SDL_Rect src,SDL_Rect dest, SDL_RendererFlip Flip);
		static void Draw(SDL_Texture* tex);
		static void Draw(SDL_Texture* tex, SDL_Rect destR);

		void Destroy(SDL_Texture* tex);
	
};
