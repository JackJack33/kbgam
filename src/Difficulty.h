#pragma once
#include "Depend.h"

class Difficulty {
public:

	Difficulty();
	~Difficulty();

	void SetDifficultyPath(std::string str);
	void SetDifficultyName(std::string str);

	std::string GetDifficultyPath();
	std::string GetDifficultyName();

private:

	std::string difficultyPath;
	std::string difficultyName;
};