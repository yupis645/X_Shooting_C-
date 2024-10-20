#include "GameManager.h"
#include "GameScene.h" 
#include "TitleScene.h" 

static int a = ScreenConfig::SRN_W;
static int b = ScreenConfig::SRN_H;
static int c = ScreenConfig::PXW;
static int d = ScreenConfig::PXH;

#include "conioex.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

int GameManager::Init() {
	return 0;
}

int GameManager::Input()
{
	inputmanager_->InputReception();

	if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))
	{
		return 999;
	}

	


//#if TestMode
//	if (DebugOn) {
//		//デバックモードの有効化 / 無効化
//		if (ChkKeyEdge(PK_D)) { DebugEnable = DebugEnable ? false : true; }
//	}
//#endif

	return 0;

}
//
//// シーンの切り替え
//int GameManager::ChangeScene(std::shared_ptr<SceneBase> newScene) {
//	currentscene_ = newScene;
//	if (currentscene_) {
//		currentscene_->Init();
//		return 0;
//	}
//	return -1;
//}

// シーンの更新と描画
int GameManager::Update() {

	
	currentscene_->Update();

	if (scenestatus_->SceneChangeSignal())
	{
		SwitchToScene<GameScene>();
	}


	return 0;
}

int GameManager::Draw() 
{
	ClearScreen(0x10, 0x10, 0x10);	//画面消去：R,G,Bの指定色で塗りつぶす
	//▼▼▼ここから
	currentscene_->Draw();
	//▲▲▲ここまで
	PrintFrameBuffer();	//画面バッファを転送
	RenderScreen();		//画面をレンダリング
	FrameSync();		//１フレームの同期    

	return 0;
}

// シーンの終了処理
int GameManager::End() {

	return 99;
}