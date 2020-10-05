
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>
#include <string>

Map* map;
Manager manager;

SDL_Texture* playerTex;

SDL_Rect srcR, destR;

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

SDL_Rect Game::camera = { 0, 0,700, 1100};

AssetManager* Game::assets = new AssetManager(&manager);

TextureManager* tex;

bool Game::isRunning = false;

bool Game::scene = false;

bool Game::change = false;

std::string path = "assets/mapTry.map";

auto& player(manager.addEntity());
auto& background(manager.addEntity());
auto& labelOne(manager.addEntity());
auto& labelTwo(manager.addEntity());
auto& labelThree(manager.addEntity());
auto& backForbutton(manager.addEntity());
auto& button(manager.addEntity());
auto& logo(manager.addEntity());

Game::Game() 
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{

	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}


	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	SDL_Color black = { 0, 0, 0, 0 };
	assets->AddFont("PS2P-Reg", "assets/PressStart2P-Regular.ttf", 20);
	labelOne.addComponent<UILabel>(540, 360, "Test String", "PS2P-Reg", black);
	labelTwo.addComponent<UILabel>(505, 465, "Test String", "PS2P-Reg", black);
	labelThree.addComponent<UILabel>(550, 565, "Test String", "PS2P-Reg", black);

	assets->AddTexture("MenuBackground", "assets/BackgroundMenu.png");
	background.addComponent<MenuBackgroundComponent>("MenuBackground");

	assets->AddTexture("menuButton", "assets/try.png");
	backForbutton.addComponent<ButtonComponent>("menuButton", 450, 250, 30, 200, 270, 400);

	assets->AddTexture("Button", "assets/try.png");
	button.addComponent<ButtonComponent>("Button", 478, 250, 300, 200, 270, 400);

	assets->AddTexture("Logo", "assets/logo2.png");
	logo.addComponent<LogoComponent>("Logo", 670, 150, 280, 50);

	
	player.addComponent<MouseController>();


		assets->AddTexture("terrain", "assets/tiles2.png");
		assets->AddTexture("player", "assets/tremel.png");
		assets->AddTexture("projectile", "assets/D.png");
		assets->AddTexture("enemy", "assets/D.png");

		map = new Map("terrain", 2, 16);

		map->LoadMap(path, 60, 60);

		player.addComponent<TransformComponent>(60.0f, 70.0f, 48, 32, 1);
		player.addComponent<SpriteComponent>("player", true);
		player.addComponent<ColliderComponent>("player");
		player.addComponent<KeyboardController>();
		player.addComponent<EnemySpriteComponent>("enemy", true);
		player.addGroup(groupPlayers);

	//assets->CreateProjectile(Vector2D(200, 350), Vector2D(1,0), 200, 0, "projectile");
	//assets->CreateProjectile(Vector2D(400, 620), Vector2D(0,0), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(600, 300), Vector2D(0,0), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(600, 500), Vector2D(2,-1), 200, 2, "projectile");

		delete map;
	
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemy(manager.getGroup(Game::groupEnemy));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	
	std::stringstream ss;
	ss << "Start";
	labelOne.getComponent<UILabel>().SetLabelText(ss.str(), "PS2P-Reg");
	ss.str("");
	ss << "Continue";
	labelTwo.getComponent<UILabel>().SetLabelText(ss.str(), "PS2P-Reg");
	ss.str("");
	ss << "Quit";
	labelThree.getComponent<UILabel>().SetLabelText(ss.str(), "PS2P-Reg");


	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;


	manager.refresh();
	manager.update();


		for (auto& c : colliders)
		{
			SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(cCol, playerCol))
			{
				player.getComponent<TransformComponent>().position = playerPos;
			}
		}

		for (auto& p : projectiles) {
			if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
			{
				p->destroy();
			}
		}

		camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
		camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 520);

		if (camera.x < 0) camera.x = 0;
		if (camera.y < 0) camera.y = 0;
		if (camera.x > camera.w) camera.x = camera.w;
		if (camera.y > camera.h) camera.y = camera.h;


}



void Game::render()
{
	SDL_RenderClear(renderer);
	
		for (auto& e : enemy) {
			e->draw();
		}

		for (auto& t : tiles) {
			t->draw();
		}

		for (auto& c : colliders)
		{
			c->draw();
		}

		for (auto& p : players) {
			p->draw();
		}

		for (auto& p : projectiles) {
			p->draw();
		
	}

	background.draw();

	backForbutton.draw();

	button.draw();

	logo.draw();

	labelOne.draw();
	labelTwo.draw();
	labelThree.draw();

	SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	delete assets;
}