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

		drawfile = drawFile;
		backfile = backFile;
		return true;
	}


	std::string GetDrawmapcsv() { return drawfile;  }
	std::string Getbackmapcsv() { return backfile;  }
	

private:
	std::string drawfile;
	std::string backfile;

	// �t�@�C�������݂��邩�`�F�b�N����֐�
	bool IsFileAccessible(const std::string& filename) {
		std::ifstream file(filename);
		return file.is_open();  // �t�@�C�����J�������ǂ�����Ԃ�
	}

};

#endif//CSVDATAMANAGER_H

