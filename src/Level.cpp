#pragma once
#include "Level.h"

Level::Level() {}
Level::~Level() {}

void Level::SetAudioPath(std::string str) {
	audioPath = str;
}

void Level::SetCoverPath(std::string str) {
	coverPath = str;
}

void Level::SetSongName(std::string str) {
	songName = str;
}

void Level::SetSongSubName(std::string str) {
	songSubName = str;
}

void Level::SetArtistName(std::string str) {
	artistName = str;
}

void Level::SetBPM(float f) {
	bpm = f;
}

void Level::AddDifficulty(Difficulty* diff) {
	difficulties.push_back(diff);
}

std::string Level::GetAudioPath() {
	return audioPath;
}

std::string Level::GetCoverPath() {
	return coverPath;
}

std::string Level::GetSongName() {
	return songName;
}

std::string Level::GetSongSubName() {
	return songSubName;
}

std::string Level::GetArtistName() {
	return artistName;
}

float Level::GetBPM() {
	return bpm;
}

std::vector<Difficulty*> Level::GetDifficulties() {
	return difficulties;
}