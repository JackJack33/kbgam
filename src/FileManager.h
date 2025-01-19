#pragma once
#include "Depend.h"
#include "Level.h"
#include "../json.hpp"

class FileManager {
public:
	void InitializeFilesystem();
	std::string GetAppDataPath();

	void CreateDirectory(const std::string& dirPath);
	nlohmann::json ReadJsonFile(const std::string& filePath); 

	std::vector<Level*> ReadAllLevels();

private:

	std::string path;
	std::string logsPath;
	std::string levelsPath;
	std::string prefPath;
};