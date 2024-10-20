
#include"common.h"
#include "Game.h"
#include "di.hpp"
#include "GameManager.h"
#include "TitleScene.h"
#include "Geometry.h"
#include "DIContainer.h"

#include "TestGameManager.h"


// デバックモードの初期状態。デバックモードが有効なら最初からtrue
bool DebugEnable = DebugOn;
/*
* @brief	main()関数
*
* @note	アプリの開始位置。
*	画面遷移の流れを作って制御している
*/
int main(void)
{
	//【アプリ全体の初期化】
	SetCaption("2023 HAL Osaka.");	//ウィンドウタイトル

	InitConioEx(ScreenConfig::SRN_W, 
				ScreenConfig::SRN_H,
				ScreenConfig::PXW,
				ScreenConfig::PXH);	//初期化：タテヨコサイズとドットの大きさ





	//【画面遷移の為のループ】
	int scene_id = TITLE;
	// SCENE構造体をDIコンテナに登録する
	//auto injector = di::make_injector(
	//	di::bind<Scenestatus>().to(std::make_shared<Scenestatus>()),   // SCENEを作成し、登録
	//	di::bind<IPlayer>().to<Player>()	//プレイヤー
	//);

	//DIContainer container;

	//auto playerpt = injector.create<std::shared_ptr<Player>>();
	// 
	// 
	   // DIコンテナを作成
	auto injector = std::make_shared<DIContainer>();

	auto GM = injector->Create<GameManager>();

	//// GameManagerをDIコンテナから取得
	//auto GM = std::make_shared<GameManager>(injector);

	// GameManagerの初期化
	GM->Init();

	while (1) {

		int state = GM->Input();
		int gamestate = GM->Update();
		int sw = GM->Draw();

		if (state == APP_EXIT) {
			break;
		}
	}

	GM->End();

	//【アプリ全体の終了処理】
	EndConioEx();	//ConioExの終了処理
	return 0;
}


//
//// デバックモードの初期状態。デバックモードが有効なら最初からtrue
//bool DebugEnable = DebugOn;
//
////スコアと残機などシーンを跨いで使用する情報
// GAMESTATE state = {0,0};
///*
//* @brief	main()関数
//*
//* @note	アプリの開始位置。
//*	画面遷移の流れを作って制御している
//*/
//int main(void)
//{
//	//【アプリ全体の初期化】
//	SetCaption("2023 HAL Osaka.");	//ウィンドウタイトル
//	InitConioEx(SRN_W, SRN_H, PXW, PXH);	//初期化：タテヨコサイズとドットの大きさ
//
//	//【画面遷移の為のループ】
//	int scene_id = TITLE;
//	// SCENE構造体をDIコンテナに登録する
//	//auto injector = di::make_injector(
//	//	di::bind<Scenestatus>().to(std::make_shared<Scenestatus>()),   // SCENEを作成し、登録
//	//	di::bind<IPlayer>().to<Player>()	//プレイヤー
//
//	//);
//
//	//DIContainer container;
//
//	//auto playerpt = injector.create<std::shared_ptr<Player>>();
//
//
//	GameManager Gamemanager(std::make_shared<DIContainer>(),std::make_shared<TitleScene>(),std::make_shared<GameStatus>(),std::make_shared<InputManager>());
//	Gamemanager.Init();
//
//
//	while (true) {
//		switch (scene_id) {
//		case	TITLE:	//タイトル画面
//			Title(&scTitle);
//			scene_id = scTitle.next_scene;	//次の画面IDを受け取る
//			break;
//		case	GAME:	//ゲーム画面
//			Game(&scGame);
//			scene_id = scGame.next_scene;	//次の画面IDを受け取る
//			break;
//		case	RESULT:	//リザルト画面
//			Result(&scResult);
//			scene_id = scResult.next_scene;	//次の画面IDを受け取る
//		}
//		//アプリ終了判定
//		if (scene_id == APP_EXIT) {
//			break;
//		}
//	}
//	//【アプリ全体の終了処理】
//	EndConioEx();	//ConioExの終了処理
//	return 0;
//}
//
//




//----------------------------------------------------------------
//	2023 HAL osaka.
//----------------------------------------------------------------
