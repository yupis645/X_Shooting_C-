#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              ゲーム全体を管理するクラス
// 
// ゲーム全体を管理するクラス。ゲーム開始から終了まで生存し続ける
// diコンテナではシングルトンでバインドされているので、create関数で常に同じインスタンスが取得できる
// init(初期化),input(入力),update(更新),draw(描画)のライフサイクルを管理する
//----------------------------------------------------------------------------------------------------

#include "Game.h"
#include "di.hpp"
#include "IGameManager.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "DIContainer.h"
#include "SceneManager.h"


class GameManager :public IGameManager {
public:
    GameManager(std::shared_ptr<DIContainer> con);      //コンストラクタ

    int Init()override;         //初期化
    int Input()override;        //入力
    int GameLoop()override;    //更新
    int End()override;    // 終了処理
    
    ~GameManager() {}   //デストラクタ


    // テンプレート関数でシーンを生成して切り替える
    template <typename SceneType>
    void SwitchToScene() {
        currentscene_ = std::make_shared<SceneType>(container_);
    }
private:
    std::shared_ptr<DIContainer> container_;            // Diコンテナ
    std::shared_ptr<SceneManager> scenemanager_;            // Diコンテナ
    std::shared_ptr<GameStatus> gamestatus_;            // ゲーム関連のステータス
    std::shared_ptr<IInputManager> inputmanager_;       // 入力クラス
    std::shared_ptr<ResourceManager> resourcemanager_;  // 画像やCSVファイルなどを管理するクラス
    std::shared_ptr<SceneBase> currentscene_;           // 現在のシーン


};

#endif // GAMEMANAGER_H
