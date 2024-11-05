#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

class GameApplication;


#include "CsvDataManager.h"
#include  "TextureManager.h"

class ResourceManager {
public:
	ResourceManager(std::shared_ptr<GameApplication> g_app);

	bool InitTextureLoad(TextureType type, const std::wstring&);
	bool SliceTexturebytype(TextureType type,TextureConfig);


	std::shared_ptr<GameTexture> GetTexture(TextureType type);

	const std::map<TextureType, std::shared_ptr<GameTexture>>& GetAllTexture() const { return texturemanager_->GetAllTexture(); }


	bool LoadTexture(TextureType type,const wchar_t* textureFilePath);

	std::vector<std::unique_ptr<Textures>> SplitTexture(TextureType type);








	bool LoadMapCsvFile(const std::string& frontcsvfile, const std::string& baclcsvfile);

	std::vector<int> ConvertDrawMapCsv_Vector();
	//std::string GetDrawMapCsv() { return csvdata->Getfrontmapcsv(); }
	std::string GetGroundEnemyslayoutCsv(){	return csvdata->GetEnemyPlacement();}


	

	~ResourceManager() = default;

private:
	std::vector<int> ConvertCsv_Vector(const std::string& filename);

	// ãtèáÇ≈ÉfÅ[É^Çì«Ç›çûÇﬁä÷êî
	std::vector<int> ConvertCsv_VectorReverse(const std::string& filename);

	std::shared_ptr<GameApplication> gameapp_;
	std::shared_ptr<TextureManager> texturemanager_;
	std::shared_ptr<CsvDataManager> csvdata;


};


#endif //RESOURCEMANAGER_H

