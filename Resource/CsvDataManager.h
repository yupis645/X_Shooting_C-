#ifndef CSVDATAMANAGER_H
#define CSVDATAMANAGER_H

#include <iostream>
#include <fstream>
#include <string>


class CsvDataManager {
public:
	CsvDataManager() {}

	bool LoadMapFile(const std::string& drawFile, const std::string& backFile) {
		if (!IsFileAccessible(drawFile) || !IsFileAccessible(backFile)) {
			std::cerr << "Failed to load map data: "
				<< drawFile << " or " << backFile << " not found." << std::endl;
			return false;
		}

		mapdatafile = drawFile;
		enemyplacement = backFile;
		return true;
	}


	std::string GetMapData() { return mapdatafile;  }
	std::string GetEnemyPlacement() { return enemyplacement;  }
	

private:
	std::string mapdatafile;
	std::string enemyplacement;

	// ファイルが存在するかチェックする関数
	bool IsFileAccessible(const std::string& filename) {
		std::ifstream file(filename);
		return file.is_open();  // ファイルが開けたかどうかを返す
	}

};

#endif//CSVDATAMANAGER_H

