#pragma once
#include "Depend.h"
#include "Scene.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, int w = 800, int h = 600, bool fullscreen = false);

	void handleEvents();
	void handleKeyboard();
	void update();
	void render();
	void clean();

	bool running();

private:

	int width;
	int height;
	int count;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	std::vector<Scene*> scenes;
	Scene* activeScene;

	Uint8* keyStatePrevious;
};