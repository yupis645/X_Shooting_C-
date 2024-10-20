#ifndef MAPMANAGER_H
#define MAPMANAGER_H



class GameTexture;
#include <iostream>
#include <vector>
#include <string>
#include "types.h"

#include "GameTexture.h" 
#include "IMapManager.h"


class MapManager : public IMapManager {
public:
    //=============================================================================================
    //                              コンストラクタ
    //=============================================================================================
    MapManager() : currentnumber(0), currentpartition(0),
        mapchip(0), mapdata({}), backmap({}),
        primarymap({ false, {}, 0, 0 }),
        secondarymap({ false, {},0,0 })
    {
        mapmanager_->LoadMapChipTexture(rm->GetTextureManager()->GetTexture(TextureType::Map));     //マップチップのロード
        mapmanager_->SetDrawMapData(rm->ConvertDrawMapCsv_Vector());

        //mapmanager_->LoadFrontMapDataCsv(rm->Getmapcsv(ScopeMapData::frontmap));                    //フロントマップのcsv
        //mapmanager_->LoadBackMapDataCsv(rm->Getmapcsv(ScopeMapData::backmap));                      //バックマップのcsv

    }
    //=============================================================================================
    //                              デストラクタ
    //=============================================================================================
    ~MapManager() = default;

    //=============================================================================================
    //                              ライフサイクル関数
    //=============================================================================================
    int Init() override;       //初期化
    int Update() override;     //更新
    int Draw() override;       //描画

    //=============================================================================================
    //                              マップチップ画像のロード
    //=============================================================================================
    bool LoadMapChipTexture(std::shared_ptr<GameTexture> tex)override {
        // テクスチャが有効かどうかを確認する
        if (!tex) {
            std::cerr << "Failed to load map chip texture: tex is null." << std::endl;
            return false;  // 失敗を示す
        }

        // 正常に読み込まれた場合
        mapchip = tex;
        return true;        // 成功を示す
    }

    //=============================================================================================
    //                              Getter / Setter
    //=============================================================================================
    const std::vector<int>& GetDrawMapData() const override { return mapdata; } //マップチップのint配列のgetter
    void SetDrawMapData(std::vector<int> copyvector) { mapdata = copyvector; }  //マップチップのint配列のsetter


private:
    int currentnumber;			    //現在のステージ番号を記憶する
    int currentpartition;			//ステージを分割した中で現在は何番目かを示す

    std::shared_ptr<GameTexture> mapchip;       //マップチップの画像を保管しておく変数
    std::vector<int> backmap;               
    std::vector<int> mapdata;           //マップチップの配置を管理するint配列

    MapStatus primarymap;       //分割したマップデータを保持しておく変数
    MapStatus secondarymap;     //分割したマップデータを保持しておく変数

    void MapDataUpdate(MapStatus& map, int startprogress);       //描写するマップの配列を更新する
};




#endif //MAPMANAGER_H