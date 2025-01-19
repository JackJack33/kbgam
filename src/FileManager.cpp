#pragma once
#include "FileManager.h"

namespace fs = std::filesystem;

void FileManager::InitializeFilesystem() {
	path = GetAppDataPath();
	logsPath = path + "logs";
	levelsPath = path + "levels";
	prefPath = path + "preferences";
	CreateDirectory(logsPath);
	CreateDirectory(levelsPath);
	CreateDirectory(prefPath);
}

std::string FileManager::GetAppDataPath() {
	const char* basePath = SDL_GetPrefPath("kbgam", "kbgam");
	if (basePath != nullptr) {
		std::string path(basePath);
		SDL_free((void*)basePath);
		return path;
	}
	else {
		std::cout << "Error getting AppData path: " << SDL_GetError() << std::endl;
		return "";
	}
}

void FileManager::CreateDirectory(const std::string& dirPath) {
	if (!fs::exists(dirPath)) {
		if (fs::create_directories(dirPath)) {
			std::cout << "Directory created: " << dirPath << std::endl;
		}
		else {
			std::cout << "Failed to create directory: " << dirPath << std::endl;
		}
	} else {
		std::cout << "Directory already exists: " << dirPath << std::endl;
	}
}

nlohmann::json FileManager::ReadJsonFile(const std::string& filePath) {
	std::ifstream file(filePath);
	nlohmann::json jsonData;

	if (file.is_open()) {
		try {
			file >> jsonData;
		}
		catch (const nlohmann::json::parse_error& e) {
			std::cout << "Error parsing JSON file: " << e.what() << std::endl;
		}
	}
	else {
		std::cout << "Error opening file: " << filePath << std::endl;
	}
	return jsonData;
}

std::vector<Level*> FileManager::ReadAllLevels() {
	std::vector<Level*> levels;

	if (fs::exists(levelsPath)) {
		for (const auto& levelEntry : fs::directory_iterator(levelsPath)) {
			if (!fs::is_directory(levelEntry)) {
				continue;
			}

			std::string levelPath = levelEntry.path().string();
			std::string infoPath = levelPath + "/info.json";

			nlohmann::json infoData = ReadJsonFile(infoPath);
			if (infoData.is_null()) {
				continue;
			}

			Level* level = new Level();
			level->SetAudioPath(infoData["audioPath"].get<std::string>());
			level->SetCoverPath(infoData["coverPath"].get<std::string>());
			level->SetSongName(infoData["songName"].get<std::string>());
			level->SetSongSubName(infoData["songSubName"].get<std::string>());
			level->SetArtistName(infoData["artistName"].get<std::string>());
			level->SetBPM(infoData["bpm"]);

			if (!infoData.contains("difficulties")) {
				continue;
			}
			for (const auto& diffData : infoData["difficulties"]) {
				Difficulty* diff = new Difficulty();
				diff->SetDifficultyPath(diffData["difficultyPath"]);
				diff->SetDifficultyName(diffData["difficultyName"]);
				level->AddDifficulty(diff);
			}

			levels.push_back(level);
		}
	}
	return levels;
}