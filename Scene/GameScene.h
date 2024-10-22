#ifndef GAMESCENE_H
#define GAMESCENE_H

class DIContainer;

#include "Game.h"
#include "DIContainer.h"
#include "di.hpp"
#include "SceneBase.h"
#include "IInputManager.h"
#include "ResourceManager.h"


class GameScene : public SceneBase {
public:
    GameScene(std::shared_ptr<DIContainer> con);


    int Init()override;

    // 更新処理
    int Update()override;

    // 描画処理
    int Draw() override;

    ~GameScene() override {
        // 終了処理（リソース解放など）
    }
private:
    std::shared_ptr<DIContainer> container_;  // Player クラスへの依存
    std::shared_ptr<GameStatus> gamestatus_;  // Player クラスへの依存
    std::shared_ptr<IMapManager>mapmanager_;
    std::shared_ptr<IInputManager>inputmanager_;
    std::shared_ptr<ResourceManager>resourcemanager_;


};

#endif // GAMESCENE_H