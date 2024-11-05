#include "GameScene.h"

#include "DIContainer.h"
#include "SceneBase.h"
#include "MapManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameSceneFactory.h"
#include "Player.h"
#include "CollisionManager.h"


GameScene::GameScene(std::shared_ptr<DIContainer> con)
    : container_(con),
    gamestatus_(con->Create<GameStatus>()),
    input_(con->Create<IInputManager>()),
    resourcemanager_(con->Create<ResourceManager>()),
    instanceFactory_ (std::make_shared<GameSceneFactory>(con)),
    collisionmanager_(std::make_shared<CollisionManager>())
{
    player_ = instanceFactory_->CreateTestPlayer();
    mapmanager_ = instanceFactory_->CreateMap();
    bullets_ = instanceFactory_->CreateTestBulletsManager();
    enemys_ = instanceFactory_->CreateTestEnemysManager();
    
}

int GameScene::Init()
{
    SceneBase::Init();
    mapmanager_->Init();
    
    return 0;

}


int GameScene::Update()
{
    int m = mapmanager_->Update();
    int s = player_->Update(framecount,input_->Dirctionkeyinput(IInputManager::InputMode::press));

    if (input_->IsFlagSet(IInputManager::InputFlag::shot, IInputManager::InputMode::pushdown))bullets_->CreatePlayerShot(player_->GetPosition());
    if (input_->IsFlagSet(IInputManager::InputFlag::bom, IInputManager::InputMode::pushdown))bullets_->CreatePlayerBom(player_->GetPosition());
    if (s == 2) {
        return SceneID::GAME;
    }

    bullets_->Update(framecount);
    enemys_->AirEnemysUpdate(framecount);
    enemys_->GroundEnemysUpdate(framecount);
    collisionmanager_->CollisionUpdate(bullets_,enemys_,player_);


    return 0;
}

int GameScene::Draw()
{

    mapmanager_->Draw();
    player_->Draw();
    enemys_->AirEnemysDraw();
    enemys_->GroundEnemysDraw();
    bullets_->Draw();


    return 0;

}

