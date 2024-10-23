#ifndef IMAPMANAGER_H
#define IMAPMANAGER_H

class GameTexture;

class IMapManager {
public :
	~IMapManager() = default;


	virtual int Init() = 0;
	virtual int Update() = 0;
	virtual int Draw() = 0;

	virtual bool LoadMapChipTexture(std::shared_ptr<GameTexture> tex)= 0;

	virtual const std::vector<int>& GetDrawMapData() const = 0;
	virtual void SetDrawMapData(std::vector<int> copyvector) = 0;

};

#endif //IMAPMANAGER_H