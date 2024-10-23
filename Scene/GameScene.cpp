#include "GameScene.h"
#include "Player.h"

GameScene::GameScene(std::shared_ptr<DIContainer> con)
    : container_(con),
    gamestatus_(con->Create<GameStatus>()),
    input_(con->Create<IInputManager>()),
    resourcemanager_(con->Create<ResourceManager>()),
    instanceFactory_ (std::make_shared<GameSceneFactory>(con))
{
    player_ = instanceFactory_->CreatePlayer();
    mapmanager_ = instanceFactory_->CreateMap();
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

    if(input_->IsFlagSet(IInputManager::InputFlag::bom,IInputManager::InputMode::pushdown) ) player_->Setshootdown(true);

    return 0;
}

int GameScene::Draw()
{
    mapmanager_->Draw();
    player_->Draw();
    
    return 0;

}

