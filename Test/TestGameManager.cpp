#include "TestGameManager.h"

#include "TestScene.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

int TestGameManager::Init() {
	currentscene_->Init();


	return 0;
}

int TestGameManager::Input()
{
	return 0;
}

// シーンの更新と描画
int TestGameManager::Update() {

	
	currentscene_->Update();



	return 0;
}

int TestGameManager::Draw()
{
	ClearScreen(0x10, 0x10, 0x10);	//画面消去：R,G,Bの指定色で塗りつぶす
	//▼▼▼ここから
	inputmanager_->InputReception();
	currentscene_->Draw();
	//▲▲▲ここまで
	PrintFrameBuffer();	//画面バッファを転送
	RenderScreen();		//画面をレンダリング
	FrameSync();		//１フレームの同期    

	return 0;
}

// シーンの終了処理
int TestGameManager::End() {

	return 99;
}