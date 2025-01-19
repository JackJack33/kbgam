#pragma once
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	game = new Game();
	game->init("kbgam");

	// timing done in integer ms
	int currentTime = SDL_GetTicks();
	int accumulator = 0;
	int t = 0;
	int dt = 5;

	while (game->running()) {

		int newTime = SDL_GetTicks();
		int frameTime = newTime - currentTime;
		if (frameTime > 250) {
			frameTime = 250;
		}
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt) {
			game->update(dt);
			t += dt;
			accumulator -= dt;
		}

		game->render();
	}

	game->clean();

	return 0;
}