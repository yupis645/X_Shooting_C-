#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <array>

class CsvDataManager;
class TextureDataManager;
class GameTextureManager;

#include "types.h"
#include "CsvDataManager.h"
#include "TextureDataManager.h"
#include "GameTextureManager.h"
#include <vector>

class ResourceManager {
public:
	ResourceManager();

	bool InitTexture(TextureType type, const UseTextureDataConfig& config);
	bool SetUpTexture(TextureType type);

	bool LoadMapCsvFile(const std::string& frontcsvfile, const std::string& baclcsvfile);


	//=======================================================================================
	// ”CˆÓ‚Ì GameTexture ‚ğ•`‰æ‚·‚éŠÖ”
	//=======================================================================================
	void GameTextureDraw(TextureType type, int index = 0, int x = 0, int y = 0) {
		gametextures->TextureDraw(type,index, x, y);
	}

	std::vector<int> ConvertDrawMapCsv_Vector() {
		return ConvertCsv_VectorReverse(csvdata->GetDrawmapcsv());
	}

	std::shared_ptr<GameTextureManager>& GetTextureManager() {
		return gametextures;
	}

	//std::string GetDrawMapCsv() { return csvdata->Getfrontmapcsv(); }
	std::string GetGroundEnemyslayoutCsv(){	return csvdata->Getbackmapcsv();}

	~ResourceManager() {}

private:
	std::shared_ptr<TextureDataManager> texturedata;
	std::shared_ptr<CsvDataManager> csvdata;
	std::shared_ptr<GameTextureManager> gametextures;

	std::vector<int> ConvertCsv_Vector(const std::string& filename);

    // ‹t‡‚Åƒf[ƒ^‚ğ“Ç‚İ‚ŞŠÖ”
	std::vector<int> ConvertCsv_VectorReverse(const std::string& filename);

};


#endif //RESOURCEMANAGER_H

