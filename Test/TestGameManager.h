#ifndef TESTGAMEMANAGER_H
#define TESTGAMEMANAGER_H

#include "Game.h"
#include "di.hpp"
#include "IGameManager.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "IInputManager.h"
#include "DIContainer.h"
#include "ResourceManager.h"
#include "common.h"

#include "TestScene.h"

class TestGameManager : public IGameManager{
public:
    TestGameManager(std::shared_ptr<DIContainer> con)
        : container_(con),
        scenestatus_(con->Create<Scenestatus>()),
        gamestatus_(con->Create<GameStatus>()),
        resoucemanager_(con->Create<ResourceManager>()),
        inputmanager_(con->Create<IInputManager>())
    {
        currentscene_ = std::make_shared<TestScene>(con,scenestatus_, gamestatus_, resoucemanager_,inputmanager_);
    }

    int Init()override;

    int Input()override;

    // シーンの更新と描画
    int Update() override;

    int Draw()override;

    // シーンの終了処理
    int End()override;

    //デストラクタ
    ~TestGameManager() {}

private:
    std::shared_ptr<SceneBase> currentscene_;  // 現在のシーン
    std::shared_ptr<GameStatus> gamestatus_;  // 現在のシーン
    std::shared_ptr<Scenestatus> scenestatus_;  // 現在のシーン
    std::shared_ptr<ResourceManager> resoucemanager_;  // 現在のシーン
    std::shared_ptr<IInputManager> inputmanager_;  // 現在のシーン
    std::shared_ptr<DIContainer> container_;  // DIContainer のメンバ変数

    //int ChangeScene(std::shared_ptr<SceneBase> newScene);
};

#endif ///ESTGAMEMANAGER_H
