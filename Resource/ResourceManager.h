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

	bool InitTextureLoad(TextureType type, const std::wstring&);
	bool SliceTexturebytype(TextureType type,TextureConfig);


	std::shared_ptr<GameTexture> GetTexture(TextureType type);

	std::shared_ptr<GameTextureManager>& GetTextureManager() {	return gametextures;	}


	bool LoadMapCsvFile(const std::string& frontcsvfile, const std::string& baclcsvfile);

	std::vector<int> ConvertDrawMapCsv_Vector();
	//std::string GetDrawMapCsv() { return csvdata->Getfrontmapcsv(); }
	std::string GetGroundEnemyslayoutCsv(){	return csvdata->Getbackmapcsv();}


	

	~ResourceManager() {}

private:
	std::shared_ptr<TextureDataManager> texturedata;
	std::shared_ptr<CsvDataManager> csvdata;
	std::shared_ptr<GameTextureManager> gametextures;

	std::vector<int> ConvertCsv_Vector(const std::string& filename);

    // ãtèáÇ≈ÉfÅ[É^Çì«Ç›çûÇﬁä÷êî
	std::vector<int> ConvertCsv_VectorReverse(const std::string& filename);

};


#endif //RESOURCEMANAGER_H

