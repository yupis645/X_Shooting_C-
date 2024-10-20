#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Game.h"
#include "di.hpp"
#include "DIContainer.h"
#include "SceneBase.h"
//#include "Player.h"
#include "IInputManager.h"
#include "ResourceManager.h"
//#include "EnemysManager.h"
//#include "BulletManager.h"
//#include "MapManager.h"

class GameScene : public SceneBase {
public:
    GameScene(std::shared_ptr<DIContainer> con,std::shared_ptr<Scenestatus> ss, std::shared_ptr<GameStatus> gs, std::shared_ptr<IInputManager> input, std::shared_ptr<ResourceManager> rm);

    // 初期化処理
    int Init() override;

    // 更新処理
    int Update() override;

    // 描画処理
    int Draw() override;

    ~GameScene() override {
        // 終了処理（リソース解放など）
    }
private:
    std::shared_ptr<DIContainer> container_;  // Player クラスへの依存
    std::shared_ptr<Scenestatus> scenestatus_;  // Player クラスへの依存
    std::shared_ptr<GameStatus> gamestatus_;  // Player クラスへの依存
    //std::shared_ptr<IPlayer> player_;  // Player クラスへの依存
    //std::shared_ptr<IEnemysManager> enemymanager_;
    //std::shared_ptr<IBulletManager>bulletmanager_;
    std::shared_ptr<IMapManager>mapmanager_;
    std::shared_ptr<IInputManager>inputmanager_;
    std::shared_ptr<ResourceManager>resourcemanager_;
};

#endif // GAMESCENE_H