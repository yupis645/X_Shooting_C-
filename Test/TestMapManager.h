
#ifndef TESTMapManager_H
#define TESTMAPMANAGER_H

class GameTexture;
class ResourceManager;
class SpriteRenderer;

#include <iostream>
#include <vector>
#include "IMapManager.h"
#include "types.h"


class TestMapManager: public IMapManager {
public:
    // コンストラクタ
    TestMapManager(std::shared_ptr<ResourceManager> rm);

   //=============================================================================================
   //                              ライフサイクル関数
   //=============================================================================================
    int Init() override;       //初期化
    int Update() override;     //更新
    int Draw() override;       //描画

  //=============================================================================================
  //                              マップチップ画像のロード
  //=============================================================================================
    bool LoadMapChipTexture(std::shared_ptr<GameTexture> tex)override;

  //=============================================================================================
  //                              Getter / Setter
  //=============================================================================================
    const std::vector<int>& GetDrawMapData() const override { return mapdata; } //マップチップのint配列のgetter
    void SetDrawMapData(std::vector<int> copyvector) { mapdata = copyvector; }  //マップチップのint配列のsetter


    //=============================================================================================
    //                              デストラクタ
    //=============================================================================================
    ~TestMapManager() = default;
private:
    int currentnumber;			    //現在のステージ番号を記憶する
    int currentpartition;			//ステージを分割した中で現在は何番目かを示す
    
    std::shared_ptr<GameTexture> mapchip;
    std::vector<int> backmap;
    std::vector<int> mapdata;
    
    MapStatus primarymap;
    MapStatus secondarymap;

    std::shared_ptr< SpriteRenderer> render_;

    void MapDataUpdate(MapStatus& map,int startprogress);       //描写するマップの配列を更新する
};



#endif //TestMapManager_H