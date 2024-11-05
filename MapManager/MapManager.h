#ifndef MAPMANAGER_H
#define MAPMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              地表のテクスチャの配置などを管理するクラス
// 
// マップのタイルチップ番号を記憶した配列と地面のテクスチャを持ち、マップのスクロールと描写を行う
// 1マップに付きスタートエリアである森のマップも合わせて (MAP_H * MAP_W) * 5 の広さを持つ
// 描写の際にはスクリーンの描画範囲である MAP_H * MAP_W の広さで区切り、
//      primarymapとsecondarymapという二つの配列を使って交互に描写している。
// メンバ変数 mapchip にはint番号に応じた地面のテクスチャが入っている
// メンバ変数 mapdata には分割前の１マップ分のまプチップの配置が入っている。
//      primarymapとsecondarymapは mapdata からマップチップの配置を受け取る
//----------------------------------------------------------------------------------------------------

class ResourceManager;
class GameTexture;
class SpriteRenderer;


#include "IMapManager.h"


class MapManager : public IMapManager {
public:
    MapManager(std::shared_ptr<ResourceManager> rm);        //コンストラクタ
   

    int Init() override;       //初期化
    int Update() override;     //更新
    int Draw() override;       //描画

    bool LoadMapChipTexture(std::shared_ptr<GameTexture> tex)override;      //マップチップ画像のロード

    void SwapMapdata();       //int配列のmapdataを更新する
 
    const std::vector<int>& GetDrawMapData() const override { return mapdata; } //マップチップのint配列のgetter
    void SetDrawMapData(std::vector<int> copyvector) { mapdata = copyvector; }  //マップチップのint配列のsetter

    ~MapManager() = default;        ///デストラクタ


private:
    int currentnumber;			    //現在のステージ番号を記憶する
    int currentpartition;			//ステージを分割した中で現在は何番目かを示す

    std::shared_ptr<GameTexture> mapchip;       //マップチップの画像を保管しておく変数
    std::vector<int> backmap;               
    std::vector<int> mapdata;           //マップチップの配置を管理するint配列

    MapStatus primarymap;       //分割したマップデータを保持しておく変数
    MapStatus secondarymap;     //分割したマップデータを保持しておく変数
     
    std::shared_ptr<SpriteRenderer> render_;
    std::shared_ptr<ResourceManager> resource_;

    void MapDataUpdate(MapStatus& map, int startprogress);       //描写するマップの配列を更新する
};




#endif //MAPMANAGER_H