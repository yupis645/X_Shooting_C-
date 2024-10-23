#ifndef TESTSCENE_H
#define TESTSCENE_H

class DIContainer;
class GameStatus;
class IInputManager;
class ResourceManager;
class SpriteRenderer;
class IMapManager;

#include "SceneBase.h"


class TestScene : public SceneBase {
public:
    TestScene(std::shared_ptr<DIContainer> container);

    int Init()override;

    // 更新処理
    int Update()override;

    // 描画処理
    int Draw() override;

    ~TestScene() override {}

private:
    std::shared_ptr<GameStatus> gamestatus_;  // Player クラスへの依存
    std::shared_ptr<ResourceManager> resourcemanager_;
   // std::shared_ptr<IMapManager> mapmanager_;  // Player クラスへの依存
    std::shared_ptr<SpriteRenderer> render_;  // Player クラスへの依存
    std::shared_ptr<IInputManager>inputmanager_;

};


#endif // TESTSCENE_H
