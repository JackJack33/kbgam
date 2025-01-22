#pragma once
#include "Depend.h"
#include "Difficulty.h"

class Level {

public:
	Level();
	~Level();

	void SetAudioPath(std::string str);
	void SetCoverPath(std::string str);
	void SetSongName(std::string str);
	void SetSongSubName(std::string str);
	void SetArtistName(std::string str);
	void SetBPM(float f);
	void AddDifficulty(Difficulty* diff);

	std::string GetAudioPath();
	std::string GetCoverPath();
	std::string GetSongName();
	std::string GetSongSubName();
	std::string GetArtistName();
	float GetBPM();
	std::vector<Difficulty*> GetDifficulties();
	Difficulty* GetDifficulty(int diffindex);

private:

	std::string audioPath;
	std::string coverPath;

	std::string songName;
	std::string songSubName;
	std::string artistName;

	float bpm;
	std::vector<Difficulty*> difficulties;
};