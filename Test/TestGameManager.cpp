
//----------------------------------------------------------------------------------------------------
//                              テスト用GameManager
// 
// ゲーム全体を管理するクラスのテストクラス
// init(初期化),input(入力),update(更新),draw(描画)のライフサイクルを管理する
//----------------------------------------------------------------------------------------------------

#include "TestGameManager.h"
#include "TestScene.h"

#include "GameManager.h"
#include "GameScene.h" 
#include "TitleScene.h" 
#include "DIContainer.h"
#include "SceneManager.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "SceneBase.h"


//==================================================================
//						コンストラクタ
// 
// diコンテナより、gameStatus,ResouceManager,InputManagerのインスタンスを取得する
// currnetscene_には最初に使用するシーンを指定する
//==================================================================
TestGameManager::TestGameManager(std::shared_ptr<DIContainer> con)
	: container_(con),
	gamestatus_(con->Create<GameStatus>()),
	resoucemanager_(con->Create<ResourceManager>()),
	inputmanager_(con->Create<IInputManager>()),
	render_(con->Create<SpriteRenderer>())
{
}

//==================================================================
//						初期化
//==================================================================
int TestGameManager::Init() {
	scenemanager_->SwitchToScene<TestScene>();

	return 0;
}

//==================================================================
//						入力
//==================================================================
int TestGameManager::Input()
{
	return 0;
}


//==================================================================
//						更新
//==================================================================
int TestGameManager::GameLoop() {

	scenemanager_->Init();
	scenemanager_->Update();
	scenemanager_->Draw();

	



	return 0;
}



//==================================================================
//						終了処理
//==================================================================
int TestGameManager::End() {

	return 99;
}