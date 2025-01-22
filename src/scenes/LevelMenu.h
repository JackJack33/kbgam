#pragma once
#include "../Depend.h"
#include "../Scene.h"

class LevelMenuScene : public Scene {
public:
	LevelMenuScene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h);
	~LevelMenuScene();

	void Start() override;

	void NextLevelIndex();
	void PrevLevelIndex();
	void DeleteLevelListObjects();
	void UpdateLevelList();

private:
	int levelListIndex;
	int numLevels;
	std::vector<GameObject*> levelListGameObjects;
};