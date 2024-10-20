#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class DIContainer;
class GameStatus;
class Scenestatus;
class IInputManager;
class ResourceManager;
class GameTextureManager;
class SceneBase;

#include "Game.h"
#include "di.hpp"
#include "IGameManager.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "DIContainer.h"
#include "common.h"


class GameManager :public IGameManager {
public:
    GameManager(std::shared_ptr<DIContainer> con)
        : container_(con),
        scenestatus_(con->Create<Scenestatus>()),
        gamestatus_(con->Create<GameStatus>()),
       inputmanager_(con->Create<IInputManager>()) ,
       resourcemanager_(con->Create<ResourceManager>())
    {
        currentscene_ = std::make_shared<TitleScene>(container_, scenestatus_, gamestatus_, inputmanager_,resourcemanager_);
    }

    // テンプレート関数でシーンを生成して切り替え
    template <typename SceneType>
    void SwitchToScene() {
        currentscene_ = std::make_shared<SceneType>( container_, scenestatus_, gamestatus_, inputmanager_, resourcemanager_);
    }

    int Init()override;

    int Input()override;

    // シーンの更新と描画
    int Update()override;

    int Draw()override;

    // シーンの終了処理
    int End()override;

    //デストラクタ
    ~GameManager() {}

private:
    std::shared_ptr<DIContainer> container_;  // Diコンテナ
    std::shared_ptr<GameStatus> gamestatus_;  // ゲーム関連のステータス
    std::shared_ptr<Scenestatus> scenestatus_;  // シーンに関するステータス
    std::shared_ptr<IInputManager> inputmanager_;  // 入力関係
    std::shared_ptr<ResourceManager> resourcemanager_;  // 画像やCSVファイルなどを管理するクラス
    std::shared_ptr<SceneBase> currentscene_;  // 現在のシーン

    //int ChangeScene(std::shared_ptr<SceneBase> newScene);
};

#endif // GAMEMANAGER_H
