#pragma once
#include "Difficulty.h"

Difficulty::Difficulty() {}
Difficulty::~Difficulty() {}

void Difficulty::SetDifficultyPath(std::string str) {
	difficultyPath = str;
}

void Difficulty::SetDifficultyName(std::string str) {
	difficultyName = str;
}

std::string Difficulty::GetDifficultyPath() {
	return difficultyPath;
}

std::string Difficulty::GetDifficultyName() {
	return difficultyName;
}