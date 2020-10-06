#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip Flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, Flip); 
}

void TextureManager::Draw(SDL_Texture* tex)
{
	SDL_RenderCopy(Game::renderer, tex, NULL, NULL);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect destR)
{
	SDL_RenderCopy(Game::renderer, tex, NULL, &destR);
}
void TextureManager::Destroy(SDL_Texture* tex) {
	SDL_DestroyTexture(tex);
}
