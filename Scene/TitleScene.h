#ifndef TITLESCENE_H
#define TITLESCENE_H
#include <array>
#include "di.hpp"

class GameStatus;
class IInputManager;
struct StringText;

#include "Geometry.h"
#include "SceneBase.h"
#include "IInputManager.h"
#include "DIContainer.h"
#include "SpriteRenderer.h"

class TitleScene : public SceneBase {
public:
    TitleScene(std::shared_ptr<DIContainer> con);


    // 初期化処理
    int Init() override;

    // 更新処理
    int Update()override;

    // 描画処理
    int Draw() override;

    ~TitleScene() override;

private :
    std::shared_ptr<DIContainer> container_;  // Player クラスへの依存
    std::shared_ptr<GameStatus> gamestatus_;  // Player クラスへの依存
    std::shared_ptr<IInputManager>inputmanager_;
    std::shared_ptr<ResourceManager>resourcemanager_;
    std::shared_ptr<SpriteRenderer>render_;

    std::shared_ptr<GameTexture> titlenameplate;       //マップチップの画像を保管しておく変数
    std::array<StringText , 3> menu;


};


#endif // TITLESCENE_H
