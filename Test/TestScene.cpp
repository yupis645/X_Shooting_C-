#include "TestScene.h"

#include <filesystem>
#include "common.h"
#include "Geometry.h"
#include "conioex.h"
#include "GameTextureManager.h"

using namespace ScreenConfig;
using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

TestScene::TestScene(std::shared_ptr<DIContainer> con,
    std::shared_ptr<Scenestatus> st,
    std::shared_ptr<GameStatus> gs,
    std::shared_ptr<ResourceManager> rm,
    std::shared_ptr<IInputManager> im) :
    scenestatus_(st),gamestatus_(gs),inputmanager_(im), resourcemanager_(rm),
    mapmanager_(con->Create<IMapManager>())
{

    mapmanager_->LoadMapChipTexture(rm->GetTextureManager()->GetTexture(TextureType::Map));     //マップチップのロード
    mapmanager_->SetDrawMapData(rm->ConvertDrawMapCsv_Vector());
    
    //mapmanager_->LoadFrontMapDataCsv(rm->Getmapcsv(ScopeMapData::frontmap));                    //フロントマップのcsv
    //mapmanager_->LoadBackMapDataCsv(rm->Getmapcsv(ScopeMapData::backmap));                      //バックマップのcsv


}

int TestScene::Init() {
    SceneBase::Init();
    mapmanager_->Init();
    return 0;
}
int TestScene::Update() { 
    mapmanager_->Update();
    return 0; 
}

int TestScene::Draw() {

    mapmanager_->Draw();

  /*  for (int r = 1; r <= MAP_H; r++) {
        for (int r2 = 0; r2 < MAP_W; r2++) {
            resouce->GetTextureManager()->Draw(TextureType::Map, mapmanager_->GetFrontMapData()[r * r2], 0 + ((r2 * 32), -32 + (r * 32)));
        }
    } 

    int w = 0;*/
   /* for (int r = 0; r < 475 ; r++) {
        if (r % MAP_W == 0) w++;
        resouce->GetTextureManager()->Draw(TextureType::Map, mapmanager_->GetMapData(ScopeMapData::frontmap)[r], 0 + ((r % MAP_W) * 32), -32 + (w * 32));

    }*/
    resourcemanager_->GameTextureDraw(TextureType::Title, 0, SRN_W / 2 - 99, 100);  // タイトルの描画
    resourcemanager_->GameTextureDraw(TextureType::Player, 2, 100, 100);         // プレイヤーの描画


    //本体の描写
    for (int r = 0; r <= 10; r++) {
        for (int r2 = 0; r2 <= 10; r2++) {
            int pic_num = r * 11 + r2;
            resourcemanager_->GameTextureDraw(TextureType::Boss, pic_num, 0 + (r2 * 32), 0 + (r * 32));         // プレイヤーの描画// 0 ～ 110の範囲で計算される

        }
    }


    return 0;
}
