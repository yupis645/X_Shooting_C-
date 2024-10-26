#include "TestGameScene.h"
#include "DebugManager.h"
#include "DIContainer.h"

#include "MapManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameSceneFactory.h"
#include "Player.h"
#include <memory>

TestGameScene::TestGameScene(std::shared_ptr<DIContainer> con)
    :GameScene(con),debug_(con->Create<DebugManager>())
{
    // TestInputManager 型へのキャストを試みる
    auto isinput_instance = std::dynamic_pointer_cast<TestInputManager>(con->Create<IInputManager>());

    if (isinput_instance) {         // 成功した場合、isinput_instance は TestInputManager 型として使用可能
        std::cout << "TestInputManager のインスタンスです" << std::endl;
        testinput_ = isinput_instance;
    }
    else {                          // 失敗した場合、isinput_instance は nullptr
        std::cout << "InputManager のインスタンスまたは他の型です" << std::endl;
        testinput_ = nullptr;
    }
}

int TestGameScene::Init()
{
    GameScene::Init();
    return 0;
}

int TestGameScene::Update()
{
    GameScene::Update();
    if (testinput_ != nullptr)
    {
        testinput_->DebugCreateAirEnemy();
    }

    return 0;
}

int TestGameScene::Draw()
{
    GameScene::Draw();


    auto enemys = GameScene::GetEnemys();
    auto bullets = GameScene::GetBullets();
    for (size_t i = 0; i < enemys->AirEnemysArray().size(); i++) {
        if (enemys->GetAirEnemysIndex(i)->GetActive()) {
            debug_->DrawHitBox(*enemys->GetAirEnemysIndex(i), 255, 0, 0, false);
        }
    }
    for (size_t i = 0; i < bullets->GetPlayershotSum(); i++) {
        debug_->DrawHitBox(*bullets->GetPlayerShotIndex(i),255,0,0,false);
    }
        debug_->DrawHitBox(*bullets->GetPlayerBom(), 255, 0, 0, false);
     for (size_t i = 0; i < bullets->GetEnemyshotSum(); i++) {
         if (bullets->GetEnemyShotIndex(i)->GetActive()) {
             debug_->DrawHitBox(*bullets->GetEnemyShotIndex(i), 255, 0, 0, false);
         }
    }


    return 0;
}
