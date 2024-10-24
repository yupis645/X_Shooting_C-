#include "GameScene.h"


#include "Game.h"
#include "DIContainer.h"
#include "SceneBase.h"
#include "MapManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameSceneFactory.h"
#include "Player.h"

GameScene::GameScene(std::shared_ptr<DIContainer> con)
    : container_(con),
    gamestatus_(con->Create<GameStatus>()),
    input_(con->Create<IInputManager>()),
    resourcemanager_(con->Create<ResourceManager>()),
    instanceFactory_ (std::make_shared<GameSceneFactory>(con, player_,mapmanager_,enemys_,bullets_))
{
    player_ = instanceFactory_->CreatePlayer();
    mapmanager_ = instanceFactory_->CreateMap();
    bullets_ = instanceFactory_->CreateBulletsManager();
    enemys_ = instanceFactory_->CreateEnemysManager();
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

    //if (input_->IsFlagSet(IInputManager::InputFlag::shot, IInputManager::InputMode::pushdown))bullets_->CreatePlayerShot(player_->GetPosition());
    //if (input_->IsFlagSet(IInputManager::InputFlag::bom, IInputManager::InputMode::pushdown))bullets_->CreatePlayerBom(player_->GetPosition());


    if (input_->IsFlagSet(IInputManager::InputFlag::bom, IInputManager::InputMode::pushdown))bullets_->CreateEnemyShot(Vector2(300,200), player_->GetPosition());
    if (input_->IsFlagSet(IInputManager::InputFlag::shot, IInputManager::InputMode::pushdown))bullets_->CreatePlayerShot(player_->GetPosition());
   

    bullets_->Update(framecount);


    return 0;
}

int GameScene::Draw()
{
    mapmanager_->Draw();
    player_->Draw();
    bullets_->Draw();
    return 0;

}

