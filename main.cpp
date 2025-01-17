#pragma once
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;
	uint32_t frameStart;
	uint32_t frameTime;

	game = new Game();
	game->init("kbgam");

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->handleKeyboard();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	game->clean();

	return 0;
}