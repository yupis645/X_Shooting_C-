#include "GameScene.h"

GameScene::GameScene(std::shared_ptr<DIContainer> con)
    : container_(con),
    gamestatus_(con->Create<GameStatus>()),
    inputmanager_(con->Create<IInputManager>()),
    resourcemanager_(con->Create<ResourceManager>()),
    mapmanager_(con->Create<IMapManager>())
{

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

    return 0;
}

int GameScene::Draw()
{
    mapmanager_->Draw();
    
    return 0;

}

