
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
#include "Game.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "SceneBase.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

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
	scenemanager_ = std::make_shared<SceneManager>(container_);
}

//===========================================================================================
//							初期化
//===========================================================================================
int GameManager::Init() {
	scenemanager_->SwitchToScene<TitleScene>();

	return 0;
}

//===========================================================================================
//							入力
// 
// InputReceptionにて方向キー、z,x,esc,enterなどゲーム中に使用する全てのキーの入力を取得する
// 他クラスはここでの入力結果を受けてアクションを起こす。
//===========================================================================================
int GameManager::Input()
{
	//全ての入力を受けつける
	inputmanager_->InputReception();

	//ESCキーの入力があった場合
	if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))		//escフラグをチェック
	{
		return SceneID::APP_EXIT;			//アプリの終了をmain関数に伝える	
	}


	return 0;

}

//===========================================================================================
//							シーンの更新
// 
// シーンの更新処理を行う。シーン中の細かな処理はSceneクラスが行う。
// ここではsceneクラスのUpdateの返り値によってエラー処理 及び シーン遷移を行う
//===========================================================================================
int GameManager::GameLoop() {

	int ir = scenemanager_->Init();
	int ur = scenemanager_->Update();
	int dr = scenemanager_->Draw();

	if (ir + ur + dr >= SceneID::APP_EXIT) return SceneID::APP_EXIT;

	return 0;
}

//===========================================================================================
//							終了処理
//===========================================================================================
int GameManager::End() {

	return 99;
}