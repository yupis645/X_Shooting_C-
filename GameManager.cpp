
//----------------------------------------------------------------------------------------------------
//                              ゲーム全体を管理するクラス
// 
// ゲーム全体を管理するクラス。ゲーム開始から終了まで生存し続ける
// diコンテナではシングルトンでバインドされているので、create関数で常に同じインスタンスが取得できる
// init(初期化),input(入力),update(更新),draw(描画)のライフサイクルを管理する
//----------------------------------------------------------------------------------------------------
#include "GameManager.h"
#include "GameScene.h" 
#include "TitleScene.h" 
#include "DIContainer.h"
#include "SceneManager.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "SceneBase.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;


using namespace DirectX;

//===========================================================================================
//							コンストラクタ
// 
// diコンテナより必要な関数のインスタンスを作成してメンバ変数で保管する
// currentsceneにはTitleSceneクラスを最初に作成する
//===========================================================================================
GameManager::GameManager(std::shared_ptr<DIContainer> con)
	: container_(con),
	gamestatus_(con->Create<GameStatus>()),
	inputmanager_(con->Create<IInputManager>()),
	resourcemanager_(con->Create<ResourceManager>())
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));		//時刻を指針に乱数をセット
	scenemanager_ = std::make_shared<SceneManager>(container_);
}

//===========================================================================================
//							初期化
//===========================================================================================
void GameManager::Initialize(Game* game, HWND window, HINSTANCE hInstance)
{
    //IDirectInput8インターフェイスの作成
    HRESULT hr = DirectInput8Create(
        hInstance,                 //アプリケーションのインスタンスハンドル
        DIRECTINPUT_VERSION,    //directInputのバージョン(DIRECTINPUT_VERSIONで固定でいい)
        IID_IDirectInput8,
        (void**)&m_directInput,
        NULL);
    if (FAILED(hr))
    {
        // 失敗
    }

    //IDirectInputDevice8の作成
    hr = m_directInput->CreateDevice(
        GUID_SysKeyboard,       //使用するデバイスの種類(今回はキーボード)
        &m_keyboardDevice,      //IDirectInputDevice8インターフェース受け取る
        NULL                    //基本NULL
    );
    if (FAILED(hr))
    {
        // 失敗
    }

    //デバイスのフォーマットの設定
    hr = m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard);

    if (FAILED(hr))
    {
        //失敗
    }

    // 協調モードの設定
    if (FAILED(m_keyboardDevice->SetCooperativeLevel(
        window,
        DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
    ))

        // 制御開始
        hr = m_keyboardDevice->Acquire();

    if (FAILED(hr))
    {
        // 制御開始失敗
    }
    {
        // 失敗
    }

    SetUp();
}

//ゲームの初期設定を行う
void GameManager::SetUp()
{

    //シーン作成
    scenemanager_->SwitchToScene<TitleScene>();
}


//===========================================================================================
//							入力
// 
// InputReceptionにて方向キー、z,x,esc,enterなどゲーム中に使用する全てのキーの入力を取得する
// 他クラスはここでの入力結果を受けてアクションを起こす。
//===========================================================================================
int GameManager::Input()
{
    ////全ての入力を受けつける
    //inputmanager_->InputReception();

    ////ESCキーの入力があった場合
    //if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))		//escフラグをチェック
    //{
    //    return SceneID::APP_EXIT;			//アプリの終了をmain関数に伝える	
    //}


    // GetDeviceState関数使用例
// キー情報取格納用
    BYTE KeyState[256];
    HRESULT hr;

    // キーボードデバイスのゲッター
    hr = m_keyboardDevice->GetDeviceState(256, KeyState);
    if (SUCCEEDED(hr))
    {

        // 上キー
        if (KeyState[DIK_UP] & 0x80)
        {
            //m_pos.y += 4.f;
        }

        // 下キー
        if (KeyState[DIK_DOWN] & 0x80)
        {
            //m_pos.y -= 4.f;
        }

        // 左キー
        if (KeyState[DIK_LEFT] & 0x80)
        {
            //m_pos.x -= 4.f;
        }

        // 右キー
        if (KeyState[DIK_RIGHT] & 0x80)
        {
            //m_pos.x += 4.f;
        }

        // リターンキー
        if (KeyState[DIK_RETURN] & 0x80)
        {

        }

        // トリガー情報取得

        // デバイスロスト時は再度制御開始を呼ぶ
    }
    else if (hr == DIERR_INPUTLOST) {
        m_keyboardDevice->Acquire();
    }
}

//===========================================================================================
//							シーンの更新
// 
// シーンの更新処理を行う。シーン中の細かな処理はSceneクラスが行う。
// ここではsceneクラスのUpdateの返り値によってエラー処理 及び シーン遷移を行う
//===========================================================================================
int GameManager::Update()
{

    int ir = scenemanager_->Init();
    int ur = scenemanager_->Update();
    int dr = scenemanager_->Draw();

    if (ir + ur + dr >= SceneID::APP_EXIT) return SceneID::APP_EXIT;

    return 0;
}
void GameManager::Draw()
{
}
void GameManager::Relese()
{
    //DirectInputの停止
    //1.デバイス制御の停止
    m_keyboardDevice->Unacquire();
    // IDirectInputDevice8の解放
    m_keyboardDevice->Release();
    //IDirectInput8の解放
    m_directInput->Release();
}

