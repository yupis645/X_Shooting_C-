
//---------------------------------------------------------------------------------------------------------------------------------------------
//                                              描写するマップを管理するクラス(テストクラス)
// 
// マップチップを並べたint配列を元にマップの座標を管理しつつ、描画する
// 描画できるスクリーンのサイズと同じ大きさを持ったint配列のprimarymapとsecondarymapを交互に描画することでスクロールする
//---------------------------------------------------------------------------------------------------------------------------------------------

#include "TestMapManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameTexture.h"



using namespace MapConfig;      //mapサイズやチップサイズなどが定義されている定数の集まり

//.cpp内で使う定数
namespace {
    constexpr int ZERO_INDEX_OFFSET = 1;           //ループの際にインデックスを後ろから数える場合のオフセット値
    constexpr int DRAWMAP_SIZE = MAP_H * MAP_W;      //1フレームでカウントした場合のマップの列数
    constexpr int DRAWMAP_HIGH = MAP_H * CHIP_SIZE;      //1フレームでカウントした場合のマップの列数
    constexpr int DRAWMAP_RANGE = DRAWMAP_HIGH * 2;      //一つのマップが描画する距離(フレームインからフレームアウトまで)
    constexpr int PARTITION_MAX = 4;                     //マップの分割数
    constexpr int INIT_Y_OFFSET = -DRAWMAP_HIGH;      //マップが描画範囲に入る前のy座標の補正値(描画は一番後ろのインデックスから始まるので左上座標はDRAWMAP_HIGH分引く必要がある)
}

TestMapManager::TestMapManager(std::shared_ptr<ResourceManager> rm) : currentnumber(0), currentpartition(0),
mapchip(0), mapdata({}), backmap({}),
primarymap({ false, {}, 0, 0 }),
secondarymap({ false, {},0,0 })
{
    mapchip = rm->GetTexture(TextureType::Map);
    SetDrawMapData(rm->ConvertDrawMapCsv_Vector());
}

//=======================================================================================
//                      初期化
// 
// ゲーム始めるときの初期設定をする
//=======================================================================================
int TestMapManager::Init()
{
    currentpartition = 0;                       //ステージの最初からになるようにcurrentpartitionを0にする
    MapDataUpdate(primarymap, DRAWMAP_HIGH);    //スタート時はmap全てが描画されいる状態にするため、y座標を調整する
    MapDataUpdate(secondarymap, 0);             //スタート時でも普段通り画面の上から描写を開始する
    
    return 0;
}

//=======================================================================================
//                      更新
// 
// 主にマップのy座標を更新する。
// y座標が一定距離になったら、int配列を更新して再びy座標0から描写を再開する
//=======================================================================================
int TestMapManager::Update()
{
    primarymap.y++;        //プライマリマップのy座標を更新する
    secondarymap.y++;      //セカンダリマップのy座標を更新する

    if (primarymap.y >= DRAWMAP_RANGE)      MapDataUpdate(primarymap, 0);       //プライマリマップy座標が一定距離進んだらマップを更新する
    if (secondarymap.y >= DRAWMAP_RANGE)    MapDataUpdate(secondarymap,0);      //セカンダリマップy座標が一定距離進んだらマップを更新する
    
    return 0;
}

//=======================================================================================
//                   int配列を更新する(private関数)
// 
// マップチップの配置をしているint配列からマップサイズに分割した配列を受け取る。
// 引き数2 の値はy座標の初期値を設定する
//=======================================================================================
void TestMapManager::MapDataUpdate(MapStatus& map,int startprogress = 0)
{
    map.y = startprogress;      //y座標の初期値を設定する(指定がなければ0)

    int indexoffset = DRAWMAP_SIZE * currentpartition - ZERO_INDEX_OFFSET;       //ステージの進行度に応じて取得するインデックスに補正をかける
    for (int r = 0; r < MAP_H; r++) {
        for (int r2 = 0; r2 < MAP_W; r2++) {
            int counter = r2 + (r * MAP_W);        //ループ中常に1カウントする値
            map.data[counter] = currentpartition == 0 ? 0 : mapdata[indexoffset - counter];     //進行度が0の場合マップチップは全て0で統一する(スタートエリア)
                                                                                                //それ以外ならint配列からマップチップの配置を受けとる
        }
    }

    currentpartition++;
    if (currentpartition > PARTITION_MAX) currentpartition = 0;
}

int TestMapManager::Draw()
{
    for (int r = 0; r < MAP_H; r++) {
        for (int r2 = 0; r2 < MAP_W; r2++) {
            int counter = r2 + (r * MAP_W);
            int x = r2 * CHIP_SIZE;
            int y = INIT_Y_OFFSET + r * CHIP_SIZE;
            render_->DrawFromTopLeftPos(mapchip, primarymap.data[counter], x, primarymap.y + y);
            render_->DrawFromTopLeftPos(mapchip, secondarymap.data[counter], x, secondarymap.y + y);
        }
    }

    return 0;
}

//=============================================================================================
//                              マップチップ画像のロード
//=============================================================================================

inline bool TestMapManager::LoadMapChipTexture(std::shared_ptr<GameTexture> tex) {
    // テクスチャが有効かどうかを確認する
    if (!tex) {
        std::cerr << "Failed to load map chip texture: tex is null." << std::endl;
        return false;  // 失敗を示す
    }

    // 正常に読み込まれた場合
    mapchip = tex;
    return true;        // 成功を示す
}
