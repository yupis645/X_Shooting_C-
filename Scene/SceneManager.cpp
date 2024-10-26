

//----------------------------------------------------------------------------------------------------
//                              ゲーム全体を管理するクラス
// 
// ゲーム全体を管理するクラス。ゲーム開始から終了まで生存し続ける
// diコンテナではシングルトンでバインドされているので、create関数で常に同じインスタンスが取得できる
// init(初期化),input(入力),update(更新),draw(描画)のライフサイクルを管理する
//----------------------------------------------------------------------------------------------------
#include "SceneManager.h"

#include "SceneBase.h"
#include "GameScene.h" 
#include "TitleScene.h" 

#include "DIContainer.h"
#include "DebugManager.h" 
#include "InputManager.h" 

#include "TestGameScene.h"


#include "conioex.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

//.cppで使われる定数
namespace {

	//引数2で指定されたsceneidから次に変更するシーンを指定して変更する
	void ChangeSceneID(SceneManager& sm, int sceneid) {
		switch (sceneid)
		{
		case SceneID::TITLE:
			sm.SwitchToScene<TitleScene>();		//タイトルシーンをもう一度ロードする
			break;
		case SceneID::GAME:
			sm.SwitchToScene<TestGameScene>();		//ゲームシーンをロードする
			break;
		case SceneID::OPTION:					//オプションシーンをロードする
			break;
		case SceneID::RESULT:					//リザルトシーンをロードする
			break;

		}
	}
}

//===========================================================================================
//							初期化
//===========================================================================================
int SceneManager::Init() {
	if (currentscene_->GetIsinit())  return 0;		//sceneクラスのisinitがtrueの間は初期化しない

	currentscene_->Init();


	currentscene_->SetIsinit(true);		//初期化を1回以上入らないようにisinitをfalseに設定する

	return 0;
}


//===========================================================================================
//							シーンの更新
// 
// シーンの更新処理を行う。シーン中の細かな処理はSceneクラスが行う。
// ここではsceneクラスのUpdateの返り値によってエラー処理 及び シーン遷移を行う
//===========================================================================================
int SceneManager::Update() {

	currentscene_->FrameCountUpdate(1);

	int status = currentscene_->Update();

	//返り値が -1 の場合
	if (status == -1) {
		std::cerr << "Error: SceneManager Update in scenemanager return -1: " << std::endl;	//エラーを出す
		return SceneID::APP_EXIT;			//アプリの終了をmain関数に伝える	 
	}

	//返り値が SceneIDの範囲であった場合
	if (status >= SceneID::TITLE && status <= SceneID::RESULT)
	{
		ChangeSceneID(*this, status);		//statusの番号によって次のシーンを決定する。関数はnamespaceにある
	}


	return 0;
}

//===========================================================================================
//							画面への描画
// 
// 画面への描画を行う。細かな描画内容はシーンのDrawが管理する。
// 画面のクリアを行ってから描画を行う
//===========================================================================================
int SceneManager::Draw()
{
	ClearScreen(0x10, 0x10, 0x10);	//画面消去：R,G,Bの指定色で塗りつぶす

	currentscene_->Draw();

	//container_->Create<DebugManager>()->DrawInputFrag();
	//container_->Create<DebugManager>()->DebugDrawTexture(DebugTexture::DebugSelectDraw::Boss);

	PrintFrameBuffer();	//画面バッファを転送
	RenderScreen();		//画面をレンダリング
	FrameSync();		//１フレームの同期    

	return 0;
}
