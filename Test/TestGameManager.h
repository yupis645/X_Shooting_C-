#ifndef TESTGAMEMANAGER_H
#define TESTGAMEMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              テスト用GameManager
// 
// ゲーム全体を管理するクラスのテストクラス
// init(初期化),input(入力),update(更新),draw(描画)のライフサイクルを管理する
//----------------------------------------------------------------------------------------------------

class DIContainer;
class SceneManager;
class GameStatus;
class IInputManager;
class ResourceManager;
class SceneBase;
class SpriteRenderer;

#include <iostream>
#include "IGameManager.h"



class TestGameManager : public IGameManager{
public:
    TestGameManager(std::shared_ptr<DIContainer> con);      //コンストラクタ 

    int Init()override;         //初期化
    int Input()override;        //入力
    int GameLoop() override;      //更新

    int End()override;          //終了処理

    ~TestGameManager() {}       //デストラクタ

private:
    std::shared_ptr<SceneManager> scenemanager_;           // 現在の使用中のシーン
    std::shared_ptr<GameStatus> gamestatus_;            // ゲームのスコアなどゲーム全体で管理するデータ
    std::shared_ptr<ResourceManager> resoucemanager_;   // 描画に使う画像やCsvなどを保管する食らうs
    std::shared_ptr<IInputManager> inputmanager_;       // 入力を管理するクラス
    std::shared_ptr<SpriteRenderer> render_;       // 入力を管理するクラス
    std::shared_ptr<DIContainer> container_;            // DIContainer のメンバ変数
};

#endif ///ESTGAMEMANAGER_H
