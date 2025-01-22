#pragma once
#include "../Depend.h"
#include "../Scene.h"
#include "../Level.h"

class DifficultyMenuScene : public Scene {
public:
	DifficultyMenuScene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h);
	~DifficultyMenuScene();

	void Start() override;

	void SetLevel(Level* level_in);
	void NextDifficultyIndex();
	void PrevDifficultyIndex();
	void DeleteDifficultyListObjects();
	void UpdateDifficultyList();

private:

	Level* level;
	int diffListIndex;
	int numDiffs;
	std::vector<GameObject*> diffListGameObjects;

};