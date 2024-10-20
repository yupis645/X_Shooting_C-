#include "GameScene.h"


GameScene::GameScene(std::shared_ptr<DIContainer> con, std::shared_ptr<Scenestatus> ss, 
                std::shared_ptr<GameStatus> gs, std::shared_ptr<IInputManager> input, std::shared_ptr<ResourceManager> rm)
    : container_(con),scenestatus_(ss),gamestatus_(gs),inputmanager_(input),resourcemanager_(rm),
    mapmanager_(con->Create<IMapManager>())
{
    // DIコンテナから依存関係（スマートポインタ）を取得し、メンバ変数に保持

/*    player_ = container->Create<IPlayer>();
    enemymanager_ = container->Create<IEnemysManager>();
    bulletmanager_ = container->Create<IBulletManager>();
    mapmanager_ = container->Create<IMapManager>();*/
}

int GameScene::Init()
{
    /*player_->Init();
    enemymanager_->ALLEnemysInit();
    bulletmanager_->InitEnemyShot();
    bulletmanager_->InitPlayerBom();
    bulletmanager_->InitPlayerShot();
    */
    mapmanager_->Init();
    
    return 0;

}


int GameScene::Update()
{
 /*   scenestatus_->FrameCountUpdate(1);*/

    auto FC = scenestatus_->Getframecount();

   /* int p = player_->Update(FC,inputmanager_->Directionkey());
    int ae = enemymanager_->AirEnemysUpdate(FC);
    int ge = enemymanager_->GroundEnemysUpdate(FC);
    int es = bulletmanager_->UpdateEnemyShot(FC);
    int pb = bulletmanager_->UpdatePlayerBom(FC);
    int ps = bulletmanager_->UpdatePlayerShot(FC);*/
    int m = mapmanager_->Update();

    return 0;
}

int GameScene::Draw()
{
   /* player_->Draw();
    enemymanager_->AirEnemysDraw();
    enemymanager_->GroundEnemysDraw();
    bulletmanager_->DrawEnemyShot();
    bulletmanager_->DrawPlayerBom();
    bulletmanager_->DrawPlayerShot(player_);*/
    mapmanager_->Draw();
    
    return 0;

}

