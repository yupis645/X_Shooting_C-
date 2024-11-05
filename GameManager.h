#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              ゲーム全体を管理するクラス
// 
// ゲーム全体を管理するクラス。ゲーム開始から終了まで生存し続ける
// diコンテナではシングルトンでバインドされているので、create関数で常に同じインスタンスが取得できる
// init(初期化),input(入力),update(更新),draw(描画)のライフサイクルを管理する
//----------------------------------------------------------------------------------------------------

class DIContainer;
class SceneManager;            
class GameStatus;          
class IInputManager;       
class ResourceManager;
class SceneBase;

#include "StepTimer.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.


class GameManager  {
public:
    GameManager(std::shared_ptr<DIContainer> con);      //コンストラクタ
    ~GameManager() = default;

    // Initialization and management
 //初期化

    //初期化
    void Initialize(Game* game, HWND window, HINSTANCE hInstance);

    //更新
    int Update();

    //入力
    int Input();

    //描画
    void Draw();

    //解放
    void Relese();

private:
    void SetUp();


private:

    std::shared_ptr<DIContainer> container_;            // Diコンテナ
    std::shared_ptr<SceneManager> scenemanager_;            // Diコンテナ
    std::shared_ptr<GameStatus> gamestatus_;            // ゲーム関連のステータス
    std::shared_ptr<IInputManager> inputmanager_;       // 入力クラス
    std::shared_ptr<ResourceManager> resourcemanager_;  // 画像やCSVファイルなどを管理するクラス
    std::shared_ptr<SceneBase> currentscene_;           // 現在のシーン


    IDirectInput8* m_directInput;               //DirectInputDevice8を作成するための関数やDirectXを使用するPCがどこまで機能を使いこなせるかをチェックする関数
    IDirectInputDevice8* m_keyboardDevice;      //IDirectInputDevice8はデバイス入力を管理するインターフェース

};




#endif // GAMEMANAGER_H
